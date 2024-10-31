import argparse
import pandas as pd
import os,re
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
def create_parser():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")

    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell cell volumes for fixed cell cycle",
                        default="../Physicell/output/new_results/fixed_cell_cycle/cells_volumes.csv")
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo cell volumes for fixed cell cycle",
                    default="../Biodynamo/unit_test_cellcycle/new_results/cell-0-sim1.csv")
    parser.add_argument("--ch-csv",action="store", dest = "ch_csv", help="Path to Chaste cell volumes for fixed cell cycle",
                    default="../Chaste/unit_test_cellcycle/results/cellcycle_fixed.dat")
    parser.add_argument("--ts-csv",action="store", dest = "ts_csv", help="Path to TiSim cell volumes for fixed cell cycle",
                        default="../Tisim/cell cycle fix.csv")

    return parser

def get_physicell_df(file):
    df = pd.read_csv(file,index_col=0,float_precision='round_trip').sort_values(by=['dt']).reset_index(drop=True)
    print(df)
    return df
def get_biodynamo_df(file):
    df = pd.read_csv(file)
    df.columns = ['timestep', 'volume', 'Phase', 'Age']
    df['vol']= df['volume']/df['volume'][0]
    # print(df)
    return df
def get_tisim_df(file):
    data = pd.read_csv(file, header=0)
    time_steps = data['time (hour)']
    volume_columns = data.columns[1:]  # Assuming all other columns are cell volumes

    average_volumes = data[volume_columns].mean(axis=1, skipna=True)
    initial_total_volume = average_volumes.iloc[0]

    percentage_total_volumes = (average_volumes / initial_total_volume)*100
    # print(percentage_total_volumes)
    # Create a new DataFrame with time steps and percentage of total volumes
    df_percentage_total_volumes = pd.DataFrame({
        'timestep': time_steps,
        'volumes': percentage_total_volumes
    })
    # print(df_percentage_total_volumes)
    return df_percentage_total_volumes
def get_chaste_df(file):
    # df = pd.read_csv(file,header = None,sep='\t',index_col=0,engine='python')
    with open(file, "r") as f:
        df = pd.DataFrame(columns=["dt","id","x","y","z","g1_duration","s_duration","g2_duration","m_duration","current_phase","target_area","volume"])
        for line in f.read().splitlines():
            data = line.split()
            data = [float(x) if x.replace('.', '', 1).isdigit() else x for x in data]
            dt = data[0]
            for i in range(0,len(data)//11):
                row = {'dt': dt, 'id': data[1+11*i], 'x': data[2+11*i], 'y': data[3+11*i], 'z': data[4+11*i], 'g1_duration': data[5+11*i], 's_duration': data[6+11*i], 'g2_duration': data[7+11*i], 'm_duration': data[8+11*i], 'current_phase': data[9+11*i], 'target_area': data[10+11*i], 'volume': data[11+11*i]}
                row = pd.Series(row)
                df2 = pd.DataFrame(row).transpose()

                df =pd.concat([df,df2],ignore_index=True)
        return df

def plot(pc_df,ts_df,ch_df,bd_df):
    fig,ax = plt.subplots()
    pc_df['dt'] = pc_df['dt']/60
    pc_init_vol = pc_df.iloc[0]["total_volume"]


    pc_dts= []
    pc_vols = []
    for dt,idx in pc_df.groupby(['dt']).groups.items():
        # print(dt)
        pc_dts.append(dt)
        total_cell_volume = 0
        for i in idx.values:
            total_cell_volume += pc_df.loc[i,'total_volume']
        perc = float((total_cell_volume/(len(idx.values)))/pc_init_vol)
        pc_vols.append(perc)
    pc_vols=[100*x for x in pc_vols]
    print((pc_dts))
    print((pc_vols))
    ax.plot(pc_dts,pc_vols,label="PhysiCell",color='green' ,linewidth=2)
    # Now plot Chaste
    dts= []
    vols = []
    ch_init_vol = ch_df.loc[0,"volume"]
    for dt,idx in ch_df.groupby(['dt']).groups.items():
        dts.append(dt)
        total_cell_volume = 0
        for i in idx.values:
            total_cell_volume += ch_df.loc[i,'volume']

        perc = (total_cell_volume/(len(idx.values)))/ch_init_vol
        vols.append(perc)

    vols=[100*x for x in vols]

    ax.plot(dts,vols,label="Chaste",color='blue',linewidth=2,alpha=0.5)
    # Now plot TiSim
    ax.plot(ts_df['timestep'],ts_df['volumes'],label="TiSim",color  = '#ffd343',linewidth=2)
    plt.xlabel(xlabel="Time (hours)",fontsize=12,color = '#262626')
    plt.ylabel(ylabel="Percentage of initial volume",fontsize=12,color = '#262626')
    plt.title(label = 'Fixed Cell Cycle Total Volume',color = '#262626')
    # Plot Biodynamo
    ax.plot(bd_df['timestep'],bd_df["vol"]*100,label = "Biodynamo",color ="red")
    for i in [0,1,2]:
        rect1 = matplotlib.patches.Rectangle((18*i,50),
                                        7, 170,
                                        facecolor ='orange',alpha = 0.1,edgecolor=None)
        
        plt.text(18*i+1.9, 210,'G0/G1',color ='orange',alpha = 0.3)
        rect2 = matplotlib.patches.Rectangle((18*i+7,50),
                                        6, 170,
                                        facecolor ='purple',alpha = 0.1,edgecolor=None)
        plt.text(18*i+7+1.7, 210,'S',color ='purple',alpha = 0.3)
        rect3 = matplotlib.patches.Rectangle((18*i+13,50),
                                        3, 170,
                                        facecolor ='yellow',alpha = 0.1,edgecolor=None)
        rect4 = matplotlib.patches.Rectangle((18*i + 16,50),
                                        2, 170,
                                        facecolor ='red',alpha = 0.1,edgecolor=None)
        
        ax.add_patch(rect1)
        ax.add_patch(rect2)
        
        if i ==2:
            break
        plt.text(18*i+13+0.8, 210,'G2',color ='gold',alpha = 0.8)
        plt.text(18*i+16+0.4, 210,'M',color ='red',alpha = 0.3)
        ax.add_patch(rect3)
        ax.add_patch(rect4)
        if i==4:
            ax.legend()

    ax.set_xlim(xmin=0,xmax = 48)
    ax.set_ylim(ymin=90)
    ax.legend(bbox_to_anchor = (1.0,1.0),loc='upper left')
    plt.tight_layout()
    plt.savefig("fixed_cell_cycle_volumes.png",dpi=200)
    plt.show()

    return
def main():
    parser = create_parser()
    args = parser.parse_args()
    pc_df = get_physicell_df(args.pc_csv)
    bd_df = get_biodynamo_df(args.bd_csv)
    ts_df = get_tisim_df(args.ts_csv)
    ch_df = get_chaste_df(args.ch_csv)
    plot(pc_df,ts_df,ch_df,bd_df)

    return

if __name__ == "__main__":
    main()
