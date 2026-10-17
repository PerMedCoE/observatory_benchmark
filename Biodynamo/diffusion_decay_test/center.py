import numpy as np
import matplotlib.pyplot as plt

data5 = np.genfromtxt("data5.csv")
data10 = np.genfromtxt("data10.csv")
data20 = np.genfromtxt("data20.csv")
data40 = np.genfromtxt("data40.csv")


plt.plot(data40[:,0], data40[:,2], label="6 resolution")
plt.plot(data20[:,0], data20[:,2], label="12 resolution")
plt.plot(data10[:,0], data10[:,2], label="24 resolution")
plt.plot(data5[:,0], data5[:,2],   label="48 resolution")

an_time = [ 0.,          0.52631579,  1.05263158,  1.57894737,  2.10526316,  2.63157895,
  3.15789474,  3.68421053,  4.21052632,  4.73684211,  5.26315789,  5.78947368,
  6.31578947,  6.84210526,  7.36842105,  7.89473684,  8.42105263,  8.94736842,
  9.47368421, 10.        ]

an_conc = [10.,          5.93968034,  3.94462468,  3.18079231,  2.91133497,  2.81811149,
  2.78600674,  2.77496231,  2.77116386,  2.76985756,  2.76940833,  2.76925384,
  2.76920071,  2.76918244,  2.76917616,  2.76917399,  2.76917325,  2.769173,
  2.76917291,  2.76917288]

plt.plot(an_time, an_conc, label="analytical", linestyle="--", color="black")

plt.title("Concentration of central voxel against time")
plt.xlabel("Time (minutes)")
plt.ylabel(r"Concentration ($\mu$M)")
plt.xlim([0, 10])
plt.legend()
plt.show()


plt.clf()

error_time_low = np.zeros(20)
error_time_high = np.zeros(20)
for i in range(20):
    time = an_time[i]
    temp_low = 0
    count_low = 0
    while (temp_low < time):
        temp_low += 0.01
        count_low += 1

    temp_high = 0
    count_high = 0
    while (temp_high < time):
        temp_high += 0.001
        count_high += 1

    error_time_low[i] += count_low
    error_time_high[i] += count_high

error_time_low[19] = 999
error_time_high[19] = 9999

print(error_time_low)
print(error_time_high)

error40 = np.zeros(20)
error20 = np.zeros(20)
error10 = np.zeros(20)
error5 = np.zeros(20)
for i in range(20):
    error40[i] = (data40[int(error_time_low[i]), 2] - an_conc[i])/an_conc[i] * 100
    error20[i] = (data20[int(error_time_low[i]), 2] - an_conc[i])/an_conc[i] * 100
    error10[i] = (data10[int(error_time_high[i]), 2] - an_conc[i])/an_conc[i] * 100
    error5[i] = (data5[int(error_time_high[i]), 2] - an_conc[i])/an_conc[i] * 100


plt.plot(an_time, error40, label="6 resolution")
plt.plot(an_time, error20, label="12 resolution")
plt.plot(an_time, error10, label="24 resolution")
plt.plot(an_time, error5, label="48 resolution")


plt.title("Error in concentration of central voxel against time")
plt.xlabel("Time (minutes)")
plt.ylabel("Error (%)")
plt.xlim([0, 10])
plt.legend()
plt.show()
