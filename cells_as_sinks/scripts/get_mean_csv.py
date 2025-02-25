import sys
from pathlib import Path
import numpy as np
import pandas as pd
import scipy.io

output_folder = sys.argv[1]
output_folder = output_folder+"/output/"
# step = float(sys.argv[2])
files = Path(output_folder).glob('*output*_microenvironment*.mat')

step = 0.1

output_file = sys.argv[1] + "microenv_many_diffusion.csv"

# Open CSV in write mode first
with open(output_file, 'w') as f:
    # Write header for CSV file
    f.write('dt,diff\n')

    i = 0
    for file in sorted(files):
        mat = scipy.io.loadmat(file)['multiscale_microenvironment']
        mean = np.mean(mat, axis=1, dtype=np.float64)

        # Append the results directly to the CSV
        f.write(f"{step * i},{mean[4]}\n")
        i += 1
