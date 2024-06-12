import sys,os,re,argparse,glob
sys.path.append('./pctk')
from pctk import multicellds
import pandas as pd
from scipy.io import loadmat
from pathlib import Path
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np

def create_parser():
    parser = argparse.ArgumentParser(description="Perform analysis of Physicell 1k Cell diffusion unit test")
    
    parser.add_argument("data_folder", action="store", help="folder were the output data is stored")
    

    parser.add_argument("--csvout", action="store", dest="csv_fname", default="/microenv_many_diffusion.csv",
                        help="File name to store the summary table used for the plot")

    return parser
def point_to_voxel_index(group, point):
    centers = group[['x', 'y', 'z']].values
    distances = np.linalg.norm(centers - point, axis=1)
    voxel_index = np.argmin(distances)
    return group.index[voxel_index]


def generate_csv(output_folder,csv_out):
    # generate csv of all voxels and their diffusion in each timestep
    files = Path(output_folder).glob('*output*_cells.mat')
    mcds = multicellds.Settings(output_folder+"/PhysiCell_settings.xml")
    step = mcds.interval
    df_cell = pd.DataFrame(columns = ['id','x','y','z'])
    i = 0
    for file in sorted(files):
        mat = loadmat(file)
        # print(mat)
        mat = mat["cells"]
        steps = [round(step*i, 2)] * mat.shape[1]
        df_mat = pd.DataFrame(mat[[0,1,2,3,64,65,68],:].transpose(),columns =  ['id','x','y','z','secretion_rates','uptake_rates','internalized_total_substrates'])
        df_mat["timestep"] = steps
        df_cell= pd.concat([df_cell,df_mat])
        i= i + 1
    df_cell.to_csv(output_folder+csv_out)
    return df_cell

def get_physicell_df(df_cells):

    file = "microenv_many_diffusion.csv"
    df= pd.read_csv(file,index_col=0)
    df['timestep'] = df['timestep'].round(2)

    print(df)
    df = df.assign(
    xmin=df['x'] - 10,
    xmax=df['x'] + 10,
    ymin=df['y'] - 10,
    ymax=df['y'] + 10,
    zmin=df['z'] - 10,
    zmax=df['z'] + 10)
    cells_grouped_by_timestep = df_cells.groupby("timestep")
    voxels_grouped_by_timestep = df.groupby("timestep")
    index_dic = {}
    df_mean = pd.DataFrame(columns=['timestep', 'diff'])
    for t , gr in cells_grouped_by_timestep:
        indexes = []
        vox_t = voxels_grouped_by_timestep.get_group(t)
        for _,cell in gr.iterrows():
            index = vox_t[(cell['x'] >= vox_t['xmin']) & (cell['x'] <= vox_t['xmax']) &
                      (cell['y'] >= vox_t['ymin']) & (cell['y'] <= vox_t['ymax']) &
                      (cell['z'] >= vox_t['zmin']) & (cell['z'] <= vox_t['zmax'])].index
            indexes.append(index.values[0])
        selected_rows = vox_t.loc[indexes]
        average_diff = selected_rows['diff'].mean()
        df_mean = df_mean.append({'timestep': t, 'diff': average_diff}, ignore_index=True)
    df_mean.to_csv("mean_diff_of_sinks.csv")
        # index_dic[t] = indexes
    
    

if __name__ == '__main__':
    
    parser = create_parser()
    args = parser.parse_args()
    data_folder = args.data_folder
    csv_fname = args.csv_fname
    df_cells = generate_csv(data_folder,csv_fname)
    get_physicell_df(df_cells)
