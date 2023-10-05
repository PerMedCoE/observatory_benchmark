from pctk.multicellds import MultiCellDS
from scipy.io import loadmat
import os
from glob import glob
import pandas as pd
from pathlib import Path
output_folder="/home/bscuser/BSC/physicell/output_480_1_48"

    # mat = loadmat(f)
    # print(mat)
    # break
# mcds = MultiCellDS(output_folder=output_folder)
files = Path(output_folder).glob('*output*cells*physicell.mat')
i=0
list_of_dicts = []
for file in sorted(files):
    # bring me the fist cell that is not necrotc
    # i want of each timepoint get cell types == default
    cell_dict = {}
    print(file)
    
    mat = loadmat(file)
    mat = mat["cells"]
    print(mat.shape)
    if mat.shape[1] != 0:
        # print(mat)
        cell = mat[:,0]
        cell_dict["id"] = cell[0]
        # print(cell_dict["id"])
        cell_dict["total_volume"] = cell[4]
        # print(cell[4])
        cell_dict["cell_type"] = cell[5]
        list_of_dicts.append(cell_dict)
    i +=1
    if i==49:
        break
    
df_cell = pd.DataFrame(list_of_dicts)
print()
df_cell.to_csv("cell1.csv")