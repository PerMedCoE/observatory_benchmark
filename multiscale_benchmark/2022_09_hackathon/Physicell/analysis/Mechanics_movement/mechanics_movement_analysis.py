import sys,os,re,argparse,glob
sys.path.append('./pctk')
from pctk import multicellds
import pandas as pd
from scipy.io import loadmat
from pathlib import Path
import matplotlib.pyplot as plt
from PIL import Image
from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt

def create_parser():
    parser = argparse.ArgumentParser(description="Perform analysis of Physicell Mechanics (Friction) Movement of a cell")
    
    parser.add_argument("--data-folder", action="store", dest = "data_folder",help="Path to the Physicell olutput folder for mechanics movement",
                        default="../../output/mechanics_movement")
    
    parser.add_argument("--gifout", action="store", dest="gif_out", default="physicell_cell_positions.gif",
                        help="File name to save the gif")
                        
    parser.add_argument("--csvout", action="store", dest="csv_fname", default="cell_position_time.csv",
                        help="File name to store the summary table used for the plot")
    parser.add_argument("-g","--generate-gif", action="store_true")
    parser.add_argument("-c","--generate-csv", action="store_true")
    return parser


def generate_position_timestep_csv(output_folder,csv_fname):
    files = Path(output_folder).glob('*output*_cells.mat')
    mcds = multicellds.Settings(output_folder+"/PhysiCell_settings.xml")
    df_cell = pd.DataFrame(columns = ['x','y','z',"dt"])
    interval = mcds.interval
    i=0
    for file in sorted(files):
        mat = loadmat(file)
        mat=mat['cells'][[0,1,2,3,53,54,55,56]]
        print(mat)
        df_mat = pd.DataFrame(mat.transpose(),columns = ['id','x','y','z','v1','mbx','mby','mbz'])
        
        df_mat['dt'] = i
        df_cell= pd.concat([df_mat,df_cell],ignore_index=True)
        i=i+interval
    
    df_cell.to_csv(output_folder+"/"+csv_fname)
    print(df_cell)
    return

def generate_gif(output_folder,csv_fname,gif):
    def update(frame):
        ax.clear()
        ax.set_xlim([-5.0, 20.0])
        ax.set_ylim([-5.0, 15.0])
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.scatter(data.iloc[frame]['x'], data.iloc[frame]['y'], c='b', marker='o')
        ax.set_title("PhysiCell Movement of a cell (Friction) Timepoint: " + str(frame))
        return ax
    data = pd.read_csv(output_folder+"/"+csv_fname,index_col=0).sort_values(by=['dt']).reset_index(drop=True)
    print(data)
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.set_xlim([-5.0, 20.0])
    ax.set_ylim([-15.0, 15.0])
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    # Define a function that will update the plot for each frame of the animation

    # Create the animation
    anim = FuncAnimation(fig, update, frames=len(data), interval=0.1)

    # Save the animation as a GIF
    anim.save(gif, writer='Pillow')



if __name__ == '__main__':
    
    parser = create_parser()
    args = parser.parse_args()
    data_folder = args.data_folder
    csv_fname = args.csv_fname
    gif_fname = args.gif_out
    # generate_position_timestep_csv(data_folder,csv_fname)
    # generate_gif(data_folder,csv_fname,gif_fname)
    print(args.generate_csv,args.generate_gif)
    if args.generate_csv:
        generate_position_timestep_csv(data_folder,csv_fname)
    if args.generate_gif:
        generate_gif(data_folder,csv_fname,gif_fname)