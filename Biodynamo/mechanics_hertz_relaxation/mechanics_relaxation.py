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
    parser = argparse.ArgumentParser(description="Perform analysis of Biodynamo Mechanics Two Cells pushing with Hertz model")

    parser.add_argument("--data_folder", action="store", dest = "data_folder",help="folder were the output data is stored",default="results/")
    parser.add_argument("--csvout", action="store", dest="csv_fname", default="positions.csv",
                        help="File name to store the summary table used for the plot")
    parser.add_argument("--multiplot", action="store_true", dest="multiplot", default=False,
                        help="If true, generate a multiplot with all the time points in a single figure")


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
        plt.title("BioDynaMo Two cells relaxation Timestep: "f"{index:.1f}""")
        # plt.legend()
        plt.savefig(data_folder+"/positions_timepoint"+str(num_ite)+".png")
        plt.close()
    ##################### Plot distances
    fig = plt.figure()
    plt.plot(indexes, distances, color='red')
    plt.axhline(y=10, color='black', linestyle='--')
    plt.xlabel('Time (min)')
    plt.ylabel('Cell-Cell distance (µm)')
    plt.title("Distance between the two cell centers across time")
    plt.xlim([0, 180])
    plt.ylim([7.5, 12.5])
    plt.savefig(data_folder+"/distances_vs_time.png")
    plt.close()
    
def get_key(fp):
    filename = os.path.splitext(os.path.basename(fp))[0]
    matches = re.findall(r'[-+]?\d*\.?\d+(?:[eE][-+]?\d+)?', filename)
    if matches:
        # Return the first number as a float to preserve decimal ordering
        return float(matches[0])
    else:
        # Return a default value if no digits are found
        return 0.0
    
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
        frame_one.save("Biodynamo_two_cell_relaxation.gif", format="GIF", append_images=frames[1:],
                    save_all=True, duration=200, loop=0)
    
def plot_multiplot(data_folder,csv_fname):
    # Read data from all folders that start with "results_" and plot in a single figure just the distance vs time
    # Find all folders that start with results_
    result_folders = glob.glob(f"results_*")
    fig = plt.figure()
    colors = ['red','blue','green','orange','purple','brown','pink','gray','olive','cyan']
    # Sort the folders based on the numerical value after "results_" in descending order. So that should be 0.1, 0.01, 0.001, etc.
    result_folders = sorted(result_folders, key=lambda x: float(x.replace("results_","").replace("drag_","").replace("_",".")), reverse=True)
    for index_folder, folder in enumerate(result_folders):
        print("Processing file: ",folder+"/"+csv_fname)
        data_biod = pd.read_csv(folder+"/" + csv_fname,header = None,sep='\t|,',engine='python',index_col=0)
        # print(data_biod)
        distances = []
        indexes = []
        # Create a 3D scatter plot
        for index,row in data_biod.iterrows():
            x1 = row.iloc[0]
            y1 = row.iloc[1]
            x2 = row.iloc[3]
            y2 = row.iloc[4]
            
            # Compute the distance between the two points
            distance = ((x2 - x1)**2 + (y2 - y1)**2)**0.5
            distances.append(distance)
            indexes.append(index)
        ##################### Plot distances
        plt.plot(indexes, distances, color=colors[index_folder], label=folder.replace("results_","").replace("_"," "))
    plt.axhline(y=10, color='black', linestyle='--')
    plt.xlabel('Time (min)')
    plt.ylabel('Cell-Cell distance (µm)')
    plt.title("Distance between the two cell centers across time - Multiplot")
    plt.xlim([0, 180])
    plt.ylim([8.8, 10.2])
    plt.legend()
    plt.savefig("distances_vs_time_multiplot.png")
    plt.close()



if __name__ == '__main__':
    
    parser = create_parser()
    args = parser.parse_args()
    data_folder = args.data_folder
    csv_fname = args.csv_fname
    multiplot = args.multiplot
    if multiplot:
        plot_multiplot(data_folder,csv_fname)
    else:
        generate_gif(data_folder,csv_fname)
    
    