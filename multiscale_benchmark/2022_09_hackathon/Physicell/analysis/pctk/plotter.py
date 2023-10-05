import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
file = "cell.csv"

df = pd.read_csv("/home/bscuser/BSC/pctk/src/pctk/cell1.csv")

total_volume = df.iloc[0].at["total_volume"]
df["percentage"] = (df["total_volume"]/total_volume)*100
df["timepoint"] = df["Unnamed: 0"]*30


plt.fill_between(df["timepoint"],df["percentage"],0)
plt.xlabel('Time (Minutes)', fontsize=10)
plt.ylabel('Volume (Percentage of initial Value)', fontsize=10)
# plt.show()
plt.savefig('totalvolume.png', dpi=250)
# calculate in new column percentage of initial total volume
# plot it against time
