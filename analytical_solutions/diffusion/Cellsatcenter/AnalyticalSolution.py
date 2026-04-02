from dataclasses import dataclass
import numpy as np

@dataclass
class AnalyticalSolution:
    """
    Class representing analytical solution of diffusion equation with sinks
    
    The initial condition is a constant concentration value c_0 which is also
    the boundary condition.
    Case with multiple point sinks at center.

    Attributes:
        c_0 - initial concentration (also boundary condition)
        D - diffusion coefficient
        L - length of the box
        rate - uptake rate
        x_cells - positions of the cells
        count_modes - number of modes
    """
    c_0: float
    D: float
    L: float
    rate: float
    x_cells: np.ndarray
    count_modes: int

    def eigenvalue(self, i: int, j: int, k: int ) -> float :
        """
        Helper method to compute eigenvalues involved in analytical solution

        Parameters:
            i - the integer corresponding to the mode associated with $x$ coordinate
            j - the integer corresponding to the mode associated with $y$ coordinate
            k - the integer corresponding to the mode associated with $z$ coordinate
        """
        return np.pi**2 * ( (2.*i+1.)**2 + (2.*j+1.)**2 + (2.*k+1.)**2 ) * self.D / self.L**2

    def eigenfunction(self, x : np.ndarray, i: int, j: int, k: int ) -> np.ndarray :
        """
        Helper method to compute eigenfunctions involved in analytical solution

        Parameters:
            x - is the position in space where to compute the eigenfunction
            i - the integer corresponding to the mode associated with $x$ coordinate
            j - the integer corresponding to the mode associated with $y$ coordinate
            k - the integer corresponding to the mode associated with $z$ coordinate
        """
        return (2. / self.L)**1.5\
             * np.cos( (2. * i + 1.) * np.pi * x[0] / self.L )\
             * np.cos( (2. * j + 1.) * np.pi * x[1] / self.L )\
             * np.cos( (2. * k + 1.) * np.pi * x[2] / self.L )\

    def iiint_eigenfunction(self, x : np.ndarray, i: int, j: int, k: int, x_first: float, x_second: float, y_first: float, y_second : float, z_first : float, z_second:float ) -> float :
        """
        Helper method to compute eigenfunctions involved in analytical solution.

        Parameters:
            x - is the position in space where to compute the eigenfunction
            i - the integer corresponding to the mode associated with $x$ coordinate
            j - the integer corresponding to the mode associated with $y$ coordinate
            k - the integer corresponding to the mode associated with $z$ coordinate
            x_first - the minimum bound in the $x$ coordinate
            x_second - the maximum bound in the $x$ coordinate
            y_first - the minimum bound in the $y$ coordinate
            y_second - the maximum bound in the $y$ coordinate
            z_first - the minimum bound in the $z$ coordinate
            z_second - the maximum bound in the $z$ coordinate
        """
        return (2. / self.L)**1.5\
             * self.L / ( (2. * i + 1.) * np.pi ) * ( np.sin( (2. * i + 1.) * np.pi * x_second / self.L ) - np.sin( (2. * i + 1.) * np.pi * x_first / self.L ) )\
             * self.L / ( (2. * j + 1.) * np.pi ) * ( np.sin( (2. * j + 1.) * np.pi * y_second / self.L ) - np.sin( (2. * j + 1.) * np.pi * y_first / self.L ) )\
             * self.L / ( (2. * k + 1.) * np.pi ) * ( np.sin( (2. * k + 1.) * np.pi * z_second / self.L ) - np.sin( (2. * k + 1.) * np.pi * z_first / self.L ) )

    def concentration( self, x: np.ndarray, t: np.ndarray) -> np.ndarray :
        """
        Helper method to integrate eigenfunction on a voxel as position $x$
        with domain $(-x_\text{first}, x_\text{second}) \times (y_\text{first}, y_\text{second})\times (z_\text{first}, z_\text{second})$.

        Parameters:
            x - is the position in space where to compute the concentration
            t - the time when to compute the concentration
        """
        sol = self.c_0
        for i in range( 0, self.count_modes ):
            for j in range( 0, self.count_modes ):
                for k in range( 0, self.count_modes ):
                    v_ijk = self.eigenfunction( i=i, j=j, k=k, x=x )
                    lambda_ijk = self.eigenvalue( i=i, j=j, k=k )
                    for x_cell in self.x_cells:
                        sol -= self.rate * v_ijk * self.eigenfunction( i=i, j=j, k=k, x=x_cell ) * ( 1. - np.exp( -lambda_ijk * t ) ) / lambda_ijk

        return sol

    def amount( self, x: np.ndarray, t: np.ndarray, x_first:float, x_second: float, y_first: float, y_second : float, z_first : float, z_second:float ) -> float:
        """
        Helper method to compute the analytical solution of the amount (integral of concentration on a given volume at a given position).
        The volume over which to integrate is a box.

        Parameters:
            x - is the position in space where to compute the amount
            t - the time when to compute the amount
            x_first - the minimum bound in the $x$ coordinate
            x_second - the maximum bound in the $x$ coordinate
            y_first - the minimum bound in the $y$ coordinate
            y_second - the maximum bound in the $y$ coordinate
            z_first - the minimum bound in the $z$ coordinate
            z_second - the maximum bound in the $z$ coordinate
        """
        V = (x_second - x_first)\
          * (y_second - y_first)\
          * (z_second - z_first)
        sol = self.c_0 * V
        for i in range( 0, self.count_modes ) :
            for j in range( 0, self.count_modes ) :
                for k in range( 0, self.count_modes ) :
                    lambda_ijk = self.eigenvalue( i=i, j=j, k=k )
                    v_ijk_int = self.iiint_eigenfunction( x=x, i=i, j=j, k=k, x_first=x_first, x_second=x_second, y_first=y_first, y_second=y_second, z_first=z_first, z_second=z_second )
                    for x_cell in self.x_cells:
                        sol -= self.rate * v_ijk_int * self.eigenfunction( i=i, j=j, k=k, x=x_cell ) * ( 1. - np.exp( -lambda_ijk * t ) ) / lambda_ijk

        return sol
