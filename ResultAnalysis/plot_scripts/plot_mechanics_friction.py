import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Load data
pc_data = pd.read_csv('PhysiCell/results/mechanics_movement/cell_position_time.csv')

output_folder = 'Biodynamo/unit_test_mechanics_friction_single/results/'
bd_data = pd.read_csv(output_folder + 'positions.csv', index_col=0, header=None, sep='\t|,', engine='python').rename(columns={1: "x", 2: "y", 3: "z"})
bd_data['dx'] = abs(bd_data['x'] - bd_data['x'].shift(1))
bd_data.fillna({"dx": 0}, inplace=True)
bd_data['timestep'] = np.arange(0, 10, 0.1)
bd_data['dt'] = 0.1
bd_data['velocity'] = bd_data['dx'] / bd_data['dt']

output_folder = 'Chaste/unit_test_mechanics_friction/results/'
ch_data = pd.read_csv(output_folder + 'node_locations.dat', header=None, names=["timestep", "x", "y"], sep='\t| ', index_col=None, engine='python')
ch_data['dx'] = abs(ch_data["x"] - ch_data["x"].shift(1))
ch_data.fillna({"dx": 0}, inplace=True)
ch_data['timestep'] = np.arange(0, 10.01, 0.1)
ch_data['dt'] = 0.1
ch_data['velocity'] = ch_data['dx'] / ch_data['dt']

output_folder = "Tisim/unit_test_mechanics_friction/"
ts_data = pd.read_csv(output_folder + 'mechanical friction.csv', header=0, sep='\t|,', engine='python', names=["dt", "velocity"])

# Set up colorblind-friendly colors and linestyles
colors = {
    'PhysiCell': '#4daf4a',   # Green
    'BioDynaMo': '#e41a1c',   # Red
    'Chaste': '#377eb8',      # Blue
    'TiSim': '#984ea3'        # Purple
}
linestyles = {
    'PhysiCell': '-.',
    'BioDynaMo': '-',
    'Chaste': '--',
    'TiSim': ':'
}

# Update font and axes settings
plt.rcParams.update({
    'font.family': 'sans-serif',
    'font.sans-serif': ['DejaVu Sans', 'Helvetica', 'Arial', 'sans-serif'],
    'font.size': 8,
    'axes.labelsize': 10,
    'axes.titlesize': 10,
    'xtick.labelsize': 8,
    'ytick.labelsize': 8,
    'legend.fontsize': 9,
    'lines.linewidth': 1.5,
    'axes.linewidth': 0.5,
    'xtick.major.width': 0.5,
    'ytick.major.width': 0.5,
    'xtick.major.size': 3,
    'ytick.major.size': 3,
    'figure.dpi': 400
})

fig, ax = plt.subplots(figsize=(8.9, 4))

# Plot each simulator (restrict to 0–0.25 min)
mask_pc = (pc_data['dt'] >= 0) & (pc_data['dt'] <= 0.25)
mask_bd = (bd_data['timestep'] >= 0) & (bd_data['timestep'] <= 0.25)
mask_ch = (ch_data['timestep'] >= 0) & (ch_data['timestep'] <= 0.25)
mask_ts = (ts_data['dt'] >= 0) & (ts_data['dt'] <= 0.25)

ax.plot(pc_data['dt'][mask_pc], pc_data['mvx'][mask_pc], label="PhysiCell", color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], alpha=0.9)
ax.plot(bd_data['timestep'][mask_bd], bd_data['velocity'][mask_bd], label="BioDynaMo", color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], alpha=0.9)
ax.plot(ch_data['timestep'][mask_ch], ch_data['velocity'][mask_ch], label="Chaste", color=colors['Chaste'], linestyle=linestyles['Chaste'], alpha=0.9)
ax.plot(ts_data['dt'][mask_ts], ts_data['velocity'][mask_ts], label="TiSim", color=colors['TiSim'], linestyle=linestyles['TiSim'], alpha=0.9)

# Axis labels and limits
ax.set_ylabel("Velocity (μm/s)", labelpad=2, fontsize=10)
ax.set_xlabel("Time (minutes)", labelpad=2, fontsize=10)
ax.set_xlim(0, 0.25)
ax.set_ylim(bottom=0)

# Remove top and right spines
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

# Subtle grid
ax.grid(True, alpha=0.3, linewidth=0.5)

# Legend below the plot
ax.legend(bbox_to_anchor=(0.5, -0.18), loc='upper center', ncol=4, frameon=False)

plt.tight_layout()
plt.subplots_adjust(bottom=0.23)

# Save in vector and raster formats
save_dir = "./ResultAnalysis/plots/mechanics_friction_plots"
os.makedirs(save_dir, exist_ok=True)
plt.savefig(os.path.join(save_dir, "mechanics_friction_zoomed.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
plt.savefig(os.path.join(save_dir, "mechanics_friction_zoomed.svg"), format='svg', bbox_inches='tight', pad_inches=0.1)
plt.savefig(os.path.join(save_dir, "mechanics_friction_zoomed.png"), dpi=300, bbox_inches='tight', pad_inches=0.1, format='png')

