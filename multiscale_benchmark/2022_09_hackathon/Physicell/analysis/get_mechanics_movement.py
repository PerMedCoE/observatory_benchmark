from pathlib import Path
from re import M

from matplotlib.pyplot import step
from src.pctk import multicellds
from scipy.io import loadmat
import pandas as pd
from pathlib import Path
# from pctk import MultiCellDS,Settings

from scipy.io import loadmat
import os
from glob import glob

# position of cell travelled through time
output_folder = "/home/thalia/BSC/NEW_BENCH/Physicell_template/mechanics_movement/"
files = Path(output_folder).glob('*output*_cells.mat')
mcds = multicellds.Settings("/home/thalia/BSC/NEW_BENCH/Physicell_template/mechanics_movement/PhysiCell_settings.xml")
df_cell = pd.DataFrame(columns = ['x','y','z',"dt"])
interval = mcds.interval
print(interval)
i=0
for file in sorted(files):
    mat = loadmat(file)
    mat=mat['cells'][0:4]
    df_mat = pd.DataFrame(mat.transpose(),columns = ['id','x','y','z'])
    df_mat['dt'] = i
    # print("----")
    df_cell= pd.concat([df_mat,df_cell],ignore_index=True)
    i=i+interval
df_cell.to_csv(output_folder+"position_step.csv")