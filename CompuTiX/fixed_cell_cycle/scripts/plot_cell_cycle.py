import argparse
import numpy as np
import yaml
import pandas as pd

from matplotlib import pyplot as plt
from pathlib import Path

# Command line - arguments
parser = argparse.ArgumentParser(
    prog="plot_cell_cycle",
    description="Compare experimental data with simulation for cell cycle."
)


parser.add_argument("-d", "--data",
                    type=Path,
                    default="data/cell_cycle.csv",
                    help="Input file containing the prescribed cell growth. Default: 'data/cell_cycle.csv'")

parser.add_argument("-r", "--results",
                    type=Path,
                    default="results/cell_volume.yaml",
                    help="Input file containing the aggregated results. Default: 'results/cell_volume.yaml'")

parser.add_argument("-o", "--output",
                    type=Path,
                    default="figures/cell_volume.svg",
                    help="Output file where figure will be saved.")

# Extract values
args = parser.parse_args()

# Load data for cell cycle
with open(args.data, "r") as f:
    df = pd.read_csv(f, header=0)

t_data = df["#Time (minutes)"] / 60.  # To hours
V_data = df["total_volume (um^3)"]
V0_data = V_data.iloc[0]

# Load results
with open(args.results, "r") as f:
    results = yaml.safe_load(f)

t_results = np.array(results["time"]["values"])
V_child_results = np.array(results["volume_per_child_cell"]["values"])
V_parent_results = np.array(results["volume_per_parent_cell"]["values"])
V0_parent_results = V_parent_results[0]

plt.plot(t_results, 100. * V_parent_results / V0_parent_results,
         label=r"$V_\text{parent}$",
         color="tab:blue")
plt.plot(t_results, 100. * V_child_results / V0_parent_results, "--",
         label=r"$V_\text{child}$",
         color="tab:blue")
plt.plot(t_data, 100. * V_data / V0_data, ".",
         label="Data",
         color="black")

plt.xlabel(r"$t \; [\mathrm{h}]$")
plt.ylabel(r"$\frac{V}{V_0} \; [\%]$")

plt.legend(loc="upper left", frameon=False)
plt.savefig(args.output)
