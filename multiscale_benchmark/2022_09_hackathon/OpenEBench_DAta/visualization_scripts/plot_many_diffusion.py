import argparse
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler, StandardScaler



def main():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")
    
    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell concentration over time csv. If not existing need to generate with many_analysis.py script",
                        default="../data/unit_test_diffusion_1k/pc_diffusion.csv")
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo concentration over time csv",
                    default="../data/unit_test_diffusion_1k/bdnm_diffusion.csv")
    parser.add_argument("--ts-csv",action="store", dest = "ts_csv", help="Path to TiSim concentration over time csv",
                    default="../data/unit_test_diffusion_1k/tisim_diffusion.csv")
    parser.add_argument("--ch-csv",action="store",dest = "ch_csv", help="Path to Chaste concentration over time csv",
                        default="../data/unit_test_diffusion_1k/chaste_diffusion.csv")
    
    args = parser.parse_args()
    


    pc_conc = pd.read_csv(args.pc_csv,index_col=0)
    bd_conc = pd.read_csv(args.bd_csv,index_col=0)
    ts_conc = pd.read_csv(args.ts_csv,index_col=0)
    ch_conc = pd.read_csv(args.ch_csv,index_col=0)


    plt.plot(pc_conc['timestep'],pc_conc['pc_diff'],label = 'Physicell',color='green')
    plt.plot(bd_conc['timestep'],bd_conc['bd_diff'],label = 'Biodynamo',alpha=0.5,color = 'red')
    plt.plot(ts_conc['timestep' ],ts_conc['ts_diff'],label = 'TiSim', color  = '#ffd343')
    plt.plot(ch_conc['timestep'],ch_conc['ch_diff'],label = 'Chaste', color  = 'blue')
    plt.ylabel("Concentration")
    plt.xlabel("Time (minutes)")
    plt.legend()
    plt.title("Average Concentration of voxels")
    plt.savefig("./many_diffusion_concentration_of_central_voxel.png",dpi=200)
    plt.show()
    # Now create a plot of the 3 different concentrations over time
if __name__ == "__main__":
    main()
