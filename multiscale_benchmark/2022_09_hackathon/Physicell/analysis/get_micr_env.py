# unit test 1 
import matplotlib.pyplot as plt
from src.pctk import multicellds
import pandas as pd
from scipy.io import loadmat
from pathlib import Path
from glob import glob

# save microenv data in a csv 
output_folder="/home/thalia/BSC/mounted/new_physicell/output_unit_test2/"
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
    print(steps)
    # list_of_dicts.append(mat)
    df_mat = pd.DataFrame(mat.transpose(),columns = ['x','y','z','vol','diff'])
    df_mat["timestep"] = steps
    df_cell= pd.concat([df_cell,df_mat],ignore_index=True)
    i= i + 1
    # print(df_cell)
    
# print(i)
df_cell.to_csv(str(output_folder)+"/microenv_data.csv")
# for dt,idx in df_cell.groupby(['timestep']).groups.items():
#     # for i in idx.values:
#     print(dt)