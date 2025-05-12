import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import os

output_folder=("PhysiCell/results/fixed_cell_cycle/cell_volumes.csv")
pc_df = pd.read_csv(output_folder,float_precision='round_trip').sort_values(by=['dt']).reset_index(drop=True)

output_folder=("Biodynamo/unit_test_cellcycle/new_results/cell-0-sim1.csv")
bd_df = pd.read_csv(output_folder,header=None)
bd_df.columns = ['timestep', 'volume', 'Phase', 'Age']
bd_df['vol']= bd_df['volume']/bd_df['volume'][0]


output_folder=("Chaste/unit_test_cellcycle/results/cellcycle_fixed.dat")
ch_df = pd.DataFrame(columns=["dt","id","x","y","z","g1_duration","s_duration","g2_duration","m_duration","current_phase","target_area","volume"])
with open(output_folder, "r") as f:
    for line in f.read().splitlines():
        data = line.split()
        data = [float(x) if x.replace('.', '', 1).isdigit() else x for x in data]
        dt = data[0]
        for i in range(0,len(data)//11):
            row = {'dt': dt, 'id': data[1+11*i], 'x': data[2+11*i], 'y': data[3+11*i], 'z': data[4+11*i], 'g1_duration': data[5+11*i], 's_duration': data[6+11*i], 'g2_duration': data[7+11*i], 'm_duration': data[8+11*i], 'current_phase': data[9+11*i], 'target_area': data[10+11*i], 'volume': data[11+11*i]}
            row = pd.Series(row)
            df2 = pd.DataFrame(row).transpose()

            ch_df =pd.concat([ch_df,df2],ignore_index=True)

file = "Tisim/unit_test_cellcycle/cell cycle fix.csv"
data = pd.read_csv(file, header=0)
time_steps = data['time (hour)']
volume_columns = data.columns[1:]  # Assuming all other columns are cell volumes

average_volumes = data[volume_columns].mean(axis=1, skipna=True)
initial_total_volume = average_volumes.iloc[0]

percentage_total_volumes = (average_volumes / initial_total_volume)*100
# print(percentage_total_volumes)
# Create a new DataFrame with time steps and percentage of total volumes
ts_df = pd.DataFrame({
    'timestep': time_steps,
    'volumes': percentage_total_volumes
})

# Update font settings with fallback options
plt.rcParams.update({
    'font.family': 'sans-serif',
    'font.sans-serif': ['DejaVu Sans', 'Helvetica', 'Arial', 'sans-serif'],
    'font.size': 8,
    'axes.labelsize': 8,
    'axes.titlesize': 8,
    'xtick.labelsize': 8,
    'ytick.labelsize': 8,
    'legend.fontsize': 8,
    'lines.linewidth': 1.5,
    'axes.linewidth': 0.5,
    'xtick.major.width': 0.5,
    'ytick.major.width': 0.5,
    'xtick.major.size': 3,
    'ytick.major.size': 3,
    'figure.dpi': 400
})

# Create figure with specific dimensions
fig, ax = plt.subplots(figsize=(8.9, 4))  # Nature's column width

# Normalize time to hours
pc_df['dt'] = pc_df['dt'] / 60
pc_init_vol = pc_df.iloc[0]["total_volume"]

# Compute average volume per time step (normalized)
pc_avg_vol = pc_df.groupby('dt')['total_volume'].mean()
pc_dts = pc_avg_vol.index
pc_vols = (pc_avg_vol / pc_init_vol * 100).tolist()

# Define consistent colors and linestyles
colors = {
    'BioDynaMo': '#e41a1c',   # Red
    'Chaste': '#377eb8',      # Blue
    'PhysiCell': '#4daf4a',   # Green
    'TiSim': '#984ea3'        # Purple
}

linestyles = {
    'BioDynaMo': '-',   # Solid
    'Chaste': '--',     # Dashed
    'PhysiCell': '-.',  # Dash-dot
    'TiSim': ':'        # Dotted
}

# Plot all simulators with consistent styling
ax.plot(pc_dts, pc_vols, 
        label="PhysiCell", 
        color=colors['PhysiCell'], 
        linestyle=linestyles['PhysiCell'], 
        linewidth=1.5)

# Chaste
ch_init_vol = ch_df.loc[0, "volume"]
ch_avg_vol = ch_df.groupby('dt')['volume'].mean()
dts = ch_avg_vol.index
vols = (ch_avg_vol / ch_init_vol * 100).tolist()
ax.plot(dts, vols, 
        label="Chaste", 
        color=colors['Chaste'], 
        linestyle=linestyles['Chaste'], 
        linewidth=1.5)

# TiSim
ax.plot(ts_df['timestep'], ts_df['volumes'], 
        label="TiSim", 
        color=colors['TiSim'], 
        linestyle=linestyles['TiSim'], 
        linewidth=1.5)

# BioDynaMo
ax.plot(bd_df['timestep'], bd_df["vol"] * 100, 
        label="BioDynaMo", 
        color=colors['BioDynaMo'], 
        linestyle=linestyles['BioDynaMo'], 
        linewidth=1.5)

# Define colorblind-friendly colors for cell cycle phases
phase_colors = {
    'G0/G1': '#E69F00',  # Orange
    'S': '#56B4E9',      # Sky blue
    'G2': '#009E73',     # Green
    'M': '#CC79A7'       # Pink
}

# Add phase background rectangles with increased contrast
for i in range(3):  # repeat 3 cell cycles
    base = 18 * i
    phases = [
        (base, 7, phase_colors['G0/G1'], 'G0/G1'),
        (base + 7, 6, phase_colors['S'], 'S'),
        (base + 13, 3, phase_colors['G2'], 'G2'),
        (base + 16, 2, phase_colors['M'], 'M'),
    ]
    for x, w, color, label in phases:
        # Only add text if the phase block is within the plot limits
        if x + w <= 50:
            # Add rectangle with increased opacity and subtle border
            ax.add_patch(patches.Rectangle((x, 50), w, 170, 
                                         facecolor=color, 
                                         edgecolor='black',  # Added border
                                         linewidth=0.5,      # Thin border
                                         alpha=0.1))         # Border opacity
            # Center text in each phase block
            ax.text(x + w/2, 210, label, 
                   color='black',
                   alpha=0.7,
                   fontsize=8,
                   ha='center')

# Remove top and right spines
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

# Add subtle grid
ax.grid(True, alpha=0.3, linewidth=0.5)

# Set axis limits and labels
ax.set_xlim(0, 48)
ax.set_ylim(90, 220)
ax.set_xlabel("Time (hours)", labelpad=2, fontsize=10)
ax.set_ylabel("% of initial volume", labelpad=2, fontsize=10)

# Add legend below the plot
ax.legend(bbox_to_anchor=(0.5, -0.15), 
         loc='upper center',
         ncol=4,  # Arrange legend items in a row
         frameon=False,
         fontsize=10)

# Adjust layout to accommodate the legend below
plt.tight_layout()
plt.subplots_adjust(bottom=0.2)  # Add more space at the bottom for the legend

# Save in vector formats
save_dir = "./ResultAnalysis/plots/cell_cycle_plots"
os.makedirs(save_dir, exist_ok=True)

# Save as PDF (preferred for publications)
plt.savefig(os.path.join(save_dir, "fixed_cell_cycle_volumes.pdf"), 
            format='pdf',
            bbox_inches='tight', 
            pad_inches=0.1)

# Optionally, also save as SVG
plt.savefig(os.path.join(save_dir, "fixed_cell_cycle_volumes.svg"), 
            format='svg',
            bbox_inches='tight', 
            pad_inches=0.1)

# Keep PNG for quick previews
plt.savefig(os.path.join(save_dir, "fixed_cell_cycle_volumes.png"), 
            dpi=300, 
            bbox_inches='tight', 
            pad_inches=0.1,
            format='png')