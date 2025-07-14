import argparse
import numpy as np
import yaml

from computix.utils.parse import parse_tree
from pathlib import Path
from tqdm import tqdm
from xml.etree import ElementTree

# Command line - arguments
parser = argparse.ArgumentParser(
    prog="extract_cell_cycle",
    description="Extracts average volume of cells over time from results."
)

parser.add_argument("RESULTS_DIR",
                    type=Path,
                    nargs='?',
                    default="build",
                    help="Folder where to find the result files. Default: 'build'")

parser.add_argument("-f", "--frames",
                    type=int,
                    default=480,
                    help="Number of frames to use. Default: 480 (corresponds to 48h)")

parser.add_argument("-o", "--output",
                    type=Path,
                    default="results/cell_volume.yaml",
                    help="Output file containing the aggregated data. Default: 'results/cell_volume.yaml'")

# Extract values
args = parser.parse_args()

# Prepare time series with cell volume per cell, per dumbbell and equilbirum target
times = np.zeros((0), dtype=np.float64)
Vs = np.zeros((0), dtype=np.float64)
V_dumbbell = np.zeros((0), dtype=np.float64)
V_eq = np.zeros((0), dtype=np.float64)

# First 48 hours with interval once pre 6 minutes
for frame in tqdm(range(args.frames)):
    with open(args.RESULTS_DIR / f"Universes_{frame:04d}.xml", "r") as f:
        tree = ElementTree.parse(f)
        data = parse_tree(tree.getroot())[0]

        # Volumes and time values
        times = np.append(times, data["t"].values)
        Vs = np.append(Vs, np.mean(data["Cells/V"].values))

        # Values per dividing cell
        dividing_cells = data["Dividing cells contacts"]
        if dividing_cells.particle_count > 0:
            V_cells = np.mean(dividing_cells["V_cells"].values)
            V_overlap = np.mean(dividing_cells["V_overlap"].values)
            V_dumbbell = np.append(V_dumbbell, V_cells - V_overlap)

            V_eq = np.append(V_eq, np.mean(dividing_cells["V_eq"].values))
        else:
            # No data provide: NaN
            V_dumbbell = np.append(V_dumbbell, np.nan)
            V_eq = np.append(V_dumbbell, np.nan)

# Complement data of dumbell outside the cell division
mask = np.isnan(V_dumbbell)
V_dumbbell[mask] = Vs[mask]

# Prepare output
# Convert:
#  time: second -> hours
#  volumes: m^3 -> um^3
data = {"time": {"values": (times / 3600.).tolist(),
                 "unit": "h"},
        "volume_per_child_cell": {"values": (Vs / 1e-18).tolist(),
                                  "unit": "um^3"},
        "volume_per_parent_cell": {"values": (V_dumbbell / 1e-18).tolist(),
                                   "unit": "um^3"}
        }

with open(args.output, "w") as f:
    yaml.dump(data, f)
