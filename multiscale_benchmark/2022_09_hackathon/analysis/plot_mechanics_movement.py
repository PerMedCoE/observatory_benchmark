import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
import argparse
from sklearn.preprocessing import MinMaxScaler

# Load data into a pandas dataframe

# data = pd.read_csv("/home/thalia/BSC/NEW_BENCH/Physicell_template/mechanics_movement/position_step.csv",index_col=0).sort_values(by=['dt']).reset_index(drop=True)
# data_biod = pd.read_csv("/home/thalia/BSC/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_friction_single/results/positions.csv"
# ,header = None,sep='\t|,',engine='python')
# data_biod = data_biod.rename(columns={1: "x", 2: "y", 3: "z"})


def get_physicell_df(file):
    df = pd.read_csv(file,index_col=0).sort_values(by=['dt']).reset_index(drop=True)
    # Normalize distances in DataFrame 1
    df['dx'] = abs(df['x'] - df['x'].shift(1))

    # The first row of the 'distances' column will be NaN, you can replace it with 0 if needed
    df['dx'].fillna(0, inplace=True)
    return df

def get_biodynamo_df(file):
    df = pd.read_csv(file,index_col=0,header = None,sep='\t|,',engine='python').rename(columns={1: "x", 2: "y", 3: "z"})
    df['dx'] = abs(df['x'] - df['x'].shift(1))

    # The first row of the 'distances' column will be NaN, you can replace it with 0 if needed
    df['dx'].fillna(0, inplace=True)

    return df
def get_tisim_df(file):
    # df= pd.read_csv(file,delimiter="\t",names = ['timestep','diff'],header=0)
    df = pd.read_csv(file,names=[x for x in range(0,28)],skiprows=[0],index_col=0,sep='\t|,',engine='python')
    return df

def get_chaste_df(file):
    df = pd.read_csv(file,header = None,sep='\t| ',index_col=0,engine='python')
    df['dx'] = abs(df[1] - df[1].shift(1))

    # The first row of the 'distances' column will be NaN, you can replace it with 0 if needed
    df['dx'].fillna(0, inplace=True)
    return df

def plot_distance_moved(pc_data,bd_data,ch_data):
    scaler = MinMaxScaler()

    pc_data['normalized_distance'] = scaler.fit_transform(pc_data[["dx"]])
    bd_data['normalized_distance'] = scaler.fit_transform(bd_data[['dx']])
    ch_data['normalized_distance'] = scaler.fit_transform(ch_data[["dx"]])
    ch_data.index=range(0,101)

    filtered_data = pc_data[pc_data.index > 10]
    filtered_data.reset_index(drop=True, inplace=True)

    plt.plot(filtered_data.index,filtered_data['normalized_distance'],label="PhysiCell", color= 'green',alpha = 0.7)
    plt.plot(bd_data.index,bd_data['normalized_distance'],label="Biodynamo",color= 'red')
    plt.plot(ch_data.index,ch_data['normalized_distance'],label="Chaste")
    plt.ylabel(ylabel="Normalized Velocity")
    plt.xlabel(xlabel="Time")
    plt.title("Normalized velocity of the movement of a cell across time")
    plt.legend()
    plt.savefig("mechanics_movement_normalized_velocity.png",dpi=200)

    plt.show()
    print(pc_data)
    print(bd_data)
    print(ch_data)
    return
def main():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")

    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell position over time csv",
                        default="../Physicell/output/mechanics_friction/cell_position_time.csv")
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo position over time csv",
                    default="../Biodynamo/unit_test_mechanics_friction_single/results/positions.csv")
    parser.add_argument("--ch-csv",action="store", dest = "ch_csv", help="Path to Chaste position over time csv",
                    default="../Chaste/unit_test_mechanics_friction/results/node_locations.dat")
    # parser.add_argument("--ts-csv", help="Path to TiSim concentration over time csv")
    
    args = parser.parse_args()
    


    pc_conc = get_physicell_df(args.pc_csv)
    bd_conc = get_biodynamo_df(args.bd_csv)
    ch_conc = get_chaste_df(args.ch_csv)

    plot_distance_moved(pc_conc,bd_conc,ch_conc)
    def update(frame, sphere_df, cube_df,triangle_df):
        ax.clear()
        ax.set_xlim([-15.0, 15.0])
        ax.set_ylim([-15.0, 15.00])
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.scatter(sphere_df.iloc[frame]['x'], sphere_df.iloc[frame]['y'], c='b', marker='o',label="Physicell")
        ax.scatter(cube_df.iloc[frame]['x'], cube_df.iloc[frame]['y'], c='r', marker='s',label="BioDynamo")
        ax.scatter(triangle_df.iloc[frame][1], triangle_df.iloc[frame][2], c='yellow', marker='s',label="Chaste")
        ax.legend()
        return ax
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.set_xlim([-21.0, 21.0])
    ax.set_ylim([-1.0, 1.0])
    ax.set_xlabel('X')
    ax.set_ylabel('Y')

    anim = FuncAnimation(fig, update, frames=len(bd_conc), fargs=(pc_conc, bd_conc,ch_conc), interval=50)
    anim.save('mechanics_movement.gif', writer='Pillow')

if __name__ == "__main__":
    main()
