import argparse
import numpy as np
import yaml

from computix.utils.parse import parse_tree
from scipy.spatial import ConvexHull
from scipy.spatial.distance import cdist
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
                    default=672,
                    help="Number of frames to use. Default: 672 (corresponds to 28d)")

parser.add_argument("-s", "--spacing",
                    type=int,
                    default=1,
                    help="Takes every N-th frame. Default: 1 (corresponds to 1h)")

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
    file = args.RESULTS_DIR / f"Universes_{frame:04d}.xml"
    if not file.exists():
        continue

    with open(file, "r") as f:
        tree = ElementTree.parse(f)
        data = parse_tree(tree.getroot())[0]

        # Positions over time
        times = np.append(times, data["t"].values)
        xs = data["Cells/x"].values

        # Number of data points
        N, _ = xs.shape 
        if N > 3 : 
            # Point has to be part of the convex hull 
            # Take the plane
            hull = ConvexHull(xs[:,1:])

            # Extract the points forming the hull
            hullpoints = xs[hull.vertices,:]

            # Naive way of finding the best pair in O(H^2) 
            dx = cdist(hullpoints, hullpoints, metric='euclidean')
        else:
            dx = cdist(xs, xs, metric='euclidean')

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
