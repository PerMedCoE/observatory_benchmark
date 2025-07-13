import argparse
import numpy as np
import yaml
import pandas as pd

from matplotlib import pyplot as plt
from pathlib import Path

# Command line - arguments
parser = argparse.ArgumentParser(
    prog="plot_monolayer",
    description="Compare experimental data with simulation for monolayer growth."
)


parser.add_argument("-d", "--data",
                    type=Path,
                    default="data/monolayer_growth.csv",
                    help="Input file containing the prescribed cell growth. Default: 'data/monolayer_growth.csv'")

parser.add_argument("-r", "--results",
                    type=Path,
                    default="results/monolayer.yaml",
                    help="Input file containing the aggregated results. Default: 'results/monolayer.yaml'")

parser.add_argument("-o", "--output",
                    type=Path,
                    default="figures/monolayer_growth.svg",
                    help="Output file where figure will be saved.")

# Extract values
args = parser.parse_args()

# Load data for cell cycle
with open(args.data, "r") as f:
    df = pd.read_csv(f, header=0)

t_data = df["Total time (hours)"] / 24.  # To days
d_data = df["Diameter (um)"]

# Load results
with open(args.results, "r") as f:
    results = yaml.safe_load(f)

t_results = np.array(results["time"]["values"]) / 24.  # To days
d_results = np.array(results["d"]["values"])

fig, (ax1, ax2) = plt.subplots(2, 1)

# Whole curve
ax1.plot(t_results, d_results,
         label=r"Simulation")
ax1.plot(t_data, d_data, ".",
         label="Data",
         color="black")

ax1.set_xlabel(r"$t \; [\mathrm{day}]$")
ax1.set_ylabel(r"$d \; [\mathrm{\mu m}]$")

ax1.legend(loc="upper left", frameon=False)

# Difference
# Prepare comparison
t_min = np.min(t_data)
t_max = np.max(t_data)

mask = np.where((t_results >= t_min) & (t_results <= t_max))
t_reduced = t_results[mask]

d_interp = np.interp(t_reduced, t_data, d_data)

ax2.plot(t_reduced, d_results[mask] - d_interp)
ax2.axhline(0, linestyle="dashed", color="black" )

ax2.set_xlabel(r"$t \; [\mathrm{day}]$")
ax2.set_ylabel(r"$\Delta d \; [\mathrm{\mu m}]$")

plt.savefig(args.output)
