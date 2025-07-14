import argparse
import numpy as np
import pandas as pd

from pathlib import Path
from scipy.optimize import least_squares


def logistic(t, V_inf, tau, t0):
    """
    Logistic curve

    Parameters:
     t - time
     V_inf - maximal volume
     t0 - time offset
     tau - growth rate
    """
    return V_inf / (1. + np.exp(- (t - t0)/tau))


# Command line - rguments
parser = argparse.ArgumentParser(
    prog="fit_cell_cycle.py",
    description="Fits the parameters of the logistic growth."
)

parser.add_argument("GROWTH_DATA",
                    type=Path,
                    nargs='?',
                    default="data/cell_cycle.csv",
                    help="Source data for the cell growth. Default: 'data/cell_cycle.csv'")

parser.add_argument("-t", "--total-growth-time",
                    type=float,
                    default=9.,
                    help="The growth period in hours. Default: 9 hours.")

parser.add_argument("-s", "--growth-start-time",
                    type=float,
                    default=7.,
                    help="Time when the growth starts in hours. Default: 7 hours.")

parser.add_argument("--svg",
                    nargs='?',
                    const="figures/cell_cycle_fit.svg",
                    default=None,
                    help="File to which the figure with comparison will be stored. Optional. Default argument: 'figures/cell_cycle_fit.svg'")

parser.add_argument("-o", "--output",
                    nargs='?',
                    const="results/cell_cycle_parameters.yaml",
                    default=None,
                    help="Output file containing the fitted parameters of the growth curve. Optional. Default argument: 'result/cell_cycle_parameters.yaml'")

# Extract values
args = parser.parse_args()


# Load cell cycle
with open(args.GROWTH_DATA, "r") as f:
    df = pd.read_csv(f, header=0)

# Extract base level and set duration
V_init = df.query("Phase == 'G0/G1'")["total_volume (um^3)"][0]
dt = args.total_growth_time * 60.
t_A = args.growth_start_time * 60.
t_B = t_A + dt


def partial_logistic(t, tau):
    """
    Partially solved logistic.
    Such that the growth period is fixed."
    """
    V_inf = (1. - np.exp(- dt / tau)) / (0.5 - np.exp(- dt / tau)) * V_init
    t_0 = t_A - tau * np.log(1. - 2. * np.exp(- dt / tau))

    return logistic(t, V_inf, tau, t_0)


# Extract growth phase
growth = df.query("Phase == 'S' or Phase == 'G2'")

t = growth["#Time (minutes)"]
V = growth["total_volume (um^3)"]

# Fit
res = least_squares(lambda params: partial_logistic(t, *params) - V,
                    [0.5 * dt],  # Initial guess it half of the growth duration
                    verbose=1)
print(res)
tau = res.x[0]

# Compute remaining parameters
V_inf = (1. - np.exp(- dt / tau)) / (0.5 - np.exp(- dt / tau)) * V_init
t_0 = t_A - tau * np.log(1. - 2. * np.exp(- dt / tau))

print()
print("Growth period:")
print(f"  from (s): {60. * t_A:.2f}")
print(f"  until (s): {60. * t_B:.2f}")
print("Baseline:")
print(f"  V_init (um^3): {V_init:.2f}")
print(f"  r_init (um): {(V_init / (4. / 3. * np.pi))**(1./3.):.2f}")
print("Target:")
print(f"  V_final (um^3): {2.*V_init:.2f}")
print(f"  r_final (um): {(2.*V_init / (4. / 3. * np.pi))**(1./3.):.2f}")
print("Fit:")
print("  Parameters:")
print(f"    V_inf (um^3): {V_inf:.2f}")
print(f"    tau (s): {60.*tau:.2f}")
print(f"    t_0 (s): {60.*t_0:.2f}")
print("  Volumes:")
print(
    f"    V({args.total_growth_time:g}h) (um^3): {logistic(t_A, V_inf, tau, t_0):.2f}")
print(
    f"    V({args.growth_start_time:g}h) (um^3): {logistic(t_B, V_inf, tau, t_0):.2f}")

# Save the result
if args.output is not None:
    import yaml

    results = {"Growth period": {"t_from": {"value": float(60.*t_A),
                                            "unit": "s"},
                                 "t_until": {"value": float(60.*t_B),
                                             "unit": "s"}},
               "Baseline": {"V_init": {"value": float(V_init),
                                       "unit": "um^3"},
                            "r_init": {"value": float((V_init / (4. / 3. * np.pi))**(1./3.)),
                                       "unit": "um"}},
               "Target": {"V_final": {"value": float(2.*V_init),
                                      "unit": "um^3"},
                          "r_final": {"value": float((2.*V_init / (4. / 3. * np.pi))**(1./3.)),
                                      "unit": "um"}},
               "Fit": {"Parameters": {"V_inf": {"value": float(V_inf),
                                 "unit": "um^3"},
                       "tau": {"value": float(60. * tau),
                               "unit": "s"},
                       "t_0": {"value": float(60.*t_0),
                               "unit": "s"}},
                       "Volumes": [{"time": {"value": float(60. * t_A),
                                             "unit": "s"},
                                    "value": float(logistic(t_A, V_inf, tau, t_0)),
                                    "unit": "um^3"},
                                   {"time": {"value": float(60. * t_B),
                                             "unit": "s"},
                                    "value": float(logistic(t_B, V_inf, tau, t_0)),
                                    "unit": "um^3"}]}}

    with open(Path(args.output), "w") as f:
        yaml.dump(results, f)

# Plot the data
if args.svg is not None:
    # Import only when needed
    from matplotlib import pyplot as plt

    t_growth = np.linspace(t_A, t_B,
                           endpoint=True,
                           dtype=np.float64,
                           num=int(dt // 6.) + 1  # Every 6 minutes
                           )

    plt.plot(t_growth, logistic(t_growth, V_inf, tau, t_0), label="Fit")
    plt.plot(df["#Time (minutes)"], df["total_volume (um^3)"], label="Data")
    plt.xlabel(r"$t \; [\mathrm{min}]$")
    plt.ylabel(r"$V \; [\mathrm{\mu m}^3]$")
    plt.legend(frameon=False)
    plt.savefig(Path(args.svg))
