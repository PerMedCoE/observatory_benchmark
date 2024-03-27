import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt("data.csv")

time = data[:,0]
avg_conc = data[:,1]


plt.plot(time, avg_conc)
plt.xlabel("Time (minutes)")
plt.ylabel("Concentration")
plt.title("Average Concentration of All Voxels")
plt.ylim([-0.1, 10.1])
plt.show()

