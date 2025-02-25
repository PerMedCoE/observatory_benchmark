import sys
from pathlib import Path
import numpy as np
import pandas as pd
import scipy.io

output_folder = sys.argv[1]
output_folder = output_folder+"/output/"
# step = float(sys.argv[2])
files = Path(output_folder).glob('*output*_cells.mat')

step = 0.1
output_file = sys.argv[1] + "internalized_substrates.csv"
# Open CSV in write mode first
# with open(output_file, 'w') as f:
#     # Write header for CSV file
#     f.write('dt,ID,x,y,z,internalized_total_substrates,diff\n')

i = 0
for file in sorted(files):
    print(file)
    mat = scipy.io.loadmat(file)['cells']
    print(mat.shape)
    exit()
    # Append the results directly to the CSV
    # f.write(f"{step * i},{mean[4]}\n")
    i += 1
