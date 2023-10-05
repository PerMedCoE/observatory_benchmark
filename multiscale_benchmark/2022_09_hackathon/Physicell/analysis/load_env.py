from src.pctk import multicellds
from scipy.io import loadmat
import pandas as pd
from pathlib import Path
# from pctk import MultiCellDS,Settings

from scipy.io import loadmat
import os
from glob import glob

output_folder="/home/thalia/BSC/mounted/physicell/output_unit_test2/"
# generate csv of all voxels and their diffusion in each timestep
files = Path(output_folder).glob('*output*_microenvironment*.mat')
mcds = multicellds.Settings(output_folder+"ABM_unit_test2_3D.xml")
step = mcds.interval
print(step)
# list_of_dicts = []
df_cell = pd.DataFrame(columns = ['x','y','z','vol','diff'])
i = 0
for file in sorted(files):
    # bring me the fist cell that is not necrotc
    # i want of each timepoint get cell types == default
    mat = loadmat(file)
    mat = mat["multiscale_microenvironment"]
    steps = [step*i] * mat.shape[1]
    print(mat.shape)
    df_mat = pd.DataFrame(mat.transpose(),columns = ['x','y','z','vol','diff'])
    df_mat["timestep"] = steps
    df_mat = pd.concat([df_cell,df_mat])
    print("|||||||||||||||||||")
    for x in df_mat['vol'].unique():
        print(x)
    print("|||||||||||||||||||")
    # df_cell= df_cell.append(df_mat,ignore_index=True)
    i= i + 1

df_cell.to_csv(str(output_folder)+"/microenv_data.csv")