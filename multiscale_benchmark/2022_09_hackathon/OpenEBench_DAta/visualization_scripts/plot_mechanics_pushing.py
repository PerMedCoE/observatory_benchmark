import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
import argparse
from sklearn.preprocessing import MinMaxScaler
def plot_distance_moved(pc_data,bd_data,ch_data,ts_data):
    scaler = MinMaxScaler()

    pc_data['normalized_distance'] = scaler.fit_transform(pc_data[["dx"]])

    # Normalize distances in DataFrame 2
    bd_data['normalized_distance'] = scaler.fit_transform(bd_data[['dx']])

    # Normalize distances in DataFrame 3
    ch_data['normalized_distance'] = scaler.fit_transform(ch_data[["dx"]])

    ts_data['normalized_distance'] = scaler.fit_transform(ts_data[["dx"]])
    plt.plot(pc_data['timestep'],pc_data['normalized_distance'],label="PhysiCell", color= 'green',alpha = 0.5)
    plt.plot(bd_data['timestep'],bd_data['normalized_distance'],label="Biodynamo",color= 'red',alpha = 0.7)
    plt.plot(ch_data.index/10,ch_data['normalized_distance'],label="Chaste",alpha = 0.6)
    plt.plot(ts_data['timestep'],ts_data['normalized_distance'],label="TiSim",alpha = 0.6)

    plt.ylabel(ylabel="Normalized Distance travelled")
    plt.xlabel(xlabel="Time")
    plt.title("Normalized distance between the two cells across time")
    plt.legend()
    plt.savefig("mechanics_pusing_normalized_distances.png",dpi=200)

    plt.show()

    return
def main():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")

    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell position over time csv",
                        default="../data/mechanics_pushing/pc_distance.csv")
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo position over time csv",
                    default="../data/mechanics_pushing/bdnm_distance.csv")
    parser.add_argument("--ch-csv",action="store", dest = "ch_csv", help="Path to Chaste position over time csv",
                    default="../data/mechanics_pushing/chaste_distance.csv")
    parser.add_argument("--ts-csv",action="store", dest = "ts_csv", help="Path to TiSim concentration over time csv",
                         default="../data/mechanics_pushing/ts_distance.csv")
    
    args = parser.parse_args()
    


    pc_df = pd.read_csv(args.pc_csv,index_col=0)
    bd_df = pd.read_csv(args.bd_csv,index_col=0)
    ch_df = pd.read_csv(args.ch_csv,index_col=0)
    ts_df = pd.read_csv(args.ts_csv,index_col=0)
    plot_distance_moved(pc_df,bd_df,ch_df,ts_df)
if __name__ == "__main__":
    main()
