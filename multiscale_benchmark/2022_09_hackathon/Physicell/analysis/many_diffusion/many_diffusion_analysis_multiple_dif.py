import sys,os,re,argparse,glob
sys.path.append('./pctk')
from pctk import multicellds
import pandas as pd
from scipy.io import loadmat
from pathlib import Path
import matplotlib.pyplot as plt
from PIL import Image


def create_parser():
    parser = argparse.ArgumentParser(description="Perform analysis of Physicell 1k Cell diffusion unit test")
    
    parser.add_argument("data_folder", action="store", help="folder were the output data is stored")
    
    parser.add_argument("--gifout", action="store", dest="gif_out", default="/physicell_many_diffusion.gif",
                        help="File name to save the gif")
                        
    parser.add_argument("--csvout", action="store", dest="csv_fname", default="/microenv_single_diffusion.csv",
                        help="File name to store the summary table used for the plot")
    parser.add_argument("-g","--generate-gif", action="store_true")
    parser.add_argument("-c","--generate-csv", action="store_true")
    return parser

def get_key(fp):
    filename = os.path.splitext(os.path.basename(fp))[0]
    # int_part = filename.split("_")[1]
    int_part =  re.findall(r'\d+', filename)[0]
    return int(int_part)


def generate_microenv_csv(output_folder,csv_out):
    # generate csv of all voxels and their diffusion in each timestep
    files = Path(output_folder).glob('*output*_microenvironment*.mat')
    mcds = multicellds.Settings(output_folder+"/PhysiCell_settings.xml")
    step = mcds.interval
    df_cell = pd.DataFrame(columns = ['x','y','z','vol','director_signal','cargo_signal'])
    i = 0
    for file in sorted(files):
        mat = loadmat(file)
        # print(mat)
        mat = mat["multiscale_microenvironment"]
        steps = [step*i] * mat.shape[1]
        df_mat = pd.DataFrame(mat.transpose(),columns = ['x','y','z','vol','director_signal','cargo_signal'])
        df_mat["timestep"] = steps
        df_cell= pd.concat([df_cell,df_mat])
        i= i + 1

    df_cell.to_csv(output_folder+csv_out)


def generate_pngs(output_folder,csv_out,dif):
    pc_me = pd.read_csv(output_folder+csv_out,index_col=0)
    grouped = pc_me.groupby(by="timestep")
    # Create a 3D scatter plot
    for t,timestep in grouped:
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')

        # Add voxels to the plot
        ax.scatter(timestep['x'], timestep['y'], timestep['z'], c=timestep[dif], cmap='jet')

        # Set the axis labels
        ax.set_xlabel('x')
        ax.set_ylabel('y')

        # Show the plot
        num_ite = t*100
        plt.title("Timestep: "+f'{t:.2f}')
        plt.savefig(output_folder+"/diff_timepoint"+str(int(num_ite))+"_"+dif+".png")
        plt.close()

def generate_gif(output_folder,csv_out,gif_out):
    for d in ['director_signal','cargo_signal']:
        gif_out=d+".gif"
        generate_pngs(output_folder,csv_out,d)
        frames = [Image.open(image) for image in sorted(glob.glob(f"{output_folder}/*{d}.png"),key=get_key)]

        frame_one = frames[0]
        frame_one.save(output_folder+gif_out, format="GIF", append_images=frames,
                save_all=True, duration=100, loop=0)
        for file in glob.glob(f"{output_folder}/*{d}.png"):
            os.remove(file)
    
if __name__ == '__main__':
    
    parser = create_parser()
    args = parser.parse_args()
    data_folder = args.data_folder
    csv_fname = args.csv_fname
    gif_out = args.gif_out
    print(args.generate_csv,args.generate_gif)
    if args.generate_csv:
        print("generating microenvironment csv")
        generate_microenv_csv(data_folder,csv_fname)
    if args.generate_gif:
        print("generating gif")
        generate_gif(data_folder,csv_fname,gif_out)
