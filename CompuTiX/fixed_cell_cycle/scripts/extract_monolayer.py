import argparse
import numpy as np
import yaml

from computix.utils.parse import parse_tree
from pathlib import Path
from tqdm import tqdm
from xml.etree import ElementTree

# Command line - rguments
parser = argparse.ArgumentParser(
    prog="extract_monolayer",
    description="Extracts maximal distance between cells and their number over time from results."
)

parser.add_argument("RESULTS_DIR",
                    type=Path,
                    nargs='?',
                    default="build",
                    help="Folder where to find the result files. Default: 'build'")

parser.add_argument("-f", "--frames",
                    type=int,
                    default=6480,
                    help="Number of frames to use. Default: 6720 (corresponds to 28d)")

parser.add_argument("-s", "--spacing",
                    type=int,
                    default=10,
                    help="Takes every N-th frame. Default: 10 (corresponds to 1h)")

parser.add_argument("-o", "--output",
                    type=Path,
                    default="results/monolayer.yaml",
                    help="Output file containing the aggregated data. Default: 'results/monolayer.yaml'")

# Extract values
args = parser.parse_args()

# Prepare time series with cell volume per cell, per dumbbell and equilbirum target
times = np.zeros((0), dtype=np.float64)
rs = np.zeros((0), dtype=np.float64)
Ns = np.zeros((0), dtype=np.int64)

# First 48 hours with interval once pre 6 minutes
for frame in tqdm(range(0, args.frames, args.spacing)):
    with open(args.RESULTS_DIR / f"Universes_{frame:04d}.xml", "r") as f:
        tree = ElementTree.parse(f)
        data = parse_tree(tree.getroot())[0]

        # Positions over time
        times = np.append(times, data["t"].values)
        xs = data["Cells/x"].values

        # Take 50% furthest cells from center of mass from system size of 512 cells
        N, _ = xs.shape
        K = N // 2 if N > 512 else min(N, 256)

        xc = np.mean(xs, axis=0)
        ds = np.linalg.norm(xs - xc, axis=1)
        indices = np.argsort(ds)[-K:]

        xs = xs[indices]

        # Expand to matrix
        ones = np.ones(K, dtype=np.float64)
        x_matr = np.einsum("i, jk -> ijk", ones, xs)

        # ... and compude distance matrix
        dx = np.transpose(x_matr, axes=(1, 0, 2)) - x_matr
        dx = np.sqrt(np.einsum("ijk, ijk -> ij", dx, dx))

        rs = np.append(rs, dx.max())
        Ns = np.append(Ns, N)

# Prepare output
# Convert:
#  time: second -> hours
#  dimater: m -> um
data = {"time": {"values": (times / 3600.).tolist(),
                 "unit": "h"},
        "d": {"values": (rs / 1e-6).tolist(),
              "unit": "um"},
        "N": {"values": Ns.tolist(),
              "unit": 1}
        }

with open(args.output, "w") as f:
    yaml.dump(data, f)
