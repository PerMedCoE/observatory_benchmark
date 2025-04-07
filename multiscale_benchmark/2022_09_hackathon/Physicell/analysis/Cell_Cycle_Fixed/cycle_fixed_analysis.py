import sys,os,re,argparse,glob
sys.path.append('./pctk')
from pctk import multicellds
import pandas as pd
from scipy.io import loadmat
from pathlib import Path
from PIL import Image
import matplotlib
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import numpy as np
def create_parser():
    parser = argparse.ArgumentParser(description="Perform analysis of Fixed Cell Cycle unit test for PhysiCEll")
    
    parser.add_argument("data_folder", action="store", help="folder were the output data is stored")
                        
    parser.add_argument("--csvout", action="store", dest="csv_fname", default="/cells_volumes.csv",
                        help="File name to store the summary table used for the plot")
    parser.add_argument("-g","--generate-gif", action="store_true")
    parser.add_argument("-c","--generate-csv", action="store_true")
    return parser
def generate_csv(data_folder,csv_fname,generate_csv):
    files = Path(data_folder).glob('*output*_cells.mat')
    # mcds = multicellds.Settings(data_folder+"/PhysiCell_settings.xml")
    df_cell = pd.DataFrame(columns = ['x','y','z',"dt",'radius'])
    interval = 30
    i=0
    for file in sorted(files):
        mat = loadmat(file)
        mat=mat['cells'][[0,1,2,3,4,7]]
        df_mat = pd.DataFrame(mat.transpose(),columns = ['id','x','y','z','total_volume','current_phase'])
        df_mat['dt'] = round(i, 1) 
        df_cell= pd.concat([df_mat,df_cell],ignore_index=True)
        i=i+30
    df_cell = df_cell.sort_values(by=['dt']).reset_index(drop=True)
    if generate_csv:
        df_cell.to_csv(data_folder+"/"+csv_fname)
    return df_cell


def create_png(physicell_data,output_folder):
    fig,ax = plt.subplots()
    physicell_data['dt'] = physicell_data['dt']/60
    pc_init_vol = physicell_data.iloc[0,4]
    print(pc_init_vol)
    dts= []
    vols = []
    for dt,idx in physicell_data.groupby(['dt']).groups.items():
        dts.append(dt)
        total_cell_volume = 0
        for i in idx.values:
            total_cell_volume += physicell_data.loc[i,'total_volume']
        perc = (total_cell_volume/(len(idx.values)))/pc_init_vol
        vols.append(perc)
    vols=[100*x for x in vols]
    plt.plot(dts,vols,label="PhysiCell",color='green' ,linewidth=2)
    plt.xlabel(xlabel="Time (hours)",fontsize=12,color = '#262626')
    plt.ylabel(ylabel="Percentage of initial volume",fontsize=12,color = '#262626')
    plt.title(label = 'PhysiCell Fixed Cell Cycle Total Volume',color = '#262626')

    for i in [0,1,2]:
        rect1 = matplotlib.patches.Rectangle((18*i,50),
                                        7, 170,
                                        facecolor ='orange',alpha = 0.1,edgecolor=None)
        
        plt.text(18*i+1.9, 210,'G0/G1',color ='orange',alpha = 0.3)
        rect2 = matplotlib.patches.Rectangle((18*i+7,50),
                                        6, 170,
                                        facecolor ='purple',alpha = 0.1,edgecolor=None)
        plt.text(18*i+7+1.7, 210,'S',color ='purple',alpha = 0.3)
        rect3 = matplotlib.patches.Rectangle((18*i+13,50),
                                        3, 170,
                                        facecolor ='yellow',alpha = 0.1,edgecolor=None)
        rect4 = matplotlib.patches.Rectangle((18*i + 16,50),
                                        2, 170,
                                        facecolor ='red',alpha = 0.1,edgecolor=None)
        
        ax.add_patch(rect1)
        ax.add_patch(rect2)
        
        if i ==2:
            break
        plt.text(18*i+13+0.8, 210,'G2',color ='gold',alpha = 0.8)
        plt.text(18*i+16+0.4, 210,'M',color ='red',alpha = 0.3)
        ax.add_patch(rect3)
        ax.add_patch(rect4)
        if i==4:
            ax.legend()

    ax.set_xlim(xmin=0,xmax = 48)
    ax.set_ylim(ymin=90)
    # ax.legend()
    # plt.plot(dts,vols,label="PhysiCell",color='green' ,linewidth=2)
    ax.legend(bbox_to_anchor = (1.0,1.0),loc='upper left')
    plt.tight_layout()
    plt.savefig("fixed_cell_cycle_volumes.png")
    plt.show()
if __name__ == '__main__':
    parser = create_parser()
    args = parser.parse_args()
    physicell_data = generate_csv(args.data_folder,args.csv_fname,args.generate_csv)
    print(physicell_data)
    # create_png(physicell_data,args.data_folder)
