import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Load data
output_folder = "PhysiCell/results/mechanics_pushing/"
df = pd.read_csv(output_folder + "cells_position_time.csv")
x0 = df[df['id'] == 0]['x'].reset_index(drop=True)
x1 = df[df['id'] == 1]['x'].reset_index(drop=True)
pc_dist_dt = pd.DataFrame()
pc_dist_dt["dx"] = abs(x0 - x1)
dt = df[df['id'] == 0]['dt'].reset_index(drop=True)
pc_dist_dt["dt"] = dt

file = "Biodynamo/unit_test_mechanics_pushing/results/positions.csv"
bd_dist = pd.read_csv(file, index_col=0, header=None, sep='\t|,', engine='python').rename(columns={1: "x1", 4: "x2"})
new_row = pd.DataFrame([[-15, 0, 0, 15, 0, 0]], columns=bd_dist.columns)
bd_dist = pd.concat([new_row, bd_dist], ignore_index=True)
bd_dist['dx'] = abs(bd_dist["x1"] - bd_dist["x2"])
bd_dist['dt'] = bd_dist.index * 0.1

file = "Tisim/unit_test_mechanics_pushing/mechanical pushing.csv"
ts_dist = pd.read_csv(file, index_col=None, header=0, names=['time', 'dx'])

file = "Chaste/unit_test_mechanics_pushing/results/results.viznodelocations"
ch_dist = pd.read_csv(file, header=None, sep='\t| ', index_col=0, engine='python')
ch_dist['dx'] = abs(ch_dist[2] - ch_dist[1]) * 10
ch_dist['dt'] = [x for x in np.arange(0, 10.01, 0.1)]
ch_dist.index = ch_dist.index * 1000

# Set up colorblind-friendly colors and linestyles
colors = {
    'PhysiCell': '#4daf4a',   # Green
    'BioDynaMo': '#e41a1c',   # Red
    'Chaste': '#377eb8',      # Blue
    'TiSim': '#984ea3',       # Purple
    'radius': '#000000'       # Black
}
linestyles = {
    'PhysiCell': '-.',
    'BioDynaMo': '-',
    'Chaste': '--',
    'TiSim': ':',
    'radius': '-'
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

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 4), sharey=True)

# --- FULL PLOT (ax1) ---
ax1.plot(pc_dist_dt['dt'], pc_dist_dt['dx'], label="PhysiCell", color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], alpha=0.9)
ax1.plot(bd_dist['dt'], bd_dist['dx'], label="BioDynaMo", color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], alpha=0.9)
ax1.plot(ch_dist['dt'], ch_dist['dx'], label="Chaste", color=colors['Chaste'], linestyle=linestyles['Chaste'], alpha=0.9)
ax1.plot(ts_dist["time"], ts_dist['dx'], label="TiSim", color=colors['TiSim'], linestyle=linestyles['TiSim'], alpha=0.9)
ax1.plot(range(0, 11), [10] * len(range(0, 11)), label='radius', color=colors['radius'], linestyle=linestyles['radius'], alpha=0.3)
ax1.set_ylabel("Distance between cell centers (μm)", labelpad=2, fontsize=10)
ax1.set_xlabel("Time (minutes)", labelpad=2, fontsize=10)
ax1.set_xlim(left=0)
ax1.set_ylim(bottom=0)
ax1.spines['top'].set_visible(False)
ax1.spines['right'].set_visible(False)
ax1.grid(True, alpha=0.3, linewidth=0.5)
ax1.set_title("Full time course", fontsize=10)

# Only plot data up to 3 minutes (ax2)
ax2.plot(pc_dist_dt['dt'][pc_dist_dt['dt'] <= 3], pc_dist_dt['dx'][pc_dist_dt['dt'] <= 3], color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], alpha=0.9)
ax2.plot(bd_dist['dt'][bd_dist['dt'] <= 3], bd_dist['dx'][bd_dist['dt'] <= 3], color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], alpha=0.9)
ax2.plot(ch_dist['dt'][np.array(ch_dist['dt']) <= 3], ch_dist['dx'][np.array(ch_dist['dt']) <= 3], color=colors['Chaste'], linestyle=linestyles['Chaste'], alpha=0.9)
ax2.plot(ts_dist["time"][ts_dist["time"] <= 3], ts_dist['dx'][ts_dist["time"] <= 3], color=colors['TiSim'], linestyle=linestyles['TiSim'], alpha=0.9)
ax2.plot(range(0, 4), [10] * len(range(0, 4)), color=colors['radius'], linestyle=linestyles['radius'], alpha=0.3)
ax2.set_xlabel("Time (minutes)", labelpad=2, fontsize=10)
ax2.set_xlim(0, 3)
ax2.set_ylim(bottom=0)
ax2.spines['top'].set_visible(False)
ax2.spines['right'].set_visible(False)
ax2.grid(True, alpha=0.3, linewidth=0.5)
ax2.set_title("First 3 minutes", fontsize=10)
ax2.set_yticklabels([])  # Hide y-tick labels for the zoomed panel if you want

# Shared legend below both plots
fig.legend(bbox_to_anchor=(0.5, 0.08), loc='upper center', ncol=5, frameon=False, fontsize=9)
plt.tight_layout()
plt.subplots_adjust(bottom=0.23)

# Save in vector and raster formats
save_dir = "./ResultAnalysis/plots/mechanics_pushing_plots"
os.makedirs(save_dir, exist_ok=True)
plt.savefig(os.path.join(save_dir, "mechanics_movement_dualpanel.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
plt.savefig(os.path.join(save_dir, "mechanics_movement_dualpanel.svg"), format='svg', bbox_inches='tight', pad_inches=0.1)
plt.savefig(os.path.join(save_dir, "mechanics_movement_dualpanel.png"), dpi=300, bbox_inches='tight', pad_inches=0.1, format='png')


# Define the cell radius (from your reference line, it's 10 μm)
cell_radius = 10.0

fig2, ax_norm = plt.subplots(figsize=(8.9, 4))

# Plot normalized distances for each simulator
ax_norm.plot(pc_dist_dt['dt'], pc_dist_dt['dx'] / cell_radius, label="PhysiCell", color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], alpha=0.9)
ax_norm.plot(bd_dist['dt'], bd_dist['dx'] / cell_radius, label="BioDynaMo", color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], alpha=0.9)
ax_norm.plot(ch_dist['dt'], ch_dist['dx'] / cell_radius, label="Chaste", color=colors['Chaste'], linestyle=linestyles['Chaste'], alpha=0.9)
ax_norm.plot(ts_dist["time"], ts_dist['dx'] / cell_radius, label="TiSim", color=colors['TiSim'], linestyle=linestyles['TiSim'], alpha=0.9)
ax_norm.axhline(1, color=colors['radius'], linestyle=linestyles['radius'], alpha=0.3, label='radius')

# Axis labels and limits
ax_norm.set_ylabel("Distance / cell radius (μm)", labelpad=2, fontsize=10)
ax_norm.set_xlabel("Time (minutes)", labelpad=2, fontsize=10)
ax_norm.set_xlim(left=0)
ax_norm.set_ylim(bottom=0)

# Remove top and right spines
ax_norm.spines['top'].set_visible(False)
ax_norm.spines['right'].set_visible(False)

# Subtle grid
ax_norm.grid(True, alpha=0.3, linewidth=0.5)

# Legend below the plot
ax_norm.legend(bbox_to_anchor=(0.5, -0.18), loc='upper center', ncol=5, frameon=False, fontsize=9)

plt.tight_layout()
plt.subplots_adjust(bottom=0.23)

# Save in vector and raster formats
plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized.svg"), format='svg', bbox_inches='tight', pad_inches=0.1)
plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized.png"), dpi=300, bbox_inches='tight', pad_inches=0.1, format='png')


fig3, ax_norm_zoom = plt.subplots(figsize=(8.9, 4), dpi=300)

# Plot normalized distances for each simulator, only up to 3 minutes
ax_norm_zoom.plot(pc_dist_dt['dt'][pc_dist_dt['dt'] <= 3], (pc_dist_dt['dx'] / cell_radius)[pc_dist_dt['dt'] <= 3],
                  label="PhysiCell", color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], alpha=0.9)
ax_norm_zoom.plot(bd_dist['dt'][bd_dist['dt'] <= 3], (bd_dist['dx'] / cell_radius)[bd_dist['dt'] <= 3],
                  label="BioDynaMo", color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], alpha=0.9)
ax_norm_zoom.plot(ch_dist['dt'][np.array(ch_dist['dt']) <= 3], (ch_dist['dx'] / cell_radius)[np.array(ch_dist['dt']) <= 3],
                  label="Chaste", color=colors['Chaste'], linestyle=linestyles['Chaste'], alpha=0.9)
ax_norm_zoom.plot(ts_dist["time"][ts_dist["time"] <= 3], (ts_dist['dx'] / cell_radius)[ts_dist["time"] <= 3],
                  label="TiSim", color=colors['TiSim'], linestyle=linestyles['TiSim'], alpha=0.9)
ax_norm_zoom.axhline(1, color=colors['radius'], linestyle=linestyles['radius'], alpha=0.3, label='radius')

# Axis labels and limits
ax_norm_zoom.set_ylabel("Distance / cell radius (μm)", labelpad=2, fontsize=10)
ax_norm_zoom.set_xlabel("Time (minutes)", labelpad=2, fontsize=10)
ax_norm_zoom.set_xlim(0, 3)
ax_norm_zoom.set_ylim(bottom=0)

# Remove top and right spines
ax_norm_zoom.spines['top'].set_visible(False)
ax_norm_zoom.spines['right'].set_visible(False)

# Subtle grid
ax_norm_zoom.grid(True, alpha=0.3, linewidth=0.5)

# Legend below the plot
ax_norm_zoom.legend(bbox_to_anchor=(0.5, -0.18), loc='upper center', ncol=5, frameon=False, fontsize=9)

plt.tight_layout()
plt.subplots_adjust(bottom=0.23)

# Save in vector and raster formats
plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized_zoom3min.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized_zoom3min.svg"), format='svg', bbox_inches='tight', pad_inches=0.1)
plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized_zoom3min.png"), dpi=300, bbox_inches='tight', pad_inches=0.1, format='png')
