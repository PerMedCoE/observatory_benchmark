# from pctk.multicellds import MultiCellDS
from scipy.io import loadmat
import os
from glob import glob
import pandas as pd
import matplotlib.pyplot as plt

from pathlib import Path
import pandas as pd
from sklearn.decomposition import PCA
# visualize unit test 1 & 2
# output_folder="/home/bscuser/BSC/Benchmarks/PhysicellBenchmarks/PhysiCell/PhysiCell/output_unit_test1/"
# this file has each voxel, its position, for each time stp
# to xo yo zo vol dif 
# t0 x1y1z1 
# synthetic key is timestep and x y z 
# df = pd.read_csv(output_folder+"microenv_data.csv",index_col=["x","y","z","timestep"],usecols=["x","y","z","timestep","diff"])
# print(df.head)

# do a pca for each dt
# visualize unit test 3
# visualize position vs time

output_folder="/home/thalia/BSC/mounted/unittest3/output_unit_test3/position_step.csv"
data_pc = pd.read_csv(output_folder)
data_biod = pd.read_csv("/home/thalia/BSC/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_friction_single/marenostrum_results/positions.csv"
,header = None,sep='\t|,',engine='python')

# # plt.plot(data['x'])
data_pc['dt'] = [round(x,2) for x in data_pc['dt']]
data_biod['dt'] = [x/10 for x in data_biod[0]]

data_biod = data_biod.rename(columns={1: "x", 2: "y", 3: "z"})
# plt.scatter(data_pc['dt'],data_pc['x'],marker = "x",label = 'Physicell')
# plt.scatter(data_biod['dt'], data_biod['x'],marker = "^",label = 'Biodynamo')
# plt.title("Mechanics, movement of a cell, Position vs Time")
# plt.ylabel("Position")
# plt.xlabel("Time (minutes)")
# plt.legend(loc = 'center right')
# # plt.savefig("/home/bscuser/BSC/stats/output_unit_test3/positionvstime.png")
# plt.show()


# plot distance travelled
import math
import numpy as np
def Euclidean_Dist(df1, cols=['x','y']):
    return np.linalg.norm(df1[cols[0]].values - df1[cols][1].values,
                   axis=1)
dt_pc = [data_pc['x'].iloc[x] - data_pc['x'].iloc[x-1] for x in range(1,data_pc.shape[0])]
dt_bd = [data_biod['x'].iloc[x] - data_biod['x'].iloc[x-1] for x in range(1,data_biod.shape[0])]
plt.plot(data_pc['dt'].iloc[1:],dt_pc,label = 'Physicell', color= 'green')
plt.plot(data_biod['dt'].iloc[1:],dt_bd,label = 'Biodynamo',color= 'red')
plt.ylabel(ylabel="Distance moved")
plt.xlabel(xlabel="Time (minutes)")
plt.title("Mechanics, movement of a cell")


plt.legend()
# dt_e_pc = Euclidean_Dist(data_pc)
# dt_e_bd = Euclidean_Dist(data_biod)
# plt.plot(data_pc['dt'].iloc[1:],dt_e_pc,label = 'Physicell')
# plt.plot(data_biod['dt'].iloc[1:],dt_e_bd,label = 'Biodynamo')
plt.savefig("/home/thalia/BSC/mounted/unittest3/output_unit_test3/distancex.png",dpi=200)

plt.show()


