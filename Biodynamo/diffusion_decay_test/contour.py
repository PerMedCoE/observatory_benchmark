import numpy as np
import matplotlib.pyplot as plt


N=48

bl = 240/N

data= np.genfromtxt("contour"+str(int(bl))+".csv")

ticks = np.array([-120, -60, 0, 60, 120])
plt.xticks(ticks)
plt.yticks(ticks)

extent=(-120,120,-120,120)
plt.imshow(data, interpolation='nearest', extent=extent, origin='lower', cmap="coolwarm")
plt.colorbar(label=r"Concentration ($\mu$M)")



line = np.linspace(-120, 120, 2)
pos=np.zeros(2)


for i in range(N-1):
     plt.plot(line, pos-120+bl+bl*i, color="black", alpha=0.2)
     plt.plot(pos-120+bl+bl*i, line, color="black", alpha=0.2)


plt.title("Concentration at 10 minutes in x-y plane")
plt.xlabel(r"x-distance ($\mu$m)")
plt.ylabel(r"y-distance ($\mu$m)")


plt.show()
