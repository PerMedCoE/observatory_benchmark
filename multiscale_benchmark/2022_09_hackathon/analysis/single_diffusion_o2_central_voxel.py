import argparse
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler, StandardScaler
pd.set_option('display.float_format', lambda x: '%.5f' % x)
# ../Biodynamo/unit_test_diffusion/results/concentration.csv
# ../Tisim/unit_test_diffusion/results/result_1c_diffusion.txt
# observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Tisim/unit_test_diffusion/results/arnau_diffusion1.txt

# here we select timesteps with step 0.1 until we reach minute 1 and then every minute.
def get_physicell_df(file):
    df= pd.read_csv(file,index_col=0)
    df = df.loc[df.index == 13]
    timesteps = np.concatenate((np.linspace(0, 1, num=11)[:-1], np.arange(1, 11, 1)))
    timesteps_rounded = np.round(timesteps, 2)
    df['timestep_rounded'] = df['timestep'].round(2)
    selected_rows = df[df['timestep_rounded'].isin(timesteps_rounded)]
    selected_rows.drop('timestep_rounded', axis=1, inplace=True)
    return selected_rows
def get_physicell_df_cells(file):
    df= pd.read_csv(file,index_col=0)
    df = df.loc[df.index == 13]
    timesteps = np.concatenate((np.linspace(0, 1, num=11)[:-1], np.arange(1, 11, 1)))
    timesteps_rounded = np.round(timesteps, 2)
    df['timestep_rounded'] = df['timestep'].round(2)
    selected_rows = df[df['timestep_rounded'].isin(timesteps_rounded)]
    selected_rows.drop('timestep_rounded', axis=1, inplace=True)
    print(selected_rows)
    return selected_rows
def get_physicell_df_not_rounded(file):
    df= pd.read_csv(file,index_col=0)
    df = df.loc[df.index == 13]
    return df
def get_biodynamo_df(file):
    df= pd.read_csv(file,index_col=None,header=None,sep = " ",names = ['timestep','avg_diff','cen_diff'])
    # df['timestep'] = df.index /100
    # df = pd.DataFrame(df[[14,'timestep']])
    timesteps = np.concatenate((np.linspace(0, 1, num=11)[:-1], np.arange(1, 11, 1),[9.99]))
    timesteps_rounded = np.round(timesteps, 2)
    df['timestep_rounded'] = df['timestep'].round(2)
    selected_rows = df[df['timestep_rounded'].isin(timesteps_rounded)]
    # selected_rows.rename(columns={14: 'diff'}, inplace=True)
    selected_rows.drop('timestep_rounded', axis=1, inplace=True)
    return selected_rows
def get_tisim_df(file):
    df= pd.read_csv(file,names = ['timestep','diff'],header=0)

    # df= pd.read_csv(file,delimiter="\t",usecols=[0,14],names = ['timestep','diff'],header=0)
    df = pd.concat([pd.DataFrame({"timestep": [0],"diff":[0]}), df], ignore_index=True)
    timesteps = np.concatenate((np.linspace(0, 1, num=11)[:-1], np.arange(1, 11, 1)))
    timesteps_rounded = np.round(timesteps, 2)
    df['timestep_rounded'] = df['timestep'].round(2)
    selected_rows = df[df['timestep_rounded'].isin(timesteps_rounded)]
    selected_rows.drop('timestep_rounded', axis=1, inplace=True)
    return selected_rows
def get_chaste_df(file):
    df= pd.read_csv(file,delim_whitespace=True,names = ['timestep','diff'],header=0)
    timesteps = np.concatenate((np.linspace(0, 1, num=11)[:-1], np.arange(1, 11, 1)))
    timesteps_rounded = np.round(timesteps, 2)
    df['timestep_rounded'] = df['timestep'].round(2)
    selected_rows = df[df['timestep_rounded'].isin(timesteps_rounded)]
    return selected_rows


def main():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")
    
    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell concentration over time csv. If not existing need to generate with many_analysis.py script",
                        default="../Physicell/output/new_results/diffusion_v1_U12044/microenv_single_diffusion.csv")
    #  action="store", dest = "data_folder",help="folder were the output data is stored",default="results/"
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo concentration over time csv",
                    default="../Biodynamo/unit_test_diffusion_small/data.csv")
    parser.add_argument("--ts-csv",action="store", dest = "ts_csv", help="Path to TiSim concentration over time csv",
                    default="../Tisim/unit_test_diffusion/results/diffusion_1_cell.csv")
    parser.add_argument("--ch-csv",action="store",dest = "ch_csv", help="Path to Chaste concentration over time csv",
                        default="../Chaste/unit_test_diffusion/results/TestDiffusionSmall03.dat")
    
    args = parser.parse_args()
    


    # pc_conc = get_physicell_df_not_rounded(args.pc_csv)
    pc_conc = get_physicell_df(args.pc_csv)
    
    # pc_df_v1 = get_physicell_df("../Physicell/output/new_results/diffusion_v1_U12044//microenv_single_diffusion.csv")
    bd_conc = get_biodynamo_df(args.bd_csv)
    ts_conc = get_tisim_df(args.ts_csv)
    ch_conc = get_chaste_df(args.ch_csv)
    pc_filtered = pc_conc[pc_conc['timestep'] <= 3.0]
    bd_filtered = bd_conc[bd_conc['timestep'] <= 3.0]
    ts_filtered = ts_conc[ts_conc['timestep'] <= 3.0]
    ch_filtered = ch_conc[ch_conc['timestep'] <= 3.0]
    ground_truth = pd.read_csv("fort.16",delim_whitespace=True,names = ["timestep",'diff'])
    print(ground_truth)
    
    plt.plot(pc_filtered['timestep'],pc_filtered['diff']/602.2,label = 'Physicell',color='green',alpha=0.6)
    plt.plot(bd_filtered['timestep'],bd_filtered['cen_diff'],label = 'Biodynamo',alpha=0.5,color = 'red')
    plt.plot(ts_filtered['timestep'],ts_filtered['diff'],label = 'TiSim', color  = '#ffd343',alpha=0.6)
    plt.plot(ch_filtered['timestep'],ch_filtered['diff'],label = 'Chaste', color  = 'blue',alpha = 0.5)
    # plt.plot(ground_truth['timestep'].round(2),ground_truth['diff'],label = 'Alya', color  = 'purple',alpha = 0.5)
    plt.ylabel("Concentration μM")
    plt.xlabel("Time (minutes)")
    plt.legend()
    plt.title("Diffusion one cell as sink : Oxygen concentration in Central Voxel")
    plt.savefig("./updated_concentration_one_cell.png",dpi=200)
    plt.show()
if __name__ == "__main__":
    main()
