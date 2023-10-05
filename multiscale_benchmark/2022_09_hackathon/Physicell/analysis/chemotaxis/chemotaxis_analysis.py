import sys,os,re,argparse,glob
sys.path.append('./pctk')
from pctk import multicellds
import pandas as pd
from scipy.io import loadmat
from pathlib import Path
from PIL import Image
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import numpy as np
def create_parser():
    parser = argparse.ArgumentParser(description="Perform analysis of Chemotaxis unit test")
    
    parser.add_argument("data_folder", action="store", help="folder were the output data is stored")
    
    parser.add_argument("--gifout", action="store", dest="gif_out", default="/physicell_cells_positions.gif",
                        help="File name to save the gif")
                        
    parser.add_argument("--csvout", action="store", dest="csv_fname", default="/cells_position_time.csv",
                        help="File name to store the summary table used for the plot")
    parser.add_argument("-g","--generate-gif", action="store_true")
    parser.add_argument("-c","--generate-csv", action="store_true")
    return parser

def generate_position_timestep_csv(data_folder,csv_fname):
    files = Path(data_folder).glob('*output*_cells.mat')
    mcds = multicellds.Settings(data_folder+"/PhysiCell_settings.xml")
    df_cell = pd.DataFrame(columns = ['x','y','z',"dt",'radius'])
    interval = mcds.interval
    i=0
    for file in sorted(files):
        mat = loadmat(file)
        mat=mat['cells'][[0,1,2,3,38]]
        df_mat = pd.DataFrame(mat.transpose(),columns = ['id','x','y','z','radius'])
        df_mat['dt'] = round(i, 1) 
        df_cell= pd.concat([df_mat,df_cell],ignore_index=True)
        i=i+interval
    df_cell = df_cell.sort_values(by=['dt']).reset_index(drop=True)
    df_cell.to_csv(data_folder+"/"+csv_fname)

def generate_trajectory(data_folder,csv_fname):
    # generate plot of first and last position
    df = pd.read_csv(data_folder+"/"+csv_fname,index_col=0)
    p0 = df.loc[df['dt']==0]
    p1 = df.tail(1)
    fig = plt.figure()
    mid = df.iloc[1:-1]
    ax = plt.axes(projection='3d')
    ax.scatter3D(p0['x'], p0['y'], p0['z'] ,color = 'lime',label='Start position')
    ax.scatter3D(mid['x'], mid['y'], mid['z'] ,color = 'limegreen',alpha = 0.3,marker=0)

    ax.scatter3D(p1['x'], p1['y'], p1['z'] ,color = 'green',label='End position')
    plt.title("Chemotaxis, cell trajectory")
    plt.legend()
    plt.show()
    plt.savefig(data_folder+"/cell_trajectory_chemotaxis.png")
    plt.close()

def generate_gif(data_folder,csv_fname,gif_outputs):
    
    # generate plot of first and last position
    df = pd.read_csv(data_folder+"/"+csv_fname,index_col=0)
    n_frames = df.shape[0]
    n_points = df.shape[0]
    x = df['x']
    y = df['y']
    z = df['z']
    dt = df['dt']
    colors = np.random.rand(n_points)
    sizes = 1000 * np.random.rand(n_points)
    fig = plt.figure(figsize=plt.figaspect(0.5))
    ax = fig.add_subplot( projection='3d')
    def update(frame):
        ax.clear()
        ax.scatter(x[:frame], y[:frame],z[:frame],color = 'green', alpha=0.5)
        ax.set_xlim([-10, 41])
        ax.set_ylim([-10, 41])
        ax.set_zlim([-10, 41])
        ax.set_title('Timpeoint {}'.format(dt[frame]))

    ani = animation.FuncAnimation(fig, update, frames=n_frames ,interval=100)

    plt.title("Chemotaxis, cell trajectory")
    plt.legend()
    writer = animation.PillowWriter(fps=1)

    # save the animation as a GIF file
    ani.save(data_folder+"/"+gif_outputs, writer=writer)
    plt.show()
    pass

if __name__ == '__main__':
    
    parser = create_parser()
    args = parser.parse_args()
    data_folder = args.data_folder
    csv_fname = args.csv_fname
    gif_fname = args.gif_out

    print(args.generate_csv,args.generate_gif)
    if args.generate_csv:
        generate_position_timestep_csv(data_folder,csv_fname)
    generate_gif(data_folder,csv_fname,gif_fname)
    # if args.generate_gif:
    #     generate_trajectory(data_folder,csv_fname,gif_fname)