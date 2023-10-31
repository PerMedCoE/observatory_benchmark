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
    parser = argparse.ArgumentParser(description="Perform analysis of TiSim Diffusion of two cells pushing")
    
    parser.add_argument("--data_folder", action="store", dest = "data_folder",help="folder were the output data is stored",default="results/")
    parser.add_argument("--csvout", action="store", dest="csv_fname", default="positions.csv",
                        help="File name to store the summary table used for the plot")


    return parser

def generate_pngs(data_folder,csv_fname):
    df = pd.read_csv(data_folder+csv_fname,header = None,engine='python').T
    # Create a 3D scatter plot
    for index,row in df.iterrows():
        fig = plt.figure()
        ax = fig.add_subplot(111)
        # Add voxels to the plot
        circle1b = plt.Circle((row[0], 0),0.3)
        circle2b = plt.Circle((row[1],0),0.3)
        # Set the axis labels
        ax.set_aspect( 1 )
        ax.add_artist( circle1b)
        # ax.add_artist( circle1b )
        ax.add_artist( circle2b )
        # ax.add_artist( circle2b )
        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_xlim([-5.0, 5.0])
        ax.set_ylim([-5.0, 5.0])
        # Show the plot
        num_ite = index
        plt.title("TiSim Two cells pushing Timestep: "f"{index:.1f}""")
        plt.legend()
        plt.savefig(data_folder+"/positions_timepoint"+str(int(num_ite))+".png")
        plt.close()
def get_key(fp):
    filename = os.path.splitext(os.path.basename(fp))[0]
    int_part =  re.findall(r'\d+', filename)[0]
    return int(int_part)

def generate_gif(output_folder,csv_out):
    generate_pngs(output_folder,csv_out)
    frames = [Image.open(image) for image in sorted(glob.glob(f"{output_folder}/*.png"),key=get_key)]

    frame_one = frames[0]
    frame_one.save("TiSim_two_cell_pushing.gif", format="GIF", append_images=frames,
               save_all=True, duration=200, loop=0)


if __name__ == '__main__':
    
    parser = create_parser()
    args = parser.parse_args()
    data_folder = args.data_folder
    csv_fname = args.csv_fname
    generate_gif(data_folder,csv_fname)