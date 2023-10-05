# plot distance travelled
import math
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn import preprocessing

def Euclidean_Dist(df1,df2, cols=['x','y']):
    print(df1.reset_index()-df2.reset_index())
    return np.linalg.norm(df1.reset_index() - df2.reset_index())

data_pc = pd.read_csv("/home/thalia/BSC/NEW_BENCH/Physicell_template/mechanics_pushing_out/cells_position_time.csv",index_col=0)
min_max_scaler = preprocessing.MinMaxScaler()
dt_pc =  data_pc[data_pc['id']==1]['dt']

pc_dist =  abs(data_pc[data_pc['id']==0]['x'].reset_index() - data_pc[data_pc['id']==1]['x'].reset_index())

pc_dist = min_max_scaler.fit(pc_dist['x'].values.reshape(-1, 1) )
print(dt_pc)
data_biod = pd.read_csv("/home/thalia/BSC/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_pushing/marenostrum_results/positions.csv"
,header = None,sep='\t|,',engine='python')
bd_dist = abs(data_biod[1] - data_biod[4])
bd_dist = min_max_scaler.fit(bd_dist.values.reshape(-1, 1) )

x1 = [0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1005,1.20487,1.27238,1.30466,1.32207,1.3309,1.33522,1.33729,1.33828,1.33875,1.33897,1.33907,1.33912,1.33914,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916,1.33916]
x2 = [3,2.9,2.8,2.7,2.6,2.5,2.4,2.3,2.2,2.1,2,1.8995,1.79513,1.72762,1.69534,1.67793,1.6691,1.66478,1.66271,1.66172,1.66125,1.66103,1.66093,1.66088,1.66086,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084,1.66084]
ts_dist = [abs(element1 - element2) for (element1, element2) in zip(x1, x2)]
# ts_dist = [x+0.2 for x in ts_dist]
ts_dist = np.reshape(ts_dist, (-1, 1))
# ts_dist = np.array(ts_dist).reshape(-1,1)
ts_dist = min_max_scaler.fit_transform(ts_dist )


# dt_pc = np.linspace(0,1,101)
dt_bd = np.linspace(0,10,100)
plt.plot(dt_pc,pc_dist,label = 'Physicell',color='green')
plt.plot(dt_bd,bd_dist,label = 'Biodynamo',alpha=0.5,color = 'red')
plt.plot(dt_pc,ts_dist,label = 'TiSim', color  = '#ffd343')
plt.ylabel("Normalized Distance between two cells")
plt.xlabel("Time (minutes)")
plt.legend()
plt.title("Mechanics, two cells pushing each other")
plt.savefig("mechanicspushingslines.png",dpi=200)
plt.show()


# fig, ax = plt.subplots()

# df.groupby(by = 'id')
# df_0 = df[df['id']==0]
# df_1 = df[df['id']==1]
# plt.plot(df_0['dt'],df_0['x'],label = 'Cell0')
# plt.plot(df_1['dt'],df_1['x'],label = 'Cell1')
# ax.set(xlabel='t (min)', ylabel='x position',title="Mechanics, two cells pushing each other")
# plt.legend()
# plt.savefig('/home/bscuser/BSC/Benchmarks/PhysicellBenchmarks/PhysiCell/PhysiCell/output_unit_test5/postionvstime.png')
# plt.show()