# againn plots all tools concentration of the central vocel for all tools. 
# inputs are the equivalent csvs
import argparse
import os
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler, StandardScaler
import numpy as np

def get_physicell_df(file):
    df= pd.read_csv(file,index_col=None,usecols=['timestep','diff'])  
    groupe_conc = df.groupby(by="timestep")
    result_conc = groupe_conc.mean()
    result_conc['nt'] = groupe_conc.sum()*8000
    timesteps = np.concatenate((np.linspace(0, 1, num=11)[:-1], np.arange(1, 11, 1)))
    timesteps_rounded = np.round(timesteps, 2)
    result_conc['timestep_rounded'] = result_conc.index.map(lambda x: round(x, 2))
    selected_rows = result_conc[result_conc['timestep_rounded'].isin(timesteps_rounded)]
    selected_rows.drop('timestep_rounded', axis=1, inplace=True)
    return selected_rows

def get_biodynamo_df(file):
    df= pd.read_csv(file,index_col=None,header=None,sep = " ",names = ['timestep','avg_diff','cen_diff'])
    timesteps = np.concatenate((np.linspace(0, 1, num=11)[:-1], np.arange(1, 11, 1),[9.99]))
    timesteps_rounded = np.round(timesteps, 2)
    df['timestep_rounded'] = df['timestep'].round(2)
    selected_rows = df[df['timestep_rounded'].isin(timesteps_rounded)]
    selected_rows.drop('timestep_rounded', axis=1, inplace=True)
    return selected_rows
def get_tisim_df(file):
    df= pd.read_csv(file,delimiter="\t",names = ['timestep','diff'],header=0)
    df['nt'] = df.sum(axis=1)*8000
    timesteps = np.arange(0, 10,0.1)
    timesteps_rounded = np.round(timesteps, 2)
    df['timestep_rounded'] = df["timestep"].round(2)
    df = df[df['timestep_rounded'].isin(timesteps_rounded)]
    df.drop('timestep_rounded', axis=1, inplace=True)
    print(df)
    return df

def get_chaste_df(file):
    df= pd.read_csv(file,delim_whitespace=True,names = ['timestep','diff','diff_cells'],header=0)
    return df

def main():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")

    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell concentration over time csv. If not existing need to generate with many_analysis.py script",
                        default="../Physicell/output/new_results/diffusion_v1_u12044_1k/microenv_many_diffusion.csv")
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
    

    pc_conc = get_physicell_df(args.pc_csv)
    bd_conc = get_biodynamo_df(args.bd_csv)

    ts_conc = get_tisim_df(args.ts_csv)
    ch_conc = get_chaste_df(args.ch_csv)

    print(pc_conc)
    print(bd_conc)
    print(ts_conc)
    print(ch_conc)


    plt.plot(pc_conc.index,pc_conc['diff']/602.2,label = 'Physicell',color='green')
    plt.plot(bd_conc['timestep'],bd_conc['avg_diff'],label = 'Biodynamo',alpha=0.5,color = 'red')
    plt.plot(ts_conc['timestep'],ts_conc['diff'],label = 'TiSim', color  = '#ffd343')
    plt.plot(ch_conc['timestep'],ch_conc['diff_cells'],label = 'Chaste', color  = 'blue')
    plt.ylabel("Concentration")
    plt.xlabel("Time (minutes)")
    plt.legend()
    plt.title("Average Concentration of all voxels")
    plt.savefig("./updated_average_concentration_of_02_of_all_voxels_1k.png",dpi=200)
    plt.show()
    # Now create a plot of the 3 different concentrations over time
if __name__ == "__main__":
    main()
