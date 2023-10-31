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
    parser = argparse.ArgumentParser(description="Perform analysis of Chaste Mechanics (Friction) Movement of a cell")
    
    parser.add_argument("--data_folder", action="store", dest = "data_folder",help="folder were the output data is stored",default="results/")
    parser.add_argument("--csvout", action="store", dest="csv_fname", default="node_locations.dat",
                        help="File name to store the summary table used for the plot")
    return parser



def generate_gif(output_folder,csv_fname):
    def update(frame):
        ax.clear()
        ax.set_xlim([-15.0, 15.0])
        ax.set_ylim([-15.0, 15.0])
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.scatter(data.iloc[frame][1], data.iloc[frame][2], c='b', marker='o')
        ax.set_title("Chaste Movement of a cell (Friction) Timepoint: " + str(frame))
        return ax
    data = pd.read_csv(output_folder+"/"+csv_fname,header = None,sep='\t| ',index_col=0)
    print(data)
    # .sort_values(by=['dt']).reset_index(drop=True)
    # exit()
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.set_xlim([-5.0, 5.0])
    ax.set_ylim([-5.0, 5.0])
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    # Define a function that will update the plot for each frame of the animation

    # Create the animation
    anim = FuncAnimation(fig, update, frames=10, interval=0.1)

    # Save the animation as a GIF
    anim.save("Chaste_cell_positions.gif", writer='Pillow')



if __name__ == '__main__':
    
    parser = create_parser()
    args = parser.parse_args()
    data_folder = args.data_folder
    csv_fname = args.csv_fname
    generate_gif(data_folder,csv_fname)