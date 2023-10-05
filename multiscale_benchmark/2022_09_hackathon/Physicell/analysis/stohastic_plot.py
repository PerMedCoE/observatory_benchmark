# from pctk.multicellds import MultiCellDS
from re import L
from scipy.io import loadmat
import os
from glob import glob
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
from pathlib import Path
import pandas as pd


# extract chaste data begining
# ch_file = '/home/bscuser/BSC/Benchmarks/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Chaste/unit_test_cellcycle_stoch/results/cellcycle_stochastic.dat'
# with open(ch_file, "r") as f:
#     ch_raw= []
#     no_line = 1
#     for line in f.read().splitlines():
#         sp_line = line.split(" ")
#         if no_line == 1:
#             print(sp_line)
#         sp_line = list(filter(None, sp_line))
#         if no_line == 1:
#             print(sp_line)
#         no_cells=len(sp_line)//11
#         ch_raw.append(sp_line[0:12])
#         # print('--',no_line,'--')
#         # print('cell 0 size ',len(sp_line[0:12]))
        
#         if no_cells != 1:

#             # print(len(sp_line))
#             for i in range(1,no_cells):
#                 temp = []
#                 temp.append(sp_line[0])
#                 # print(i*11+1,i*11+11+2)
#                 # print(i,"st cell")
#                 # print('cell',i,' size ',len(temp + sp_line[i*11+1:i*11+11+1]))
#                 ch_raw.append(temp + sp_line[i*11+1:i*11+11+1])
#         no_line=no_line+1
# print(ch_raw)
# ch_data = pd.DataFrame(ch_raw,columns=["time","cellid","x_pos","y_pos","z_pos","g1_duration","s_duration","g2_duration","m_duration","current_phase","target_area","volume"])
# ch_data.to_csv("chaste_volumes_fijo_stohastic.csv")

# extract chaste data end
# cell_cycle 7

# plot stohastic
# fig,ax = plt.subplots()
# pc_file = "/home/thalia/BSC/mounted/cell_cycle/benchmark_ABMs/PhysiCell/output_unit_test8/cell_volumes.csv"
# pc_df = pd.read_csv(pc_file,index_col=0)
# pc_df['dt'] = pc_df['dt']/60

# ch_df = pd.read_csv("chaste_volumes_fijo_stohastic.csv",usecols=["time","cellid","volume","current_phase"])

# pc_init_vol = pc_df.iloc[0,2]
# ch_init_vol = ch_df.loc[0,"volume"]
# cell_ids= []
# dts =[]
# for cell_id,idx in pc_df.groupby(['id']).groups.items():
#     vols = []
#     cell_ids.append(cell_id)
#     for i in idx.values:
#         vols.append(pc_df.loc[i,'volume'])
#         dts.append(pc_df.loc[i,'dt'])
#     plt.plot(dts,vols,label="PhysiCell",color='green' ,linewidth=2)
# vols=[100*x for x in vols]
# plt.plot(dts,vols,label="PhysiCell",color='green' ,linewidth=2)

# dts= []
# vols = []
# for dt,idx in ch_df.groupby(['time']).groups.items():
#     dts.append(dt)
#     total_cell_volume = 0
#     for i in idx.values:
#         total_cell_volume += ch_df.loc[i,'volume']

#     perc = (total_cell_volume/(len(idx.values)))/ch_init_vol
#     vols.append(perc)

# vols=[100*x for x in vols]

# ax.plot(dts,vols,label="Chaste",color='blue',linewidth=2)
# plt.xlabel(xlabel="Time (hours)",fontsize=12,color = '#262626')
# plt.ylabel(ylabel="Percentage of initial volume",fontsize=12,color = '#262626')
# plt.title(label = 'Fixed Cell Cycle Total Volume',color = '#262626')


# # ax.legend()
# ax.legend(bbox_to_anchor = (1.0,1.0),loc='upper left')
# plt.tight_layout()
# plt.savefig("/home/bscuser/BSC/unittestscellcycle/output_unit_test8/stohastic_cell_cycle.png",dpi=200)
# plt.show()



# -*- coding: utf-8 -*-
"""
Created on Thu Oct 27 16:48:54 2022

@author: bscuser
"""

# from pctk.multicellds import MultiCellDS
import numpy as np
from scipy.io import loadmat
import os
from glob import glob
import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path
import pandas as pd
import matplotlib as mpl
import matplotlib.pylab as pl

from matplotlib.colors import ListedColormap

# extract chaste data begining
# ch_file = '/home/bscuser/BSC/Benchmarks/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Chaste/unit_test_cellcycle_stoch/results/cellcycle_stochastic.dat'
# with open(ch_file, "r") as f:
#     ch_raw= []
#     no_line = 1
#     for line in f.read().splitlines():
#         sp_line = line.split(" ")
#         if no_line == 1:
#             print(sp_line)
#         sp_line = list(filter(None, sp_line))
#         if no_line == 1:
#             print(sp_line)
#         no_cells=len(sp_line)//11
#         ch_raw.append(sp_line[0:12])
#         # print('--',no_line,'--')
#         # print('cell 0 size ',len(sp_line[0:12]))
        
#         if no_cells != 1:

#             # print(len(sp_line))
#             for i in range(1,no_cells):
#                 temp = []
#                 temp.append(sp_line[0])
#                 # print(i*11+1,i*11+11+2)
#                 # print(i,"st cell")
#                 # print('cell',i,' size ',len(temp + sp_line[i*11+1:i*11+11+1]))
#                 ch_raw.append(temp + sp_line[i*11+1:i*11+11+1])
#         no_line=no_line+1
# print(ch_raw)
# ch_data = pd.DataFrame(ch_raw,columns=["time","cellid","x_pos","y_pos","z_pos","g1_duration","s_duration","g2_duration","m_duration","current_phase","target_area","volume"])
# ch_data.to_csv("chaste_volumes_fijo_stohastic.csv")

# extract chaste data end
# cell_cycle 7

# plot stohastic
fig,ax = plt.subplots()
pc_file = "/home/thalia/BSC/mounted/cell_cycle/benchmark_ABMs/PhysiCell/output_unit_test8/cell_volumes.csv"
pc_df = pd.read_csv(pc_file,index_col=0)
pc_df['dt'] = pc_df['dt']/60


pc_init_vol = pc_df.iloc[0,2]
pc_group =  pc_df.groupby(['id']).groups.items()
num_cels = len(pc_group)
colors = pl.cm.Greens(np.linspace(0,1,num_cels*2))
j=2
# j=0
# colors = ['green','red','blue','purple']
for cell_id,idx in pc_group:
    vols = []
    dts = []
    for i in idx.values:
        vols.append(pc_df.loc[i,'total_volume'])
        dts.append(pc_df.loc[i,'dt'])
    # plt.plot(dts,vols,label="PhysiCell", color=colors[j] ,linewidth=2)
    if cell_id!=num_cels-1:
        plt.plot(dts,vols, color=colors[j] ,linewidth=2)
    else:
        plt.plot(dts,vols, color=colors[j],label = 'PhysiCell' ,linewidth=2)
    j+=1
 
    
ch_df = pd.read_csv("chaste_volumes_fijo_stohastic.csv",usecols=["time","cellid","volume","current_phase"]) 
ch_group =  ch_df.groupby(['cellid']).groups.items()
num_cels = len(ch_group)
colors = pl.cm.Blues(np.linspace(0,1,num_cels*2))
j=4
for cell_id,idx in ch_group:
    vols = []
    dts = []
    for i in idx.values:
        vols.append(ch_df.loc[i,'volume']*1000)
        dts.append(ch_df.loc[i,'time'])
    if cell_id!=num_cels-1:
        plt.plot(dts,vols, color=colors[j] ,linewidth=2)
    else:
        plt.plot(dts,vols, color=colors[j],label='Chaste' ,linewidth=2)

    j+=1

colors = pl.cm.YlOrBr(np.linspace(0,1,10))
v1=[1,1.0202,1.04068,1.06142,1.08244,1.10068,1.12222,1.14403,1.16612,1.18528,1.2079,1.23081,1.25067,1.27411,1.29785,1.32187,1.34619,1.36728,1.39215,1.41732,1.44279,1.46487,1.49091,1.51725,1.54391,1.567,1.59423,1.62178,1.64964,1.67377,1.70223,1.731,1.76009,1.78529,1.81499,1.84501,1.87537,1.90165,1.93262,1.96393,1.99557,1.01363,1.03507,1.05369,1.07569,1.09799,1.12061,1.14023,1.16342,1.18692,1.21073,1.23139,1.25579,1.28052,1.30556,1.32728,1.35293,1.37891,1.40522,1.42803,1.45496,1.48222,1.50982,1.53375,1.56199,1.59057,1.61949,1.64456,1.67414,1.70407,1.73435,1.76059,1.79154,1.82284,1.85451,1.88195,1.9143,1.94701,1.9801,1,1.0117,1.02942,1.05035,1.07157,1.09307,1.11173,1.13376,1.15608,1.17869,1.19831,1.22146,1.24492,1.26867,1.28927,1.31358,1.33819,1.36311,1.38472,1.41021,1.43602,1.46213]
t1=[0,0.497778,0.995556,1.49333,1.99111,2.41778,2.91556,3.41333,3.91111,4.33778,4.83556,5.33333,5.76,6.25778,6.75556,7.25333,7.75111,8.17778,8.67556,9.17333,9.67111,10.0978,10.5956,11.0933,11.5911,12.0178,12.5156,13.0133,13.5111,13.9378,14.4356,14.9333,15.4311,15.8578,16.3556,16.8533,17.3511,17.7778,18.2756,18.7733,19.2711,19.7333,20.2311,20.6578,21.1556,21.6533,22.1511,22.5778,23.0756,23.5733,24.0711,24.4978,24.9956,25.4933,25.9911,26.4178,26.9156,27.4133,27.9111,28.3378,28.8356,29.3333,29.8311,30.2578,30.7556,31.2533,31.7511,32.1778,32.6756,33.1733,33.6711,34.0978,34.5956,35.0933,35.5911,36.0178,36.5156,37.0133,37.5111,37.9733,38.4711,38.8978,39.3956,39.8933,40.3911,40.8178,41.3156,41.8133,42.3111,42.7378,43.2356,43.7333,44.2311,44.6578,45.1556,45.6533,46.1511,46.5778,47.0756,47.5733,48.0711]
plt.plot(t1,[100*x for x in v1], color=colors[2],label='TiSim' ,linewidth=2)

v2=[1.01641,1.04229,1.06481,1.0915,1.11864,1.14621,1.17021,1.19863,1.2275,1.25683,1.28234,1.31254,1.3432,1.37434,1.40141,1.43344,1.46596,1.49896,1.52764,1.56156,1.59598,1.6309,1.66123,1.69709,1.73346,1.77035,1.80238,1.84024,1.87863,1.91754,1.95132,1.99123,1.01341,1.03238,1.04882,1.06823,1.08788,1.10776,1.12644,1.14679,1.16443,1.18523,1.20628,1.22758,1.24603,1.2678,1.28981,1.31208,1.33137,1.35411,1.37711,1.40037,1.42051,1.44425,1.46826,1.49253,1.51355,1.53831,1.56335,1.58865]
t2=[19.7333,20.2311,20.6578,21.1556,21.6533,22.1511,22.5778,23.0756,23.5733,24.0711,24.4978,24.9956,25.4933,25.9911,26.4178,26.9156,27.4133,27.9111,28.3378,28.8356,29.3333,29.8311,30.2578,30.7556,31.2533,31.7511,32.1778,32.6756,33.1733,33.6711,34.0978,34.5956,35.0933,35.5911,36.0178,36.5156,37.0133,37.5111,37.9733,38.4711,38.8978,39.3956,39.8933,40.3911,40.8178,41.3156,41.8133,42.3111,42.7378,43.2356,43.7333,44.2311,44.6578,45.1556,45.6533,46.1511,46.5778,47.0756,47.5733,48.0711]
plt.plot(t2,[100*x for x in v2], color=colors[4],label='TiSim' ,linewidth=2)

v3=[1.01348,1.03256,1.0491,1.06862,1.08838,1.10839,1.12718,1.14765,1.1654,1.18633,1.20752,1.22895,1.24752,1.26942,1.29158,1.31399,1.33341,1.35631,1.37946,1.40288,1.42316,1.44706,1.47124,1.49568,1.51684,1.54178,1.567,1.59249]
t3=[35.0933,35.5911,36.0178,36.5156,37.0133,37.5111,37.9733,38.4711,38.8978,39.3956,39.8933,40.3911,40.8178,41.3156,41.8133,42.3111,42.7378,43.2356,43.7333,44.2311,44.6578,45.1556,45.6533,46.1511,46.5778,47.0756,47.5733,48.0711]
plt.plot(t3,[100*x for x in v3], color=colors[6],label='TiSim' ,linewidth=2)

v4=[1,1.01129,1.02838,1.04857,1.06902,1.08973,1.10769,1.1289,1.15038,1.17212,1.19098,1.21323,1.23576,1.25857,1.27834,1.30166,1.32527,1.34916,1.36987,1.39429,1.419,1.444]
t4=[37.9733,38.4711,38.8978,39.3956,39.8933,40.3911,40.8178,41.3156,41.8133,42.3111,42.7378,43.2356,43.7333,44.2311,44.6578,45.1556,45.6533,46.1511,46.5778,47.0756,47.5733,48.0711]
plt.plot(t4,[100*x for x in v4], color=colors[8],label='TiSim' ,linewidth=2)

# ok now you have to check when a cell is
plt.xlabel(xlabel="Time (mins)",fontsize=12,color = '#262626')
plt.ylabel(ylabel="Total volume",fontsize=12,color = '#262626')
plt.title(label = 'Stochastic Cell Cycle Total Volume',color = '#262626')


ax.legend(labels= ["Physicel","Chaste"])
ax.legend(bbox_to_anchor = (1.0,1.0),loc='upper left')
plt.tight_layout()
plt.savefig("/home/thalia/BSC/mounted/cell_cycle/benchmark_ABMs/PhysiCell/output_unit_test8/stohastic_cell_cycle.png",dpi=200)
plt.show()