import math
import numpy as np
import matplotlib.pyplot as plt

# Optional dependencies: only needed for some interactive workflows.
try:
    import pandas as pd  # noqa: F401
except ModuleNotFoundError:  # pragma: no cover
    pd = None

try:
    from IPython.display import clear_output  # type: ignore
except ModuleNotFoundError:  # pragma: no cover
    def clear_output(*args, **kwargs):  # type: ignore
        return None


class CellInteractionSimulation:
    """
    A class to encapsulate various cell-cell interaction potentials and
    simulate cell motion under these potentials.

    Parameters
    ----------
    potential_model : str
        The model of the potential to use. Options:
        - "original": Use the original cell interaction potential.
        - "morse": Use the Morse-type potential.
        - "else": Placeholder for future implementations.

    r_default : float, optional
        Default radius of each cell (default is 8.413).
    c1_repulsion : float, optional
        Repulsion coefficient for the first cell (default is 100.0).
    c2_repulsion : float, optional
        Repulsion coefficient for the second cell (default is 100.0).
    c1_adhesion : float, optional
        Adhesion coefficient for the first cell (default is 0.4).
    c2_adhesion : float, optional
        Adhesion coefficient for the second cell (default is 0.4).
    c1_relative_maximum_adhesion_distance : float, optional
        Relative maximum adhesion distance for the first cell (default is 1.25).
    c2_relative_maximum_adhesion_distance : float, optional
        Relative maximum adhesion distance for the second cell (default is 1.25).
    Pd : float, optional
        Packing density parameter for the Morse potential (default is 0.9).
    N : int, optional
        Number of cells (or effective parameter) for the Morse potential (default is 1000).
    l : float, optional
        Dimensionless parameter used in scaling for the Morse potential (default is 0.75).
    k0 : float, optional
        Base stiffness parameter for the Morse potential (default is 5e-3).
    rho : float, optional
        Scaling factor in the Morse exponent (default is 2.0).
    alpha : float, optional
        Shifting factor in the Morse potential (default is 2.0).

    Attributes (common)
    -------------------
    potential_model : str
        The chosen potential model.
    r_default : float
        Default radius of each cell.
    R : float
        Sum of the radii of the two cells.
    S : float
        Effective maximum adhesion distance between the two cells.

    Attributes (original potential)
    -------------------------------
    c1_repulsion : float
        Repulsion coefficient for the first cell.
    c2_repulsion : float
        Repulsion coefficient for the second cell.
    c1_adhesion : float
        Adhesion coefficient for the first cell.
    c2_adhesion : float
        Adhesion coefficient for the second cell.
    effective_repulsion : float
        Effective repulsion coefficient.
    effective_adhesion : float
        Effective adhesion coefficient.

    Attributes (Morse potential)
    ----------------------------
    Pd : float
        Packing density parameter.
    N : int
        Number of cells (or effective parameter).
    l : float
        Dimensionless parameter used in scaling.
    k0 : float
        Base stiffness parameter.
    rho : float
        Scaling factor in the Morse exponent.
    alpha : float
        Shifting factor in the Morse potential.
    k : float
        Computed stiffness parameter that depends on N and l.
    u0 : float
        Potential well depth for the Morse potential.
    r_eq : float
        Equilibrium distance for the Morse potential.
    initial_distance : float
        Default initial distance between cells for Morse potential simulations.
    """

    def __init__(self,
                 potential_model="original",
                 # Original potential parameters
                 r_default=8.413,
                 c1_repulsion=100.0, c2_repulsion=100.0,
                 c1_adhesion=0.4, c2_adhesion=0.4,
                 c1_relative_maximum_adhesion_distance=1.25,
                 c2_relative_maximum_adhesion_distance=1.25,
                 # Morse potential parameters
                 Pd=0.9, N=1000, l=0.75, k0=5e-3,
                 rho=2.0, alpha=2.0,
                 # Kelvin-Voigt parameters (new)
                 kv_rest_length=None,
                 kv_spring_constant=1.0,
                 kv_dissipation_rate=0.1):

        self._potential_model = potential_model
        # Original potential parameters
        self._r_default = r_default
        self._r1 = self._r_default
        self._r2 = self._r_default
        self._c1_repulsion = c1_repulsion
        self._c2_repulsion = c2_repulsion
        self._c1_adhesion = c1_adhesion
        self._c2_adhesion = c2_adhesion
        self._c1_relative_maximum_adhesion_distance = c1_relative_maximum_adhesion_distance
        self._c2_relative_maximum_adhesion_distance = c2_relative_maximum_adhesion_distance

        self._R = self._r1 + self._r2
        self._S = (self._c1_relative_maximum_adhesion_distance * self._r1) + \
                  (self._c2_relative_maximum_adhesion_distance * self._r2)

        self._effective_repulsion = np.sqrt(self._c1_repulsion * self._c2_repulsion)
        self._effective_adhesion = np.sqrt(self._c1_adhesion * self._c2_adhesion)

        # Morse potential parameters
        self._Pd = Pd
        self._N = N
        self._l = l
        self._k0 = k0
        self._density_factor = (self._Pd / self._N) ** (1 / 2)
        self._r_eq = 2 * self._R  # equilibrium distance typically chosen as 2*R
        self._rho = rho
        self._alpha = alpha
        self._k = self._k0 * self._N ** (-1 / 3) * (1 - (self._l * self._N ** (-1 / 3)))
        self._u0 = self._k * ((self._r_eq ** 2) / (8 * self._rho ** 2))
        self._initial_distance = 2 * self._R + 1

        # Set Kelvin-Voigt parameters
        self._kv_rest_length = kv_rest_length if kv_rest_length is not None else 2 * self._R
        self._kv_spring_constant = kv_spring_constant
        self._kv_dissipation_rate = kv_dissipation_rate

    @property
    def potential_model(self):
        return self._potential_model

    @potential_model.setter
    def potential_model(self, value):
        self._potential_model = value

    @property
    def r_default(self):
        return self._r_default

    @r_default.setter
    def r_default(self, value):
        self._r_default = value

    @property
    def r1(self):
        return self._r1

    @r1.setter
    def r1(self, value):
        self._r1 = value

    @property
    def r2(self):
        return self._r2

    @r2.setter
    def r2(self, value):
        self._r2 = value

    @property
    def c1_repulsion(self):
        return self._c1_repulsion

    @c1_repulsion.setter
    def c1_repulsion(self, value):
        self._c1_repulsion = value

    @property
    def c2_repulsion(self):
        return self._c2_repulsion

    @c2_repulsion.setter
    def c2_repulsion(self, value):
        self._c2_repulsion = value

    @property
    def c1_adhesion(self):
        return self._c1_adhesion

    @c1_adhesion.setter
    def c1_adhesion(self, value):
        self._c1_adhesion = value

    @property
    def c2_adhesion(self):
        return self._c2_adhesion

    @c2_adhesion.setter
    def c2_adhesion(self, value):
        self._c2_adhesion = value

    @property
    def c1_relative_maximum_adhesion_distance(self):
        return self._c1_relative_maximum_adhesion_distance

    @c1_relative_maximum_adhesion_distance.setter
    def c1_relative_maximum_adhesion_distance(self, value):
        self._c1_relative_maximum_adhesion_distance = value

    @property
    def c2_relative_maximum_adhesion_distance(self):
        return self._c2_relative_maximum_adhesion_distance

    @c2_relative_maximum_adhesion_distance.setter
    def c2_relative_maximum_adhesion_distance(self, value):
        self._c2_relative_maximum_adhesion_distance = value

    @property
    def R(self):
        return self._R

    @R.setter
    def R(self, value):
        self._R = value

    @property
    def S(self):
        return self._S

    @S.setter
    def S(self, value):
        self._S = value

    @property
    def effective_repulsion(self):
        return self._effective_repulsion

    @effective_repulsion.setter
    def effective_repulsion(self, value):
        self._effective_repulsion = value

    @property
    def effective_adhesion(self):
        return self._effective_adhesion

    @effective_adhesion.setter
    def effective_adhesion(self, value):
        self._effective_adhesion = value

    @property
    def Pd(self):
        return self._Pd

    @Pd.setter
    def Pd(self, value):
        self._Pd = value

    @property
    def N(self):
        return self._N

    @N.setter
    def N(self, value):
        self._N = value

    @property
    def l(self):
        return self._l

    @l.setter
    def l(self, value):
        self._l = value

    @property
    def k0(self):
        return self._k0

    @k0.setter
    def k0(self, value):
        self._k0 = value

    @property
    def density_factor(self):
        return self._density_factor

    @density_factor.setter
    def density_factor(self, value):
        self._density_factor = value

    @property
    def r_eq(self):
        return self._r_eq

    @r_eq.setter
    def r_eq(self, value):
        self._r_eq = value

    @property
    def rho(self):
        return self._rho

    @rho.setter
    def rho(self, value):
        self._rho = value

    @property
    def alpha(self):
        return self._alpha

    @alpha.setter
    def alpha(self, value):
        self._alpha = value

    @property
    def k(self):
        return self._k

    @k.setter
    def k(self, value):
        self._k = value

    @property
    def u0(self):
        return self._u0

    @u0.setter
    def u0(self, value):
        self._u0 = value

    @property
    def initial_distance(self):
        return self._initial_distance

    @initial_distance.setter
    def initial_distance(self, value):
        self._initial_distance = value

    @property
    def kv_rest_length(self):
        return self._kv_rest_length

    @kv_rest_length.setter
    def kv_rest_length(self, value):
        self._kv_rest_length = value

    @property
    def kv_spring_constant(self):
        return self._kv_spring_constant

    @kv_spring_constant.setter
    def kv_spring_constant(self, value):
        self._kv_spring_constant = value

    @property
    def kv_dissipation_rate(self):
        return self._kv_dissipation_rate

    @kv_dissipation_rate.setter
    def kv_dissipation_rate(self, value):
        self._kv_dissipation_rate = value

    def cell_interaction_potential(self, d, R=None, S=None,
                                   effective_repulsion=None, effective_adhesion=None,
                                   div_d_flag=True):
        """
        Compute the original cell-cell interaction potential.
        """
        if R is None:
            R = self.R
        if S is None:
            S = self.S
        if effective_repulsion is None:
            effective_repulsion = self.effective_repulsion
        if effective_adhesion is None:
            effective_adhesion = self.effective_adhesion

        # Repulsion potential

        if d <= R:
            temp_r = (1 - d / R) ** 2 * effective_repulsion
        else:
            temp_r = 0

        # Adhesion potential
        if d < S:
            temp_a = (1 - d / S) ** 2 * effective_adhesion
        else:
            temp_a = 0

        # Total potential
        total_potential = temp_r - temp_a

        # Divide by d if div_d_flag is True
        if div_d_flag:
            total_potential /= d

        return total_potential, temp_r, temp_a

    def cell_interaction_morse_potential(self, d, d_eq=None, rho=None, alpha=None, u0=None):
        """
        Compute the Morse-type cell-cell interaction potential.
        """
        if d_eq is None:
            d_eq = self.r_eq
        if rho is None:
            rho = self.rho
        if alpha is None:
            alpha = self.alpha
        if u0 is None:
            u0 = self.u0

        d = np.array(d, ndmin=1)
        fraction = d ** 2 / (d_eq ** 2)
        exp_argument = rho * (1 - fraction)
        V = (u0 * np.exp(2 * exp_argument)) - (alpha * u0 * np.exp(exp_argument))
        return V

    def cell_interaction_kv_potential(self, d, d_eq=None, k_spring=None):
        """
        Compute the Kelvin-Voigt elastic potential (spring part only).
        Note: The viscous part is handled separately as it depends on velocity.

        U = 0.5 * k * (d - d_eq)^2
        """
        if d_eq is None:
            d_eq = self.kv_rest_length
        if k_spring is None:
            k_spring = self.kv_spring_constant

        return 0.5 * k_spring * (d - d_eq)**2

    def get_potential(self, distance):
        """
        Get the potential from the currently selected potential model for the given distance(s).
        """
        if self.potential_model == "original":
            total_potential, repulsive_potential, adhesive_potential = self.cell_interaction_potential(distance)
            return total_potential
        elif self.potential_model == "morse":
            return self.cell_interaction_morse_potential(distance)
        elif self.potential_model == "kv":
            # For K-V, just return the elastic part
            return self.cell_interaction_kv_potential(distance)
        else:
            # Placeholder for future potential types
            return 0

    def simulate_motion(self, time_step=0.001, initial_velocity=0.0, initial_distance=None):
        """
        Simulate the motion of two cells using the currently selected potential model.
        We will add damping if KV model is selected.
        """
        if initial_distance is None:
            initial_distance = self.initial_distance

        plt.close('all')
        clear_output(wait=True)

        dt = time_step
        T = 100
        N = int(T / dt)
        time = np.linspace(0, T, N + 1)

        d1 = dt * 1.5
        d2 = dt * (-0.5)

        x1 = np.zeros(N + 1)
        x2 = np.zeros(N + 1)
        v1 = np.zeros(N + 1)
        v2 = np.zeros(N + 1)
        V = np.zeros(N + 1)
        d_1 = np.zeros(N + 1)
        d_2 = np.zeros(N + 1)
        distances = np.zeros(N + 1)

        x1[0] = 0.0
        x2[0] = initial_distance
        v1[0] = initial_velocity
        v2[0] = -initial_velocity

        for n in range(N):
            d_1[n] = x1[n] - x2[n]
            d_2[n] = x2[n] - x1[n]
            distance = abs(d_1[n])
            distances[n] = distance

            # Get current potential
            V_n = self.get_potential(distance)

            # Compute elastic force: For the K-V model, force = -dU/dd = -k*(d - d_eq)
            # For others, force is derived from the given potential.
            # Currently, in the code, we are using d_1[n]*V_n as a force approximation, but let's make it consistent:
            # The original code used V_n directly in velocity updates. We'll keep the same logic for now.

            # If KV model is selected, add damping force:
            # Damping force: F_damp = -eta * (v1 - v2) (projected along the line)
            # Relative velocity:
            rel_vel = (v1[n] - v2[n])
            direction = np.sign(d_1[n]) if d_1[n] != 0 else 1.0
            damp_force = 0.0
            if self.potential_model == "kv":
                print("Using kv model")
                # Elastic force from potential derivative: F_elastic = -dU/dd = -k*(d - d_eq)
                d_eq = self.kv_rest_length
                k_spring = self.kv_spring_constant
                F_elastic = -k_spring * (distance - d_eq) * direction
                # Damping force: F_damp = -eta * rel_vel
                eta = self.kv_dissipation_rate
                F_damp = -eta * rel_vel * direction
                print("F_elastic: ", F_elastic)
                # Total force on cell 1: (F_elastic + F_damp)
                # Total force on cell 2: -(F_elastic + F_damp)
                # We'll update velocities with these forces instead of using V_n directly.
                v1[n + 1] = v1[n] + (F_elastic + F_damp) * dt
                v2[n + 1] = v2[n] - (F_elastic + F_damp) * dt
            else:
                # Keep original approach for other potentials:
                # Note: This is a simplification. In a more accurate model, you'd derive force from potential properly.
                v1[n + 1] = v1[n] + d_1[n] * V_n
                v2[n + 1] = v2[n] + d_2[n] * V_n

            # Update positions (Adams-Bashforth)
            x1[n + 1] = x1[n] + d1 * v1[n + 1] + d2 * v1[n]
            x2[n + 1] = x2[n] + d1 * v2[n + 1] + d2 * v2[n]

            V[n] = V_n

        # Final step evaluation
        d_1[N] = x1[N] - x2[N]
        d_2[N] = x2[N] - x1[N]
        distance = abs(d_1[N])
        distances[N] = distance
        V_N = self.get_potential(distance)
        V[N] = V_N

        self.plot_results(distances, V, time, initial_distance)

    def plot_results(self, d, V, time, initial_distance):
        """
        Plot the results of the motion simulation under the chosen potential model.
        """
        d_vals = np.linspace(0, initial_distance, 1000)
        total_potential = []
        adhesion_potential = []
        repulsion_potential = []
        if self.potential_model == "morse":
            for elem in d_vals:
                potential = self.get_potential(elem)
                total_potential.append(potential)
        elif self.potential_model == "original":
            for elem in d_vals:
                potential = self.get_potential(elem)
                total_potential.append(potential)
        elif self.potential_model == "kv":
            for elem in d_vals:
                potential = self.get_potential(elem)
                total_potential.append(potential)

        fig, axs = plt.subplots(2, 1, figsize=(10, 10))

        axs[0].plot(d_vals, total_potential, label='Potential Function')
        axs[0].plot(d, V, 'ro-', label='Simulation Steps')
        axs[0].set_xlabel('Distance (d)')
        axs[0].set_ylabel('Potential V(d)')
        title = 'Motion of Cells Under {} Potential'.format(self.potential_model.capitalize())
        axs[0].set_title(title)
        axs[0].legend()
        axs[0].grid(True)

        axs[1].plot(time, d, 'b-', label='Distance between Cells')

        axs[1].axhline(y=(self._r1 + self._r2), color='green', linestyle='-',
                       label='R1 + R2 (Cells Just Touching)')
        if(self.potential_model == "original"):
            axs[1].axhline(y=(self._c1_relative_maximum_adhesion_distance + self._c2_relative_maximum_adhesion_distance),
                        color='red', linestyle='-', label='MAX ADHESION DISTANCE')
        else:
            axs[1].axhline(y=self._r_eq,
                        color='red', linestyle='-', label='R equilibirum')
        axs[1].set_xlabel('Time (t)')
        axs[1].set_ylabel('Distance (d)')
        axs[1].set_title('Distance Between Cells Over Time')
        axs[1].legend()
        axs[1].grid(True)

        plt.tight_layout()
        plt.show()
