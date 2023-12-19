import argparse
import os
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler, StandardScaler

# ../Biodynamo/unit_test_diffusion/results/concentration.csv
# ../Tisim/unit_test_diffusion/results/result_1c_diffusion.txt
def get_physicell_df(file):
    df= pd.read_csv(file,index_col=0)
    result = df.loc[df.index == 13]
    return result

def get_biodynamo_df(file):
    df= pd.read_csv(file,index_col=0,header=None)
    df.index = df.index /100
    df = pd.DataFrame(df[14])
    df.rename(columns={14: 'diff'}, inplace=True)

    return df
def get_tisim_df(file):
    df= pd.read_csv(file,delimiter="\t",names = ['timestep','diff'],header=0)
    
    # df.rename(columns={'Concentration (uM)': 'diff'}, inplace=True)
    return df

def get_chaste_df(file):
    df= pd.read_csv(file,delim_whitespace=True,names = ['timestep','diff'],header=0)
    print(df)
    return df


def main():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")
    
    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell concentration over time csv. If not existing need to generate with many_analysis.py script",
                        default="../Physicell/output/diffusion/microenv_single_diffusion.csv")
    #  action="store", dest = "data_folder",help="folder were the output data is stored",default="results/"
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo concentration over time csv",
                    default="../Biodynamo/unit_test_diffusion/results/concentration.csv")
    parser.add_argument("--ts-csv",action="store", dest = "ts_csv", help="Path to TiSim concentration over time csv",
                    default="../Tisim/unit_test_diffusion/results/result_1c_diffusion.txt")
    parser.add_argument("--ch-csv",action="store",dest = "ch_csv", help="Path to Chaste concentration over time csv",
                        default="../Chaste/unit_test_diffusion/results/TestDiffusionSmall03.dat")
    
    args = parser.parse_args()
    


    pc_conc = get_physicell_df(args.pc_csv)
    bd_conc = get_biodynamo_df(args.bd_csv)
    ts_conc = get_tisim_df(args.ts_csv)
    ch_conc = get_chaste_df(args.ch_csv)



    plt.plot(pc_conc['timestep'],pc_conc['diff'],label = 'Physicell',color='green')
    plt.plot(bd_conc.index,bd_conc['diff']*602.2,label = 'Biodynamo',alpha=0.5,color = 'red')
    plt.plot(ts_conc['timestep'],ts_conc['diff']*602.2,label = 'TiSim', color  = '#ffd343')
    plt.plot(ch_conc['timestep'],ch_conc['diff']*602.2,label = 'Chaste', color  = 'blue')
    plt.ylabel("Concentration")
    plt.xlabel("Time (minutes)")
    plt.legend()
    plt.title("Concentration of central voxel")
    plt.savefig("./single_diffusion_concentration_of_central_voxel.png",dpi=200)
    plt.show()
    # Now create a plot of the 3 different concentrations over time
if __name__ == "__main__":
    main()
