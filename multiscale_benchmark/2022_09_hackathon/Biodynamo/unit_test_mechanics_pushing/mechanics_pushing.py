import sys,os,re,argparse,glob
sys.path.append('./pctk')
# from pctk import multicellds
import pandas as pd
from scipy.io import loadmat
from pathlib import Path
import matplotlib.pyplot as plt
from PIL import Image
from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt
def create_parser():
    parser = argparse.ArgumentParser(description="Perform analysis of Biodynamo Mechanics Two Cells pushing")

    parser.add_argument("--data_folder", action="store", dest = "data_folder",help="folder were the output data is stored",default="results/")
    parser.add_argument("--csvout", action="store", dest="csv_fname", default="positions.csv",
                        help="File name to store the summary table used for the plot")


    return parser

def generate_pngs(data_folder,csv_fname):
    data_biod = pd.read_csv(data_folder+csv_fname,header = None,sep='\t|,',engine='python',index_col=0)
    print(data_biod)
    distances = []
    indexes = []
    # Create a 3D scatter plot
    for index,row in data_biod.iterrows():
        fig = plt.figure()
        ax = fig.add_subplot(111)
        
        # print(index)
        # Add voxels to the plot
        circle1b = plt.Circle((row.iloc[0], row.iloc[1]),5)
        circle2b = plt.Circle((row.iloc[3],row.iloc[4]),5)
        x1 = row.iloc[0]
        y1 = row.iloc[1]
        x2 = row.iloc[3]
        y2 = row.iloc[4]
        
        # Compute the distance between the two points
        distance = ((x2 - x1)**2 + (y2 - y1)**2)**0.5
        distances.append(distance)
        indexes.append(index)
        # Set the axis labels
        ax.set_aspect( 1 )
        ax.add_artist( circle1b)
        # ax.add_artist( circle1b )
        ax.add_artist( circle2b )
        # ax.add_artist( circle2b )
        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_xlim([-21.0, 21.0])
        ax.set_ylim([-10.0, 11.0])
        # Show the plot
        num_ite = index*100
        plt.title("BiodyNamo Two cells pushing Timestep: "f"{index:.1f}""")
        # plt.legend()
        plt.savefig(data_folder+"/positions_timepoint"+str(int(num_ite))+".png")
        plt.close()
    ##################### Plot distances
    fig = plt.figure()
    plt.plot(indexes, distances, color='red')
    plt.axhline(y=10, color='black', linestyle='--')
    plt.xlabel('Time')
    plt.ylabel('Real distance travelled')
    plt.title("Real distance between the two cells across time")
    plt.xlim([-5, 105])
    plt.ylim([0, 32])
    plt.savefig(data_folder+"/distances_vs_time.png")
    plt.close()
    
def get_key(fp):
    filename = os.path.splitext(os.path.basename(fp))[0]
    matches = re.findall(r'\d+', filename)
    if matches:
        # Return the first sequence of digits as an integer
        return int(matches[0])
    else:
        # Return a default value if no digits are found
        return 0
    
def generate_gif(output_folder, csv_out):
    generate_pngs(output_folder, csv_out)
        
    # List of image file paths sorted by time point
    image_files = sorted(glob.glob(f"{output_folder}/*.png"), key=get_key)
        
    # Open images one by one and append to frames
    frames = []
    for image in image_files:
        with Image.open(image) as img:
            frames.append(img.copy())  # Copy the image to store in memory
        
    # Save the frames as a GIF
    if frames:
        frame_one = frames[0]
        frame_one.save("Biodynamo_two_cell_pushing.gif", format="GIF", append_images=frames[1:],
                    save_all=True, duration=200, loop=0)



if __name__ == '__main__':
    
    parser = create_parser()
    args = parser.parse_args()
    data_folder = args.data_folder
    csv_fname = args.csv_fname
    generate_gif(data_folder,csv_fname)