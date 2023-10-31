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
    parser = argparse.ArgumentParser(description="Perform analysis of Biodynamo Mechanics (Friction) Movement of a cell")
    
    parser.add_argument("--data_folder", action="store", dest = "data_folder",help="folder were the output data is stored",default="results/")
    parser.add_argument("--csvout", action="store", dest="csv_fname", default="positions.csv",
                        help="File name to store the summary table used for the plot")
    return parser



def generate_gif(output_folder,csv_fname):
    def update(frame):
        ax.clear()
        ax.set_xlim([-15.0, 15.0])
        ax.set_ylim([-15.0, 15.0])
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.scatter(data.iloc[frame]['x'], data.iloc[frame]['y'], c='b', marker='o')
        ax.set_title("Biodynamo Movement of a cell (Friction) Timepoint: " + str(frame))
        return ax
    data = pd.read_csv(output_folder+"/"+csv_fname,header = None,sep='\t|,',engine='python').rename(columns={1: "x", 2: "y", 3: "z"})
    print(data)
    # .sort_values(by=['dt']).reset_index(drop=True)
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.set_xlim([-15.0, 15.0])
    ax.set_ylim([-15.0, 15.0])
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    # Define a function that will update the plot for each frame of the animation

    # Create the animation
    anim = FuncAnimation(fig, update, frames=len(data), interval=0.1)

    # Save the animation as a GIF
    anim.save("biodynamo_cell_positions.gif", writer='Pillow')



if __name__ == '__main__':
    
    parser = create_parser()
    args = parser.parse_args()
    data_folder = args.data_folder
    csv_fname = args.csv_fname
    # generate_position_timestep_csv(data_folder,csv_fname)
    # generate_gif(data_folder,csv_fname,gif_fname)
    generate_gif(data_folder,csv_fname)