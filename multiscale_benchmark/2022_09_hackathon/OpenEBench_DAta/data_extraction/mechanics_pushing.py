import pandas as pd
import argparse
import numpy as np
# Load data into a pandas dataframe


def get_physicell_df(file):
    df = pd.read_csv(file,index_col=0,float_precision='round_trip').sort_values(by=['dt']).reset_index(drop=True)
    pc_dist =  abs(df[df['id']==0]['x'].reset_index() - df[df['id']==1]['x'].reset_index())
    pc_dist['timestep'] = df['dt'].unique()
    pa= df[df['id']==0]['radius'].reset_index() + df[df['id']==1]['radius'].reset_index()
    pc_dist['radius'] = pa["radius"]
    
    pc_dist.rename({"x":"dx","dt":"timestep"},inplace=True,axis=1)
    pc_dist.drop("index",axis=1,inplace=True)
    pc_dist['dxx'] = abs(pc_dist['dx'] - pc_dist['radius'])

    pc_dist= pc_dist[["timestep","dxx"]]
    pc_dist.rename({"dxx":"dx"},inplace=True,axis=1)
    pc_dist.to_csv("../data/mechanics_pushing/pc_distance.csv")
    return pc_dist

def get_biodynamo_df(file):
    df = pd.read_csv(file,index_col=0,header = None,sep='\t|,',engine='python').rename(columns={1: "x1", 4: "x2"})
    df['dx'] = abs(df["x1"] - df["x2"])
    df['timestep'] = np.arange(0, 10, .1)
    
    # # The first row of the 'distances' column will be NaN, you can replace it with 0 if needed
    # df['dx'].fillna(0, inplace=True)
    df = df[["timestep","dx"]]
    df.to_csv("../data/mechanics_pushing/bdnm_distance.csv")
    return df
def get_tisim_df(file):
    df = pd.read_csv(file,index_col=None,header=None).T
    df['dx'] = abs(df[0]-df[1])
    df['timestep'] = np.arange(0, 10.01, .1)
    df = df[["timestep","dx"]]
    df.to_csv("../data/mechanics_pushing/ts_distance.csv")
    return df

def get_chaste_df(file):
    df = pd.read_csv(file,header = None,sep='\t| ',index_col=0,engine='python')
    df['timestep'] = df.index
    df.reset_index(drop=True,inplace=True)
    df['dx'] = abs(df[2] - df[1])
    # The first row of the 'distances' column will be NaN, you can replace it with 0 if needed
    df['dx'].fillna(0, inplace=True)
    df = df[["timestep","dx"]]
    df.to_csv("../data/mechanics_pushing/chaste_distance.csv")
    return df


def main():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")

    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell position over time csv",
                        default="../../Physicell/output/mechanics_pushing/cells_position_time.csv")
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo position over time csv",
                    default="../../Biodynamo/unit_test_mechanics_pushing/results/positions.csv")
    parser.add_argument("--ch-csv",action="store", dest = "ch_csv", help="Path to Chaste position over time csv",
                    default="../../Chaste/unit_test_mechanics_pushing/results/results.viznodelocations")
    parser.add_argument("--ts-csv",action="store", dest = "ts_csv", help="Path to TiSim concentration over time csv",
                         default="../../Tisim/unit_test_mechanics_pushing/results/positions.csv")
    
    args = parser.parse_args()
    


    pc_df = get_physicell_df(args.pc_csv)
    bd_df = get_biodynamo_df(args.bd_csv)
    ch_df = get_chaste_df(args.ch_csv)
    ts_df = get_tisim_df(args.ts_csv)
if __name__ == "__main__":
    main()
