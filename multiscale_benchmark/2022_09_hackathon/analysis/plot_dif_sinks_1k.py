import argparse
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler, StandardScaler
pd.set_option('display.float_format', lambda x: '%.5f' % x)
# ../Biodynamo/unit_test_diffusion/results/concentration.csv
# ../Tisim/unit_test_diffusion/results/result_1c_diffusion.txt

def get_physicell_df_sinks(file):
    df= pd.read_csv(file,index_col=None,usecols=['timestep','diff'])
    df['timestep'] = df['timestep'].round(2)
    return df
def get_biodynamo_df(file):
    df= pd.read_csv(file,index_col=None,header=None,names = ['timestep','diff'],sep=" ")
    # df.index= df.index /100
    return df
def get_tisim_df(file):
    df= pd.read_csv(file,delimiter="\t",names = ['timestep','diff'],header=0)
    # df = pd.read_csv(file,names=[x for x in range(0,28)],skiprows=[0],index_col=0,sep='\t|,',engine='python')
    # df['diff']= df.mean(axis=1)
    df['nt'] = df.sum(axis=1)*8000
    df.to_csv("check.csv")
    timesteps = np.arange(0, 10,0.1)
    timesteps_rounded = np.round(timesteps, 2)
    df['timestep_rounded'] = df["timestep"].round(2)
    # df['timestep_rounded'] = df.index.values.round(2)
    df = df[df['timestep_rounded'].isin(timesteps_rounded)]
    df.drop('timestep_rounded', axis=1, inplace=True)
    return df

def get_chaste_df(file):
    df= pd.read_csv(file,delim_whitespace=True,names = ['timestep','diff'],header=0)
    return df


def main():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")

    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell concentration over time csv. If not existing need to generate with many_analysis.py script",
                        default="../Physicell/output/diffusion_1k/mean_diff_of_sinks.csv")
    #  action="store", dest = "data_folder",help="folder were the output data is stored",default="results/"
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo concentration over time csv",
                    default="../Biodynamo/unit_test_diffusion_1k/data.csv")
    # Biodynamo/unit_test_diffusion_1k/data.csv
    parser.add_argument("--ts-csv",action="store", dest = "ts_csv", help="Path to TiSim concentration over time csv",
                    default="../Tisim/unit_test_diffusion_1k/results/result_1000c_diffusion.txt")
    # parser.add_argument("--ts-csv",action="store", dest = "ts_csv", help="Path to TiSim concentration over time csv",
    #                 default="../Tisim/unit_test_diffusion_1k/results/result1000.txt")
    parser.add_argument("--ch-csv",action="store",dest = "ch_csv", help="Path to Chaste concentration over time csv",
                        default="../Chaste/unit_test_diffusion_1k/results/TestDiffusionSmall12.dat")    
    args = parser.parse_args()
    
# "mean_diff_of_sinks.csv"

    pc_conc = get_physicell_df_sinks(args.pc_csv)

    # pc_conc_2 = get_physicell_df_not_rounded("../Physicell/output/diffusion_0.001/microenv_single_diffusion.csv")
    # print(pc_conc_2['diff']/602.2)
    bd_conc = get_biodynamo_df(args.bd_csv)
    ts_conc = get_tisim_df(args.ts_csv)
    ch_conc = get_chaste_df(args.ch_csv)



    plt.plot(pc_conc['timestep'],pc_conc['diff']/602.2,label = 'Physicell 0.1',color='green',alpha=0.6)
    # plt.plot(pc_conc_2['timestep'],pc_conc['diff']/602.2,label = 'Physicell 0.001',color='orange',alpha=0.6)
    plt.plot(bd_conc['timestep'],bd_conc['diff'],label = 'Biodynamo',alpha=0.5,color = 'red')
    plt.plot(ts_conc['timestep'],ts_conc['diff'],label = 'TiSim', color  = '#ffd343',alpha=0.6)
    plt.plot(ch_conc['timestep'],ch_conc['diff'],label = 'Chaste', color  = 'blue',alpha = 0.5)
    plt.ylabel("Concentration μM")
    plt.xlabel("Time (minutes)")
    plt.legend()
    plt.title("Concentration of central voxel")
    plt.savefig("./single_diffusion_concentration_of_central_voxel_sinks.png",dpi=200)
    plt.show()
if __name__ == "__main__":
    main()
