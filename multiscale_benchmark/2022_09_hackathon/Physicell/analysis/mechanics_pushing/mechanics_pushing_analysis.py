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
    parser = argparse.ArgumentParser(description="Perform analysis of Physicell Movement two cells pushing unit test")
    
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
    df_cell = pd.DataFrame(columns = ['x','y','z',"dt",'radius','nuclear_radius'])
    interval = mcds.interval
    i=0
    for file in sorted(files):
        mat = loadmat(file)
        mat=mat['cells'][[0,1,2,3,38,39]]
        df_mat = pd.DataFrame(mat.transpose(),columns = ['id','x','y','z','radius','nuclear_radius'])
        df_mat['dt'] = round(i, 1) 
        df_cell= pd.concat([df_mat,df_cell],ignore_index=True)
        i=i+interval
    df_cell = df_cell.sort_values(by=['dt']).reset_index(drop=True)
    df_cell.to_csv(data_folder+"/"+csv_fname)
def generate_pngs(data_folder,csv_fname):
    pc_me = pd.read_csv(data_folder+csv_fname,index_col=0,float_precision='round_trip')
    # print(pc_me['dt'])
    # exit()
    grouped = pc_me.groupby(by="dt")
    # Create a 3D scatter plot
    for t,timestep in grouped:
        fig = plt.figure()
        ax = fig.add_subplot(111)
        # Add voxels to the plot
        # ax.scatter(timestep['x'], timestep['y'],s = timestep['radius']*20,c='green',label = "PhysiCell")
        circle1a = plt.Circle((timestep['x'].iloc[0], timestep['y'].iloc[0]), timestep['radius'].iloc[0], color='r',alpha = 0.5,label = "Cell volume")
        circle1b = plt.Circle((timestep['x'].iloc[0], timestep['y'].iloc[0]), timestep['nuclear_radius'].iloc[0], color='g',alpha = 0.2,label = "Cell nucleo")

        circle2a = plt.Circle((timestep['x'].iloc[1], timestep['y'].iloc[1]), timestep['radius'].iloc[0], color='r',alpha = 0.5,label = "Cell volume")
        circle2b = plt.Circle((timestep['x'].iloc[1], timestep['y'].iloc[1]), timestep['nuclear_radius'].iloc[0], color='g',alpha = 0.2,label = "Cell nucleo")
        # Set the axis labels
        ax.set_aspect( 1 )
        ax.add_artist( circle1a)
        ax.add_artist( circle1b )
        ax.add_artist( circle2a )
        ax.add_artist( circle2b )
        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_xlim([-21.0, 21.0])
        ax.set_ylim([-10.0, 11.0])
        # Show the plot
        num_ite = t*100
        plt.title("Timestep: "f"{t:.1f}""\n Two cells pushing")
        plt.legend()
        plt.savefig(data_folder+"/positions_timepoint"+str(int(num_ite))+".png")
        plt.close()
def get_key(fp):
    filename = os.path.splitext(os.path.basename(fp))[0]
    # int_part = filename.split("_")[1]
    int_part =  re.findall(r'\d+', filename)[0]
    return int(int_part)

def generate_gif(output_folder,csv_out,gif_out):
    generate_pngs(output_folder,csv_out)
    frames = [Image.open(image) for image in sorted(glob.glob(f"{output_folder}/*.png"),key=get_key)]

    frame_one = frames[0]
    frame_one.save(output_folder+gif_out, format="GIF", append_images=frames,
               save_all=True, duration=200, loop=0)


if __name__ == '__main__':
    
    parser = create_parser()
    args = parser.parse_args()
    data_folder = args.data_folder
    csv_fname = args.csv_fname
    gif_fname = args.gif_out

    print(args.generate_csv,args.generate_gif)
    if args.generate_csv:
        generate_position_timestep_csv(data_folder,csv_fname)
    if args.generate_gif:
        generate_gif(data_folder,csv_fname,gif_fname)