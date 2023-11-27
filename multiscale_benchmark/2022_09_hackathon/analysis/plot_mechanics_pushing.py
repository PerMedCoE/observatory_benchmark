import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
import argparse
from sklearn.preprocessing import MinMaxScaler

# Load data into a pandas dataframe


def get_physicell_df(file):
    df = pd.read_csv(file,index_col=0,float_precision='round_trip').sort_values(by=['dt']).reset_index(drop=True)
    pc_dist =  abs(df[df['id']==0]['x'].reset_index() - df[df['id']==1]['x'].reset_index())

    pc_dist['dt'] = df['dt'].unique()
    pa= df[df['id']==0]['radius'].reset_index() + df[df['id']==1]['radius'].reset_index()
    pc_dist['radius'] = pa["radius"]
    
    pc_dist.rename({"x":"dx"},inplace=True,axis=1)
    pc_dist.drop("index",axis=1,inplace=True)
    pc_dist['dxx'] = abs(pc_dist['dx'] - pc_dist['radius'])
    print(pc_dist)
    return pc_dist

def get_biodynamo_df(file):
    df = pd.read_csv(file,index_col=0,header = None,sep='\t|,',engine='python').rename(columns={1: "x1", 4: "x2"})
    df['dx'] = abs(df["x1"] - df["x2"])

    # # The first row of the 'distances' column will be NaN, you can replace it with 0 if needed
    # df['dx'].fillna(0, inplace=True)
    return df
def get_tisim_df(file):
    df = pd.read_csv(file,index_col=None,header=None).T
    df['dx'] = abs(df[0]-df[1])
    print(df)
    return df

def get_chaste_df(file):
    df = pd.read_csv(file,header = None,sep='\t| ',index_col=0,engine='python')
    df['dx'] = abs(df[2] - df[1])
    # The first row of the 'distances' column will be NaN, you can replace it with 0 if needed
    df['dx'].fillna(0, inplace=True)
    return df

def plot_distance_moved(pc_data,bd_data,ch_data,ts_data):
    scaler = MinMaxScaler()

    pc_data['normalized_distance'] = scaler.fit_transform(pc_data[["dxx"]])

    # Normalize distances in DataFrame 2
    bd_data['normalized_distance'] = scaler.fit_transform(bd_data[['dx']])

    # Normalize distances in DataFrame 3
    ch_data['normalized_distance'] = scaler.fit_transform(ch_data[["dx"]])
    ch_data.index=range(0,101)

    ts_data['normalized_distance'] = scaler.fit_transform(ts_data[["dx"]])
    plt.plot(pc_data.index,pc_data['normalized_distance'],label="PhysiCell", color= 'green',alpha = 0.5)
    plt.plot(bd_data.index,bd_data['normalized_distance'],label="Biodynamo",color= 'red',alpha = 0.7)
    plt.plot(ch_data.index,ch_data['normalized_distance'],label="Chaste",alpha = 0.6)
    plt.plot(ts_data.index,ts_data['normalized_distance'],label="TiSim",alpha = 0.6)

    plt.ylabel(ylabel="Normalized Distance travelled")
    plt.xlabel(xlabel="Time")
    plt.title("Normalized distance between the two cells across time")
    plt.legend()
    plt.savefig("mechanics_pusing_normalized_distances.png",dpi=200)

    plt.show()
    print(pc_data)
    print(bd_data)
    print(ch_data)
    return
def main():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")

    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell position over time csv",
                        default="../Physicell/output/mechanics_pushing/cells_position_time.csv")
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo position over time csv",
                    default="../Biodynamo/unit_test_mechanics_pushing/results/positions.csv")
    parser.add_argument("--ch-csv",action="store", dest = "ch_csv", help="Path to Chaste position over time csv",
                    default="../Chaste/unit_test_mechanics_pushing/results/results.viznodelocations")
    parser.add_argument("--ts-csv",action="store", dest = "ts_csv", help="Path to TiSim concentration over time csv",
                         default="../Tisim/unit_test_mechanics_pushing/results/positions.csv")
    
    args = parser.parse_args()
    


    pc_df = get_physicell_df(args.pc_csv)
    bd_df = get_biodynamo_df(args.bd_csv)
    ch_df = get_chaste_df(args.ch_csv)
    ts_df = get_tisim_df(args.ts_csv)
    plot_distance_moved(pc_df,bd_df,ch_df,ts_df)
if __name__ == "__main__":
    main()
