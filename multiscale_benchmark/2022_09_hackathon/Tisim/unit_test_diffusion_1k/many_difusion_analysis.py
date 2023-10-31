import pandas as pd
import matplotlib.pyplot as plt
from PIL import Image
import os,argparse
import glob
import re
def create_parser():
    parser = argparse.ArgumentParser(description="Perform analysis of TiSim Diffusion of 1K cells as sink")
    
    parser.add_argument("--data_folder", action="store", dest = "data_folder",help="folder were the output data is stored",default="results/")
    parser.add_argument("--csvout", action="store", dest="csv_fname", default="result1000.txt",
                        help="File name to store the summary table used for the plot")
    return parser
# Generate GIF
def get_key(fp):
    filename = os.path.splitext(os.path.basename(fp))[0]
    int_part = re.findall(r'\d+', filename)[0]
    return int(int_part)

def create_gif(output_folder,csv_fname):

    # Read the dataframe from the specified file
    df = pd.read_csv(data_folder+csv_fname,header=None,index_col=0)
    df = pd.read_csv(data_folder+csv_fname,names=[x for x in range(0,28)],skiprows=[0],index_col=0,sep='\t|,',engine='python')
    print(df)
    # exit()
    df =df*602.2
    x = []
    y = []
    z = []
    # numbers = list(range(-110, 111, 20))

    # for xi in numbers:
    #     for yi in numbers:
    #         for zi in numbers:
    #             x.append(xi)
    #             y.append(yi)
    #             z.append(zi)
    for xi in [-20,0,20]:
        for yi in [-20,0,20]:
            for zi in [-20,0,20]:
                x.append(xi)
                y.append(yi)
                z.append(zi)
    print(len(x))
    global_min = df.values.min()
    global_max = df.values.max()
    for index, row in df.iterrows():
        fractional_part = str(index).split('.')[1]
        if len(fractional_part)<=1:
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            sc = ax.scatter(x, y, z, c=row, cmap='jet',vmin=global_min, vmax=global_max)
            cbar = fig.colorbar(sc,shrink=0.7)
            ax.set_xlabel('x')
            ax.set_ylabel('y')
            plt.title("TiSim Diffusion of molecules, 1k cells as sinks Timestep: " + f'{index:.2f}')
            plt.savefig(output_folder+"/diff_timepoint"+str(int(index*10))+".png")
            plt.close()


    frames = [Image.open(image) for image in sorted(glob.glob(f"{output_folder}/*.png"), key=get_key)]
    frame_one = frames[0]
    frame_one.save(os.path.join("many_diffusion.gif"), format="GIF", append_images=frames,
                save_all=True, duration=100, loop=0)
if __name__ == '__main__':
    
    parser = create_parser()
    args = parser.parse_args()
    data_folder = args.data_folder
    csv_fname = args.csv_fname
    create_gif(data_folder,csv_fname)