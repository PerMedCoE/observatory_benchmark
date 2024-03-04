import pandas as pd
from pathlib import Path
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
def create_png(data):
    fig,ax = plt.subplots()
    bd_init_vol = data.iloc[0,1]
    print(bd_init_vol)
    dts= []
    vols = []
    for dt,idx in data.groupby(['timestep']).groups.items():
        dts.append(dt)
        total_cell_volume = 0
        for i in idx.values:
            total_cell_volume += data.loc[i,'volume']
        perc = (total_cell_volume/(len(idx.values)))/bd_init_vol
        vols.append(perc)
    vols=[100*x for x in vols]
    df_dts_vol = pd.DataFrame({"timestep":dts,"volume":vols})
    df_dts_vol.to_csv('volume_perncentage_over_time.csv')
    plt.plot(dts,vols,label="Biodynamo",color='green' ,linewidth=2)
    plt.xlabel(xlabel="Time (hours)",fontsize=12,color = '#262626')
    plt.ylabel(ylabel="Percentage of initial volume",fontsize=12,color = '#262626')
    plt.title(label = 'Biodynamo Fixed Cell Cycle Total Volume',color = '#262626')

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
    # ax.legend()
    # plt.plot(dts,vols,label="PhysiCell",color='green' ,linewidth=2)
    ax.legend(bbox_to_anchor = (1.0,1.0),loc='upper left')
    plt.tight_layout()
    plt.savefig("fixed_cell_cycle_volumes.png")
    plt.show()

if __name__ == '__main__':
    file1 = "cell-0.csv"
    file2 = "cell-2.csv"
    file3 = "cell-2.csv"
    file4 = "cell-4.csv"

    df1 = pd.read_csv(file1,header=None,names=["timestep","volume","cell_id","index"],usecols=[0,1,2])
    df2 = pd.read_csv(file2,header=None,names=["timestep","volume","cell_id","index"],usecols=[0,1,2])
    df3 = pd.read_csv(file3,header=None,names=["timestep","volume","cell_id","index"],usecols=[0,1,2])
    df4 = pd.read_csv(file4,header=None,names=["timestep","volume","cell_id","index"],usecols=[0,1,2])
    df =pd.concat([df1,df2,df3,df4], ignore_index=True)
    create_png(df)
    print(df)