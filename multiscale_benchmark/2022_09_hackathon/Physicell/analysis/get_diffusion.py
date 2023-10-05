# unit test 1 
import sys
sys.path.append('./pctk')
from pctk import multicellds
import pandas as pd
from scipy.io import loadmat
from pathlib import Path


# save microenv data in a csv 
output_folder="/home/thalia/BSC/NEW_BENCH/Physicell_template/single_diffusion_out/"
# generate csv of all voxels and their diffusion in each timestep
files = Path(output_folder).glob('*output*_microenvironment*.mat')
mcds = multicellds.Settings(output_folder+"PhysiCell_settings.xml")
step = mcds.interval
df_cell = pd.DataFrame(columns = ['x','y','z','vol','diff'])
i = 0
for file in sorted(files):
    # bring me the fist cell that is not necrotc
    # i want of each timepoint get cell types == default
    mat = loadmat(file)
    mat = mat["multiscale_microenvironment"]
    steps = [step*i] * mat.shape[1]
    # list_of_dicts.append(mat)
    df_mat = pd.DataFrame(mat.transpose(),columns = ['x','y','z','vol','diff'])
    df_mat["timestep"] = steps
    df_cell= pd.concat([df_cell,df_mat])
    i= i + 1

df_cell.to_csv(output_folder+"coordinates_diffusion.csv")