import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
import argparse
from sklearn.preprocessing import MinMaxScaler
import numpy as np


def get_physicell_df(file):
    df = pd.read_csv(file,index_col=0).sort_values(by=['dt']).reset_index(drop=True)
    df.rename(columns= {"dt":"timestep"},inplace=True)
    
    df['velocity'] = df['v1']
    df= df[["timestep","velocity"]]
    df.to_csv("../data/mechanics_movement/pc_velocity.csv")

    return df

def get_biodynamo_df(file):
    df = pd.read_csv(file,index_col=0,header = None,sep='\t|,',engine='python').rename(columns={1: "x", 2: "y", 3: "z"})
    
    df['dx'] = abs(df['x'] - df['x'].shift(1))
    df['dx'].fillna(0, inplace=True)
    
    df['timestep'] = np.arange(0,10,0.1)
    df['dt'] = abs(df['timestep'] - df['timestep'].shift(1))
    df['dt'].fillna(0, inplace=True)

    df['velocity'] = df['dx'] / df['dt']
    df= df[["timestep","velocity"]]
    df.to_csv("../data/mechanics_movement/bdnm_velocity.csv")
    return df
def get_tisim_df(file):
    # df= pd.read_csv(file,delimiter="\t",names = ['timestep','diff'],header=0)
    df = pd.read_csv(file,names=[x for x in range(0,28)],skiprows=[0],index_col=0,sep='\t|,',engine='python')
    return df

def get_chaste_df(file):
    df = pd.read_csv(file,header = None,names=["timestep","x","y"],sep='\t| ',index_col=None,engine='python')

    df['dx'] = abs(df["x"] - df["x"].shift(1))
    df['dx'].fillna(0, inplace=True)

    df['dt'] = np.arange(0,10.01,0.1)

    df['velocity'] = df['dx'] / df['dt']
    df= df[["timestep","velocity"]]
    df.to_csv("../data/mechanics_movement/chaste_velocity.csv")

    return df
def main():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")

    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell position over time csv",
                        default="../../Physicell/output/mechanics_movement/cell_position_time.csv")
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo position over time csv",
                    default="../../Biodynamo/unit_test_mechanics_friction_single/results/positions.csv")
    parser.add_argument("--ch-csv",action="store", dest = "ch_csv", help="Path to Chaste position over time csv",
                    default="../../Chaste/unit_test_mechanics_friction/results/node_locations.dat")
    # parser.add_argument("--ts-csv", help="Path to TiSim concentration over time csv")
    
    args = parser.parse_args()
    


    pc_conc = get_physicell_df(args.pc_csv)
    bd_conc = get_biodynamo_df(args.bd_csv)
    ch_conc = get_chaste_df(args.ch_csv)
main()