# unit test 1 
import matplotlib.pyplot as plt
from src.pctk import multicellds
import pandas as pd
from scipy.io import loadmat
from pathlib import Path
from glob import glob
import numpy as np
# save microenv data in a csv 
# output_folder="/home/bscuser/BSC/Benchmarks/PhysicellBenchmarks/PhysiCell/PhysiCell/output_unit_test1/"
# # generate csv of all voxels and their diffusion in each timestep
# files = Path(output_folder).glob('*output*_microenvironment*.mat')
# mcds = multicellds.Settings(output_folder+"ABM_unit_test1_3D.xml")
# step = mcds.interval
# # list_of_dicts = []
# df_cell = pd.DataFrame(columns = ['x','y','z','vol','diff'])
# i = 0
# for file in sorted(files):
#     # bring me the fist cell that is not necrotc
#     # i want of each timepoint get cell types == default
#     mat = loadmat(file)
#     mat = mat["multiscale_microenvironment"]
#     steps = [step*i] * mat.shape[1]
#     # list_of_dicts.append(mat)
#     df_mat = pd.DataFrame(mat.transpose(),columns = ['x','y','z','vol','diff'])
#     df_mat["timestep"] = steps
#     df_cell= df_cell.append(df_mat,ignore_index=True)
#     i= i + 1

# df_cell.to_csv(str(output_folder)+"/microenv_data.csv")


# file="//home/thalia/BSC/mounted/new_physicell/output_unit_test1/microenv_data.csv"
file = '/home/thalia/BSC/mounted/new_physicell/output_unit_test2/microenv_data.csv'
# get volume where its not 
# bd_file = '/home/thalia/BSC/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_diffusion/marenostrum_results/concentration.csv'
bd_file = '/home/thalia/BSC/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_diffusion_1k/marenostrum_results/concentration_all.csv'


fig, ax = plt.subplots()

pc_df = pd.read_csv(file,index_col=0)
print(len(pc_df['diff']))
data_vox = [pc_df['diff'][i]/602.2 for i in range(13,27027,27)]
data_dt = [pc_df['timestep'][i] for i in range(13,27027,27)]
bd_df = pd.read_csv(bd_file,header = None)
bd_data_dt = bd_df[0]*0.01
bd_data_vox = bd_df[14]
# bd_data_vox[0]  = 0
# for dt,idx in pc_df.groupby(['dt']).groups.items():

    
# ax.set(xlabel='t', ylabel='Diffusion',title="Diffusion 1 cell")
plt.xlabel(xlabel="Time (mins)",fontsize=12,color = '#262626')
plt.ylabel(ylabel="Concentration central voxel (um)",fontsize=12,color = '#262626')
plt.title(label = 'Diffusion 1 cell',color = '#262626')

plt.plot(data_dt,data_vox,label = "Physicell",color = 'green')
plt.plot(bd_data_dt,bd_data_vox,label = "Biodynamo",color = 'red')
plt.xticks(np.arange(0, 11, 1))
plt.legend()
plt.show()
fig.savefig("/home/thalia/BSC/mounted/new_physicell/output_unit_test1/diffusionvstime.png",dpi=200)