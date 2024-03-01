import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
import argparse
from sklearn.preprocessing import MinMaxScaler
import numpy as np


def get_physicell_df(file):
    df = pd.read_csv(file,index_col=0)
    return df

def get_biodynamo_df(file):
    df = pd.read_csv(file,index_col=0)

    return df
def get_tisim_df(file):
    df = pd.read_csv(file,names=[x for x in range(0,28)],skiprows=[0],index_col=0,sep='\t|,',engine='python')
    return df

def get_chaste_df(file):
    df = pd.read_csv(file,index_col=0)
    return df

def plot_distance_moved(pc_data,bd_data,ch_data):
    plt.plot(pc_data["timestep"],pc_data['velocity'],label="PhysiCell", color= 'green',alpha = 0.7)
    plt.plot(bd_data["timestep"],bd_data['velocity'],label="Biodynamo",color= 'red')
    plt.plot(ch_data["timestep"],ch_data['velocity'],label="Chaste")
    plt.ylabel(ylabel="Velocity μM/s")
    plt.xlabel(xlabel="Time")
    plt.title("Velocity of the movement of a cell across time")
    plt.legend()
    plt.savefig("mechanics_movement_normalized_velocity.png",dpi=200)

    plt.show()

    return
def main():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")

    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell position over time csv",
                        default="../data/mechanics_movement/pc_velocity.csv")
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo position over time csv",
                    default="../data/mechanics_movement/bdnm_velocity.csv")
    parser.add_argument("--ch-csv",action="store", dest = "ch_csv", help="Path to Chaste position over time csv",
                    default="../data/mechanics_movement/chaste_velocity.csv")
    # parser.add_argument("--ts-csv", help="Path to TiSim concentration over time csv")
    
    args = parser.parse_args()
    


    pc_conc = get_physicell_df(args.pc_csv)
    bd_conc = get_biodynamo_df(args.bd_csv)
    ch_conc = get_chaste_df(args.ch_csv)

    plot_distance_moved(pc_conc,bd_conc,ch_conc)

if __name__ == "__main__":
    main()
