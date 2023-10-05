# from pctk.multicellds import MultiCellDS
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

# pc_file = "/home/bscuser/BSC/unittestscellcycle/output_unit_test8/cell_volumes.csv"
# pc_df = pd.read_csv(pc_file,index_col=0)
# pc_df['dt'] = pc_df['dt']/60

# ch_df = pd.read_csv("chaste_volumes_fijo_stohastic.csv",usecols=["time","cellid","volume","current_phase"])

# pc_init_vol = pc_df.loc[0,'total_volume']
# ch_init_vol = ch_df.loc[0,"volume"]
# dts= []
# vols = []
# for dt,idx in pc_df.groupby(['dt']).groups.items():
#     dts.append(dt)
#     total_cell_volume = 0
#     for i in idx.values:
#         total_cell_volume += pc_df.loc[i,'total_volume']
#     print(total_cell_volume/pc_init_vol)
#     vols.append(total_cell_volume/pc_init_vol)
# vols=[100*x for x in vols]
# plt.scatter(dts,vols,label="PhysiCell",color='green', alpha=0.6)

# dts= []
# vols = []
# for dt,idx in ch_df.groupby(['time']).groups.items():
#     dts.append(dt)
#     total_cell_volume = 0
#     for i in idx.values:
#         total_cell_volume += ch_df.loc[i,'volume']
#         # print(ch_df.loc[i,'volume'])
#         # print(i)
#     vols.append(total_cell_volume/ch_init_vol)
# vols=[100*x for x in vols]
# plt.scatter(dts,vols,label="Chaste",color='blue', alpha=0.6)
# plt.legend()
# plt.xlabel(xlabel="Time (hours)")
# plt.ylabel(ylabel="Percentage of initial volume")
# plt.title(label = 'Stohastic Cell Cycle total volume')
# plt.savefig("/home/bscuser/BSC/unittestscellcycle/output_unit_test8/stohastic_cell_cycle.png",dpi=200)
# plt.show()
# get percentage of initial volume in chaste 
# 
fig,ax = plt.subplots()
pc_file = "/home/thalia/BSC/mounted/cell_cycle/output_unit_test7/cell_volumes_2.csv"
pc_df = pd.read_csv(pc_file,index_col=0)
pc_df['dt'] = pc_df['dt']/60
print(pc_df)
ch_df = pd.read_csv("chaste_volumes_fijo.csv",usecols=["time","cellid","volume","current_phase"])

pc_init_vol = pc_df.iloc[0,2]

ch_init_vol = ch_df.loc[0,"volume"]
dts= []
vols = []
for dt,idx in pc_df.groupby(['dt']).groups.items():
    dts.append(dt)
    total_cell_volume = 0
    for i in idx.values:
        total_cell_volume += pc_df.loc[i,'total_volume']
    perc = (total_cell_volume/(len(idx.values)))/pc_init_vol
    vols.append(perc)
vols=[100*x for x in vols]
plt.plot(dts,vols,label="PhysiCell",color='green' ,linewidth=2)
plt.show()

dts= []
vols = []
for dt,idx in ch_df.groupby(['time']).groups.items():
    dts.append(dt)
    total_cell_volume = 0
    for i in idx.values:
        total_cell_volume += ch_df.loc[i,'volume']

    perc = (total_cell_volume/(len(idx.values)))/ch_init_vol
    vols.append(perc)

vols=[100*x for x in vols]

ax.plot(dts,vols,label="Chaste",color='blue',linewidth=2)

tisim_arr = [1,1.00454,1.00902,1.01351,1.01801,1.02253,1.02706,1.0316,1.03616,1.04073,1.04531,1.04991,1.05452,1.05915,1.06378,1.06844,1.0731,1.07778,1.08247,1.08718,1.0919,1.09663,1.10138,1.10614,1.11091,1.1157,1.1205,1.12532,1.13014,1.13499,1.13984,1.14471,1.1496,1.1545,1.15941,1.16433,1.16927,1.17423,1.1792,1.18418,1.18917,1.19418,1.19921,1.20425,1.2093,1.21436,1.21944,1.22454,1.22965,1.23477,1.23991,1.24506,1.25022,1.2554,1.2606,1.26581,1.27103,1.27627,1.28152,1.28678,1.29206,1.29736,1.30267,1.30799,1.31333,1.31868,1.32405,1.32943,1.33483,1.34024,1.34566,1.3511,1.35656,1.36203,1.36751,1.37301,1.37852,1.38405,1.38959,1.39515,1.40072,1.40631,1.41191,1.41753,1.42316,1.42881,1.43447,1.44015,1.44584,1.45155,1.45727,1.463,1.46876,1.47452,1.4803,1.4861,1.49191,1.49774,1.50358,1.50944,1.51531,1.5212,1.5271,1.53302,1.53895,1.5449,1.55087,1.55685,1.56284,1.56885,1.57488,1.58092,1.58698,1.59305,1.59913,1.60524,1.61136,1.61749,1.62364,1.6298,1.63598,1.64218,1.64839,1.65462,1.66086,1.66712,1.6734,1.67969,1.68599,1.69231,1.69865,1.70501,1.71137,1.71776,1.72416,1.73058,1.73701,1.74346,1.74992,1.7564,1.7629,1.76941,1.77594,1.78248,1.78905,1.79562,1.80221,1.80882,1.81545,1.82209,1.82875,1.83542,1.84211,1.84882,1.85554,1.86228,1.86903,1.8758,1.88259,1.88939,1.89621,1.90305,1.9099,1.91677,1.92366,1.93056,1.93748,1.94441,1.95137,1.95833,1.96532,1.97232,1.97934,1.98637,1.99343,1.99625,1.759,1.54133,1.34241,1.16138,1,1.00443,1.0089,1.01339,1.0179,1.02241,1.02694,1.03149,1.03604,1.04061,1.0452,1.0498,1.05441,1.05903,1.06367,1.06832,1.07298,1.07766,1.08235,1.08706,1.09178,1.09651,1.10126,1.10602,1.11079,1.11558,1.12038,1.12519,1.13002,1.13487,1.13972,1.14459,1.14948,1.15437,1.15929,1.16421,1.16915,1.1741,1.17907,1.18405,1.18905,1.19406,1.19908,1.20412,1.20917,1.21424,1.21932,1.22441,1.22952,1.23464,1.23978,1.24493,1.2501,1.25527,1.26047,1.26568,1.2709,1.27614,1.28139,1.28665,1.29193,1.29723,1.30254,1.30786,1.3132,1.31855,1.32392,1.3293,1.33469,1.3401,1.34553,1.35097,1.35642,1.36189,1.36737,1.37287,1.37839,1.38391,1.38946,1.39501,1.40059,1.40617,1.41177,1.41739,1.42302,1.42867,1.43433,1.44001,1.4457,1.4514,1.45712,1.46286,1.46861,1.47438,1.48016,1.48596,1.49177,1.49759,1.50344,1.50929,1.51517,1.52105,1.52696,1.53287,1.53881,1.54475,1.55072,1.5567,1.56269,1.5687,1.57473,1.58077,1.58682,1.5929,1.59898,1.60508,1.6112,1.61734,1.62349,1.62965,1.63583,1.64203,1.64824,1.65446,1.66071,1.66697,1.67324,1.67953,1.68583,1.69216,1.69849,1.70485,1.71121,1.7176,1.724,1.73042,1.73685,1.7433,1.74976,1.75624,1.76274,1.76925,1.77578,1.78232,1.78888,1.79546,1.80205,1.80866,1.81528,1.82192,1.82858,1.83525,1.84194,1.84865,1.85537,1.86211,1.86886,1.87563,1.88242,1.88922,1.89604,1.90288,1.90973,1.9166,1.92349,1.93039,1.93731,1.94424,1.95119,1.95816,1.96515,1.97215,1.97916,1.9862,1.99325,2.00034,1.76469,1.54654,1.34716,1.16569,1.0013,1.00439,1.00887,1.01336,1.01786,1.02238,1.02691,1.03145,1.03601,1.04058,1.04516,1.04976,1.05437,1.05899,1.06363,1.06828,1.07295,1.07762,1.08231,1.08702,1.09174,1.09647,1.10122,1.10598,1.11075,1.11554,1.12034,1.12515,1.12998,1.13483,1.13968,1.14455,1.14944,1.15433,1.15924,1.16417,1.16911,1.17406,1.17903,1.18401,1.18901,1.19402,1.19904,1.20408,1.20913,1.2142,1.21928,1.22437,1.22948,1.2346,1.23974,1.24489,1.25005,1.25523,1.26043,1.26563,1.27086,1.27609,1.28134,1.28661,1.29189,1.29718,1.30249,1.30781,1.31315,1.3185,1.32387,1.32925,1.33465,1.34006,1.34548,1.35092,1.35638,1.36184,1.36733,1.37283,1.37834,1.38387,1.38941,1.39497,1.40054,1.40613,1.41173,1.41734,1.42297,1.42862,1.43428,1.43996,1.44565,1.45136,1.45708,1.46281,1.46856,1.47433,1.48011,1.48591,1.49172,1.49755,1.50339,1.50924,1.51512,1.521,1.52691,1.53282,1.53876,1.54471,1.55067,1.55665,1.56264,1.56865,1.57468,1.58072,1.58677,1.59284,1.59893,1.60503,1.61115,1.61728,1.62343,1.6296,1.63578]
tisim_arr = [x*100 for x in tisim_arr]
tisim_dt = [x/60 for x in range(0,2881,6)]

ax.plot(tisim_dt,tisim_arr,label="TiSim",color  = '#ffd343',linewidth=2)


plt.xlabel(xlabel="Time (hours)",fontsize=12,color = '#262626')
plt.ylabel(ylabel="Percentage of initial volume",fontsize=12,color = '#262626')
plt.title(label = 'Fixed Cell Cycle Total Volume',color = '#262626')

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
ax.legend(bbox_to_anchor = (1.0,1.0),loc='upper left')
plt.tight_layout()
plt.savefig("/home/thalia/BSC/mounted/cell_cycle/output_unit_test7/fixed_cell_cycle_2.png",dpi=200)
plt.show()