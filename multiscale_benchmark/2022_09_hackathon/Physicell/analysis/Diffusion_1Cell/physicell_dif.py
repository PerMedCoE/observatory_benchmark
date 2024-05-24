import sys,os,re,argparse,glob
sys.path.append('./pctk')
from pctk import multicellds
import pandas as pd
from scipy.io import loadmat
from pathlib import Path
import matplotlib.pyplot as plt
from PIL import Image

def generate_microenv_csv(output_folder,csv_out):
    # generate csv of all voxels and their diffusion in each timestep
    files = Path(output_folder).glob('*output*_microenvironment*.mat')
    mcds = multicellds.Settings(output_folder+"/PhysiCell_settings.xml")
    step = mcds.interval
    df_cell = pd.DataFrame(columns = ['x','y','z','vol','diff'])
    i = 0
    for file in sorted(files):
        mat = loadmat(file)
        mat = mat["multiscale_microenvironment"]
        steps = [step*i] * mat.shape[1]
        df_mat = pd.DataFrame(mat.transpose(),columns = ['x','y','z','vol','diff'])
        df_mat["timestep"] = steps
        df_cell= pd.concat([df_cell,df_mat])
        i= i + 1
    return df_cell
    df_cell.to_csv(output_folder+csv_out)
def generate_cell_csv(output_folder):
    # generate csv of all voxels and their diffusion in each timestep
    files = Path(output_folder).glob('*output*_cells.mat')
    mcds = multicellds.Settings(output_folder+"/PhysiCell_settings.xml")
    step = mcds.interval
    df_cell = pd.DataFrame(columns = ['id','internalized_substrates',"total_volume"])
    i = 0
    for file in sorted(files):
        mat = loadmat(file)
        
        mat = mat["cells"]
        steps = [step*i] * mat.shape[1]
        df_mat = pd.DataFrame(mat[[1,68,4]].transpose(),columns = ['id','internalized_substrates',"total_volume"])
        df_mat["timestep"] = steps
        df_cell= pd.concat([df_cell,df_mat])
        i= i + 1
    df_cell.to_csv(output_folder+"/cell_prop.csv")



df1 = pd.read_csv("../../output/diffusion_v1_u12000/microenv_single_diffusion.csv",index_col=0)
df2 = pd.read_csv("../../output/diffusion_v10_u1200/microenv_single_diffusion.csv",index_col=0)
# /home/thalia/BSC/github/Benchmarks/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Physicell/output/diffusion_v500_u2000
df3 = pd.read_csv("../../output/diffusion_v500_u2000/microenv_single_diffusion.csv",index_col=0)
df1 = df1.loc[df1.index == 13]
df2 = df2.loc[df2.index == 13]
df3 = df3.loc[df3.index == 13]
print(df1)
plt.plot(df1['timestep'],df1['diff'],label = 'Physicell',color='green',alpha=0.6)
plt.plot(df2['timestep'],df2['diff'],label = 'Physicell',alpha=0.5,color = 'red')
plt.plot(df3['timestep'],df3['diff'],label = 'Physicell',alpha=0.5,color = 'orange')

plt.xlabel("Time (minutes)")
plt.legend()
plt.title("Density of central voxel")
# plt.savefig("./comp.png",dpi=200)
plt.show()