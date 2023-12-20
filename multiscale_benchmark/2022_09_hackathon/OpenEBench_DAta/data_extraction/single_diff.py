import argparse
import pandas as pd
import numpy as np
# pd.reset_option('display.max_rows')
# pd.reset_option('display.max_columns')
# pd.reset_option('display.width')
# pd.set_option('display.max_rows', None)
# pd.set_option('display.max_columns', None)
# pd.set_option('display.width', None)
def create_parser():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")

    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell concentration over time csv. If not existing need to generate with many_analysis.py script",
                        default="../../Physicell/output/diffusion/microenv_single_diffusion.csv")
    #  action="store", dest = "data_folder",help="folder were the output data is stored",default="results/"
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo concentration over time csv",
                    default="../../Biodynamo/unit_test_diffusion/results/concentration.csv")
    parser.add_argument("--ts-csv",action="store", dest = "ts_csv", help="Path to TiSim concentration over time csv",
                    default="../../Tisim/unit_test_diffusion/results/result_1c_diffusion.txt")
    parser.add_argument("--ch-csv",action="store",dest = "ch_csv", help="Path to Chaste concentration over time csv",
                        default="../../Chaste/unit_test_diffusion/results/TestDiffusionSmall03.dat")

    return parser


def get_physicell_df(file):
    df= pd.read_csv(file,index_col=0)
    df.rename(columns={'diff': 'pc_diff'}, inplace=True)

    df = df.loc[df.index == 13]
    df = df[["pc_diff","timestep"]]

    df.to_csv("../data/unit_test_diffusion/pc_diffusion.csv")

    return df

def get_biodynamo_df(file):
    df= pd.read_csv(file,index_col=0,header=None)
    df.index = df.index /100
    df = pd.DataFrame(df[14])
    indices = np.arange(0, 10.1, 0.1)
    # df = df.loc[df.index.isin(indices)]
    df = df[np.any(np.abs(df.index.values[:, None] - indices) < 1e-5, axis=1)]
    # 

    df.rename(columns={14: 'bd_diff'}, inplace=True)
    df['bd_diff'] = df['bd_diff'] * 602.2
    df["timestep"] = df.index
    df.to_csv("../data/unit_test_diffusion/bdnm_diffusion.csv")
    return df
def get_tisim_df(file):
    df= pd.read_csv(file,delimiter="\t",names = ['timestep','ts_diff'],header=0)
    df['ts_diff'] = df['ts_diff'] * 602.2
    df.to_csv("../data/unit_test_diffusion/tisim_diffusion.csv")
    return df

def get_chaste_df(file):
    df= pd.read_csv(file,delim_whitespace=True,names = ['timestep','ch_diff'],header=0,index_col=None)

    df.index = df.index /100
    
    indices = np.arange(0, 10.1, 0.1)
    # df = df.loc[df.index.isin(indices)]
    df = df[np.any(np.abs(df.index.values[:, None] - indices) < 1e-5, axis=1)]
    df["ch_diff"] = df['ch_diff'] = df['ch_diff'] * 602.2
    df["timestep"] = df.index
    df.reset_index(drop=True, inplace=True)
    df.to_csv("../data/unit_test_diffusion/chaste_diffusion.csv")
    return df


def main():
    args = create_parser().parse_args()
    pc_df = get_physicell_df(args.pc_csv)
    bd_df = get_biodynamo_df(args.bd_csv)
    ts_df = get_tisim_df(args.ts_csv)
    ch_df = get_chaste_df(args.ch_csv)

main()