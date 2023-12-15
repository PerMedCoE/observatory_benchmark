import re
import matplotlib.pyplot as plt

with open('tissuewidth.dat') as results_file:
    times = []
    tissue_widths = []
    num_cells = []
    for line in results_file:
        line = line.replace('\n', '')
        values = re.split('\t|,', line)
        if len(values) == 1:
            continue
        
        times.append(float(values[0]))
        tissue_widths.append(float(values[3]))
        num_cells.append(int(values[4]))

plt.plot(times, tissue_widths)
plt.title("2D Monolayer Diameter Over Time")
plt.xlabel("Time (hours)")
plt.ylabel("Tissue Diameter (micrometers)")
plt.show()

plt.plot(times, num_cells)
plt.title("Number of Cells in 2D Monolayer Over Time")
plt.xlabel("Time (hours)")
plt.ylabel("Number of Cells")
plt.show()

