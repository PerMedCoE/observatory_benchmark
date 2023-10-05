# from src.pctk import MultiCellDS
from scipy.io import loadmat
import os
from glob import glob
import pandas as pd
from pathlib import Path
output_folder="/home/thalia/BSC/mounted/cell_cycle/output_unit_test7/"

    # mat = loadmat(f)
    # print(mat)
    # break
# mcds = MultiCellDS(output_folder=output_folder)
files = Path(output_folder).glob('*output*cells*.mat')
list_of_dicts = []
time = 0
timestep = 60
for file in sorted(files):
      
    cells = {}
    mat = loadmat(file)
    mat = mat["cells"]
    for i in range(0,mat.shape[1]):
        cell_dict = {}
        cell_dict['dt'] = time*timestep
        cell_dict['id'] = int(mat[0,i])
        cell_dict['total_volume'] = mat[4,i]
        cell_dict['current_phase'] = mat[7,i]
        print(cell_dict)
        list_of_dicts.append(cell_dict)
    time =time+1


for l in list_of_dicts:
    print(l)
df_cell = pd.DataFrame(list_of_dicts)
df_cell.to_csv("/home/thalia/BSC/mounted/cell_cycle/output_unit_test7/cell_volumes_1.6.csv")


# mat = loadmat('/home/bscuser/BSC/unittestscellcycle/output_unit_test7/output00000048_cells.mat')
# print(mat["cells"])