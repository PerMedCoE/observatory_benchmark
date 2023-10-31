import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path
import glob,argparse
from PIL import Image
import os,re

def create_parser():
    parser = argparse.ArgumentParser(description="Perform analysis of Biodynamo Diffusion of one cell as sink")
    
    parser.add_argument("--data_folder", action="store", dest = "data_folder",help="folder were the output data is stored",default="results/")
    parser.add_argument("--csvout", action="store", dest="csv_fname", default="concentration.csv",
                        help="File name to store the summary table used for the plot")

    return parser
def get_key(fp):
    filename = os.path.splitext(os.path.basename(fp))[0]
    # int_part = filename.split("_")[1]
    int_part =  re.findall(r'\d+', filename)[0]
    return int(int_part)
def create_gif(output_folder,csv_fname):

    df = pd.read_csv(data_folder+csv_fname,header=None,index_col=0)
    df= df*602.2
    print(df)
    x=[]
    y=[]
    z=[]
    for xi in [-20,0,20]:
        for yi in [-20,0,20]:
            for zi in [-20,0,20]:
                x.append(xi)
                y.append(yi)
                z.append(zi)
    # print(len(x))
    global_min = df.values.min()
    global_max = df.values.max()
    for index, row  in df.iterrows():
        if index%10==0:
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            # index = timestep
            # column = voxel id
            # # Add voxels to the plot
            sc = ax.scatter(x, y, z, c=row, cmap='jet',vmin=global_min, vmax=global_max)
            cbar = fig.colorbar(sc,shrink=0.7)

            # # Set the axis labels
            ax.set_xlabel('x')
            ax.set_ylabel('y')

            plt.title("Diffusion of molecules, one cell as sink: BioDynamo Timestep:: "+f'{index:.2f}')
            plt.savefig(output_folder+"/diff_timepoint"+str(int(index))+".png")
            plt.close()

# now generate gif

    frames = [Image.open(image) for image in sorted(glob.glob(f"{output_folder}/*.png"),key=get_key)]

    frame_one = frames[0]
    frame_one.save("single_diffusion.gif", format="GIF", append_images=frames,
                save_all=True, duration=100, loop=0)
if __name__ == '__main__':
    
    parser = create_parser()
    args = parser.parse_args()
    data_folder = args.data_folder
    csv_fname = args.csv_fname
    create_gif(data_folder,csv_fname)

