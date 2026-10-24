import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
import yaml

# Load data
output_folder = "PhysiCell/results/mechanics_pushing/mechanics_pushing_01_004/"
df = pd.read_csv(output_folder + "cells_position_time.csv")
x0 = df[df['id'] == 0]['x'].reset_index(drop=True)
x1 = df[df['id'] == 1]['x'].reset_index(drop=True)
pc_dist_dt = pd.DataFrame()
pc_dist_dt["dx"] = abs(x0 - x1)
dt = df[df['id'] == 0]['dt'].reset_index(drop=True)
pc_dist_dt["dt"] = dt

output_folder = "PhysiCell/results/mechanics_pushing/mechanics_pushing_001_004/"
df = pd.read_csv(output_folder + "cells_position_time.csv")
x0 = df[df['id'] == 0]['x'].reset_index(drop=True)
x1 = df[df['id'] == 1]['x'].reset_index(drop=True)
pc_dist_dt2 = pd.DataFrame()
pc_dist_dt2["dx"] = abs(x0 - x1)
dt = df[df['id'] == 0]['dt'].reset_index(drop=True)
pc_dist_dt2["dt"] = dt

file = "Biodynamo/mechanics_pushing/results_timestep0.1/positions.csv"
bd_dist = pd.read_csv(file, index_col=0, header=None, sep='\t|,', engine='python').rename(columns={1: "x1", 4: "x2"})
new_row = pd.DataFrame([[-15, 0, 0, 15, 0, 0]], columns=bd_dist.columns)
bd_dist = pd.concat([new_row, bd_dist], ignore_index=True)
bd_dist['dx'] = abs(bd_dist["x1"] - bd_dist["x2"])
bd_dist['dt'] = bd_dist.index *0.1
file = "Biodynamo/mechanics_pushing/results_timestep0.01/positions.csv"
bd_dist2 = pd.read_csv(file, index_col=0, header=None, sep='\t|,', engine='python').rename(columns={1: "x1", 4: "x2"})
new_row = pd.DataFrame([[-15, 0, 0, 15, 0, 0]], columns=bd_dist2.columns)
bd_dist2 = pd.concat([new_row, bd_dist2], ignore_index=True)
bd_dist2['dx'] = abs(bd_dist2["x1"] - bd_dist2["x2"])
bd_dist2['dt'] = bd_dist2.index * 0.01

file = "Tisim/mechanics_pushing/mechanics_pushing.csv"
ts_dist = pd.read_csv(file, index_col=None, header=0, names=['time', 'dx'])

file = "Chaste/mechanics_pushing/results/results.viznodelocations"
ch_dist = pd.read_csv(file, header=None, sep='\t| ', index_col=0, engine='python')
ch_dist['dx'] = abs(ch_dist[4] - ch_dist[1]) * 10
# ch_dist['dt'] = [x for x in np.arange(0,10.01,0.1)]
# ch_dist.index = ch_dist.index*1000
ch_dist['dt'] = ch_dist.index * 60
# ch_dist.index = ch_dist.index * 100

# computix
with open("CompuTiX/mechanics_pushing/benchmark_exmaple_2.yaml", "r") as f:
    data = yaml.safe_load(f)

ct_t = np.array( data["t"]["values"] ) #[s]
ct_x = np.array( data['Cells']['values']['x']['values'] ) #[m]

#Compute absolute distance between spheres' centers
ct_d = np.abs(ct_x[:, 0] - ct_x[:, 1])


# Set up colorblind-friendly colors and linestyles
colors = {
    'PhysiCell': '#98FB98',   # Light Green
    'PhysiCell2': '#4daf4a',   # Green
    'BioDynaMo': '#ff7f00', 
    'BioDynaMo2': "#f85d25",    # Orange (changed from red)
    'Chaste': '#377eb8',      # Blue
    'TiSim': '#984ea3',       # Purple
    'Computix': "#fd2a2aff",       # Pink
    'radius': '#000000'       # Black
}
linestyles = {
    'PhysiCell': '-',
    'PhysiCell2': '-',
    'BioDynaMo': '-',
    'BioDynaMo2': '-',
    'Chaste': '-',
    'TiSim': '-',
    'Computix': '-',
    'radius': 'dotted'
}
labels = {
    'PhysiCell': 'PhysiCell',
    'PhysiCell2': 'PhysiCell x10res',
    'BioDynaMo': 'BioDynaMo',
    'BioDynaMo2': 'BioDynaMo x10res',
    'Chaste': 'Chaste x10res',
    'TiSim': 'TiSim',
    'Computix': 'Computix'
}

# Update font settings for more compact plots
plt.rcParams.update({
    'font.family': 'sans-serif',
    'font.sans-serif': ['DejaVu Sans', 'Helvetica', 'Arial', 'sans-serif'],
    'font.size': 8,  # Increased from 7
    'axes.labelsize': 9,  # Increased from 8
    'axes.titlesize': 9,  # Increased from 8
    'xtick.labelsize': 8,  # Increased from 7
    'ytick.labelsize': 8,  # Increased from 7
    'legend.fontsize': 8,  # Increased from 7
    'lines.linewidth': 1.8,  # Increased from 1.2
    'axes.linewidth': 0.8,  # Increased from 0.5
    'xtick.major.width': 0.8,  # Increased from 0.5
    'ytick.major.width': 0.8,  # Increased from 0.5
    'xtick.major.size': 3,  # Increased from 2
    'ytick.major.size': 3,  # Increased from 2
    'figure.dpi': 400
})

# --- DUAL PANEL PLOT (Full and first 3 min) ---
# fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(8, 2.8))  # Wider and more compact

# --- FULL PLOT (ax1) ---
# ax1.plot(pc_dist_dt['dt'], pc_dist_dt['dx'], color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], alpha=0.7)
# ax1.plot(bd_dist['dt'], bd_dist['dx'], color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], alpha=0.7)
# ax1.plot(ch_dist['dt'], ch_dist['dx'], color=colors['Chaste'], linestyle=linestyles['Chaste'], alpha=0.7)
# ax1.plot(ts_dist["time"], ts_dist['dx'], color=colors['TiSim'], linestyle=linestyles['TiSim'], alpha=0.7)
# ax1.plot(range(0, 11), [10] * len(range(0, 11)), color=colors['radius'], linestyle=linestyles['radius'], alpha=0.3)
# ax1.set_ylabel("Distance between cell centers (μm)", labelpad=8, fontsize=12)
# ax1.set_xlabel("Time (minutes)", labelpad=8, fontsize=12)
# ax1.set_xlim(left=0)
# ax1.set_ylim(bottom=0)
# ax1.spines['top'].set_visible(False)
# ax1.spines['right'].set_visible(False)
# ax1.grid(False)
# ax1.set_title("Full time course", fontsize=11)
# ax1.tick_params(axis='both', which='major', labelsize=11)

# --- ZOOMED PLOT (ax2) ---
# ax2.plot(pc_dist_dt['dt'][pc_dist_dt['dt'] <= 3], pc_dist_dt['dx'][pc_dist_dt['dt'] <= 3], color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], alpha=0.7)
# ax2.plot(bd_dist['dt'][bd_dist['dt'] <= 3], bd_dist['dx'][bd_dist['dt'] <= 3], color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], alpha=0.7)
# ax2.plot(ch_dist['dt'][np.array(ch_dist['dt']) <= 3], ch_dist['dx'][np.array(ch_dist['dt']) <= 3], color=colors['Chaste'], linestyle=linestyles['Chaste'], alpha=0.7)
# ax2.plot(ts_dist["time"][ts_dist["time"] <= 3], ts_dist['dx'][ts_dist["time"] <= 3], color=colors['TiSim'], linestyle=linestyles['TiSim'], alpha=0.7)
# ax2.plot(range(0, 4), [10] * len(range(0, 4)), color=colors['radius'], linestyle=linestyles['radius'], alpha=0.3)
# ax2.set_xlabel("Time (minutes)", labelpad=8, fontsize=12)
# ax2.set_xlim(0, 3)
# ax2.set_ylim(bottom=0)
# ax2.spines['top'].set_visible(False)
# ax2.spines['right'].set_visible(False)
# ax2.grid(False)
# ax2.set_title("First 3 minutes", fontsize=11)
# ax2.tick_params(axis='both', which='major', labelsize=11)

# plt.tight_layout()
# plt.subplots_adjust(bottom=0.15)

# # Save in vector and raster formats
# save_dir = "./ResultAnalysis/plots/mechanics_pushing_plots"
# os.makedirs(save_dir, exist_ok=True)
# plt.savefig(os.path.join(save_dir, "mechanics_movement_dualpanel.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
# plt.savefig(os.path.join(save_dir, "mechanics_movement_dualpanel.svg"), format='svg', bbox_inches='tight', pad_inches=0.1)
# plt.savefig(os.path.join(save_dir, "mechanics_movement_dualpanel.png"), dpi=600, bbox_inches='tight', pad_inches=0.1, format='png')
# plt.close(fig)

# --- INDIVIDUAL FULL PLOT ---
# fig_full, ax_full = plt.subplots(figsize=(3, 2.8))
# ax_full.plot(pc_dist_dt['dt'], pc_dist_dt['dx'], color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], alpha=0.7)
# ax_full.plot(bd_dist['dt'], bd_dist['dx'], color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], alpha=0.7)
# ax_full.plot(ch_dist['dt'], ch_dist['dx'], color=colors['Chaste'], linestyle=linestyles['Chaste'], alpha=0.7)
# ax_full.plot(ts_dist["time"], ts_dist['dx'], color=colors['TiSim'], linestyle=linestyles['TiSim'], alpha=0.7)
# ax_full.plot(range(0, 11), [10] * len(range(0, 11)), color=colors['radius'], linestyle=linestyles['radius'], alpha=0.3)
# ax_full.set_ylabel("Distance between cell centers (μm)", labelpad=8, fontsize=12)
# ax_full.set_xlabel("Time (minutes)", labelpad=8, fontsize=12)
# ax_full.set_xlim(left=0)
# ax_full.set_ylim(bottom=0)
# ax_full.spines['top'].set_visible(False)
# ax_full.spines['right'].set_visible(False)
# ax_full.grid(False)
# ax_full.tick_params(axis='both', which='major', labelsize=11)
# plt.tight_layout()
# plt.savefig(os.path.join(save_dir, "mechanics_movement_full.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
# plt.savefig(os.path.join(save_dir, "mechanics_movement_full.svg"), format='svg', bbox_inches='tight', pad_inches=0.1)
# plt.savefig(os.path.join(save_dir, "mechanics_movement_full.png"), dpi=600, bbox_inches='tight', pad_inches=0.1, format='png')
# plt.close(fig_full)

# --- INDIVIDUAL ZOOMED PLOT (First 3 min) ---
# fig_zoom, ax_zoom = plt.subplots(figsize=(3, 2.8))
# ax_zoom.plot(pc_dist_dt['dt'][pc_dist_dt['dt'] <= 3], pc_dist_dt['dx'][pc_dist_dt['dt'] <= 3], color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], alpha=0.7)
# ax_zoom.plot(bd_dist['dt'][bd_dist['dt'] <= 3], bd_dist['dx'][bd_dist['dt'] <= 3], color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], alpha=0.7)
# ax_zoom.plot(ch_dist['dt'][np.array(ch_dist['dt']) <= 3], ch_dist['dx'][np.array(ch_dist['dt']) <= 3], color=colors['Chaste'], linestyle=linestyles['Chaste'], alpha=0.7)
# ax_zoom.plot(ts_dist["time"][ts_dist["time"] <= 3], ts_dist['dx'][ts_dist["time"] <= 3], color=colors['TiSim'], linestyle=linestyles['TiSim'], alpha=0.7)
# ax_zoom.plot(range(0, 4), [10] * len(range(0, 4)), color=colors['radius'], linestyle=linestyles['radius'], alpha=0.3)
# ax_zoom.set_xlabel("Time (minutes)", labelpad=8, fontsize=12)
# ax_zoom.set_xlim(0, 3)
# ax_zoom.set_ylim(bottom=0)
# ax_zoom.spines['top'].set_visible(False)
# ax_zoom.spines['right'].set_visible(False)
# ax_zoom.grid(False)
# ax_zoom.tick_params(axis='both', which='major', labelsize=11)
# plt.tight_layout()
# plt.savefig(os.path.join(save_dir, "mechanics_movement_zoom3min.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
# plt.savefig(os.path.join(save_dir, "mechanics_movement_zoom3min.svg"), format='svg', bbox_inches='tight', pad_inches=0.1)
# plt.savefig(os.path.join(save_dir, "mechanics_movement_zoom3min.png"), dpi=600, bbox_inches='tight', pad_inches=0.1, format='png')
# plt.close(fig_zoom)

# --- INDIVIDUAL NORMALIZED FULL PLOT ---
# cell_radius = 10.0
# fig2, ax_norm = plt.subplots(figsize=(3, 2.8))
# ax_norm.plot(pc_dist_dt['dt'], pc_dist_dt['dx'] / cell_radius, color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], alpha=0.7)
# ax_norm.plot(bd_dist['dt'], bd_dist['dx'] / cell_radius, color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], alpha=0.7)
# ax_norm.plot(ch_dist['dt'], ch_dist['dx'] / cell_radius, color=colors['Chaste'], linestyle=linestyles['Chaste'], alpha=0.7)
# ax_norm.plot(ts_dist["time"], ts_dist['dx'] / cell_radius, color=colors['TiSim'], linestyle=linestyles['TiSim'], alpha=0.7)
# ax_norm.axhline(1, color=colors['radius'], linestyle=linestyles['radius'], alpha=0.3)
# ax_norm.set_ylabel("Distance / cell radius (μm)", labelpad=8, fontsize=12)
# ax_norm.set_xlabel("Time (minutes)", labelpad=8, fontsize=12)
# ax_norm.set_xlim(left=0)
# ax_norm.set_ylim(bottom=0)
# ax_norm.spines['top'].set_visible(False)
# ax_norm.spines['right'].set_visible(False)
# ax_norm.grid(False)
# ax_norm.tick_params(axis='both', which='major', labelsize=11)
# plt.tight_layout()
# plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
# plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized.svg"), format='svg', bbox_inches='tight', pad_inches=0.1)
# plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized.png"), dpi=600, bbox_inches='tight', pad_inches=0.1, format='png')
# plt.close(fig2)

# --- INDIVIDUAL NORMALIZED ZOOMED PLOT (First 3 min) ---
# save_dir = "./ResultAnalysis/plots/mechanics_pushing_plots"
# os.makedirs(save_dir, exist_ok=True)
# cell_radius = 10.0

# fig3, ax_norm_zoom = plt.subplots(figsize=(3, 2.8))
# ax_norm_zoom.plot(bd_dist['dt'][bd_dist['dt'] <= 3], (bd_dist['dx'] / cell_radius)[bd_dist['dt'] <= 3], 
#                   color=colors['BioDynaMo'],
#                   linestyle=linestyles['BioDynaMo'], 
#                   label=labels['BioDynaMo'], 
#                   alpha=0.7)
# ax_norm_zoom.plot(ch_dist['dt'][np.array(ch_dist['dt']) <= 3], (ch_dist['dx'] / cell_radius)[np.array(ch_dist['dt']) <= 3], 
#                   color=colors['Chaste'], 
#                   linestyle=linestyles['Chaste'], 
#                   label=labels['Chaste'], 
#                   alpha=0.7)
# ax_norm_zoom.plot(pc_dist_dt['dt'][pc_dist_dt['dt'] <= 3], (pc_dist_dt['dx'] / cell_radius)[pc_dist_dt['dt'] <= 3], 
#                   color=colors['PhysiCell'], 
#                   linestyle=linestyles['PhysiCell'], 
#                   label=labels['PhysiCell'],
#                   alpha=0.7)
# ax_norm_zoom.plot(pc_dist_dt2['dt'][pc_dist_dt2['dt'] <= 3], (pc_dist_dt2['dx'] / cell_radius)[pc_dist_dt2['dt'] <= 3], 
#                   color=colors['PhysiCell2'], 
#                   linestyle=linestyles['PhysiCell2'], 
#                   label=labels['PhysiCell2'],
#                   alpha=0.7)
# ax_norm_zoom.plot(ts_dist["time"][ts_dist["time"] <= 3], (ts_dist['dx'] / cell_radius)[ts_dist["time"] <= 3], 
#                   color=colors['TiSim'], 
#                   linestyle=linestyles['TiSim'], 
#                   label=labels['TiSim'], 
#                   alpha=0.7)
# ax_norm_zoom.axhline(1, color=colors['radius'], linestyle=linestyles['radius'], alpha=0.3)
# ax_norm_zoom.set_ylabel("Distance / cell diam (μm)", labelpad=8, fontsize=12)
# ax_norm_zoom.set_xlabel("Time (min)", labelpad=8, fontsize=12)
# ax_norm_zoom.set_xlim(0, 3)
# ax_norm_zoom.set_ylim(bottom=0)
# ax_norm_zoom.spines['top'].set_visible(False)
# ax_norm_zoom.spines['right'].set_visible(False)
# ax_norm_zoom.grid(False)
# ax_norm_zoom.tick_params(axis='both', which='major', labelsize=11)
# ax_norm_zoom.legend(loc='upper right', bbox_to_anchor=(1, 1), fontsize=8)

# plt.tight_layout()
# plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized_zoom3min.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
# plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized_zoom3min.svg"), format='svg', bbox_inches='tight', pad_inches=0.1)
# plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized_zoom3min.png"), dpi=600, bbox_inches='tight', pad_inches=0.1, format='png')
# plt.close(fig3)

# --- INDIVIDUAL NORMALIZED ZOOMED PLOT (First 5 min) ---
save_dir = "./ResultAnalysis/plots/mechanics_pushing_plots"
os.makedirs(save_dir, exist_ok=True)
cell_radius = 10.0

fig4, ax_norm_zoom = plt.subplots(figsize=(3, 2.8))
ax_norm_zoom.plot(bd_dist['dt'][bd_dist['dt'] <= 5], (bd_dist['dx'] / cell_radius)[bd_dist['dt'] <= 5], 
                  color=colors['BioDynaMo'],
                  linestyle=linestyles['BioDynaMo'], 
                  label=labels['BioDynaMo'], 
                  alpha=0.7)
# ax_norm_zoom.plot(bd_dist2['dt'][bd_dist2['dt'] <= 5], (bd_dist2['dx'] / cell_radius)[bd_dist2['dt'] <= 5], 
#                   color=colors['BioDynaMo2'],
#                   linestyle=linestyles['BioDynaMo2'], 
#                   label=labels['BioDynaMo2'], 
#                   alpha=0.7)
ax_norm_zoom.plot(ch_dist['dt'][np.array(ch_dist['dt']) <= 5], (ch_dist['dx'] / cell_radius)[np.array(ch_dist['dt']) <= 5], 
                  color=colors['Chaste'], 
                  linestyle=linestyles['Chaste'], 
                  label=labels['Chaste'], 
                  alpha=0.7)
ax_norm_zoom.plot(pc_dist_dt['dt'][pc_dist_dt['dt'] <= 5], (pc_dist_dt['dx'] / cell_radius)[pc_dist_dt['dt'] <= 5], 
                  color=colors['PhysiCell'], 
                  linestyle=linestyles['PhysiCell'], 
                  label=labels['PhysiCell'],
                  alpha=0.7)
ax_norm_zoom.plot(pc_dist_dt2['dt'][pc_dist_dt2['dt'] <= 5], (pc_dist_dt2['dx'] / cell_radius)[pc_dist_dt2['dt'] <= 5], 
                  color=colors['PhysiCell2'], 
                  linestyle=linestyles['PhysiCell2'], 
                  label=labels['PhysiCell2'],
                  alpha=0.7)
ax_norm_zoom.plot(ts_dist["time"][ts_dist["time"] <= 5], (ts_dist['dx'] / cell_radius)[ts_dist["time"] <= 5], 
                  color=colors['TiSim'], 
                  linestyle=linestyles['TiSim'], 
                  label=labels['TiSim'], 
                  alpha=0.7)
ax_norm_zoom.plot(ct_t[ct_t <= 300] / 60., (ct_d[ct_t <= 300] / 1e-6) / cell_radius,
                  linestyle=linestyles['Computix'],
                  label=labels['Computix'],
                  color=colors['Computix'],
                  alpha=0.6)
ax_norm_zoom.axhline(1, color=colors['radius'], linestyle=linestyles['radius'], alpha=0.3)
ax_norm_zoom.set_ylabel("Distance / cell diam (μm)", labelpad=8, fontsize=12)
ax_norm_zoom.set_xlabel("Time (min)", labelpad=8, fontsize=12)
ax_norm_zoom.set_xlim(0, 5)
ax_norm_zoom.set_ylim(bottom=0)
ax_norm_zoom.spines['top'].set_visible(False)
ax_norm_zoom.spines['right'].set_visible(False)
ax_norm_zoom.grid(False)
ax_norm_zoom.tick_params(axis='both', which='major', labelsize=11)
ax_norm_zoom.legend(loc='upper right', bbox_to_anchor=(1, 1), fontsize=8)

plt.tight_layout()
# plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized_zoom3min.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
# plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized_zoom3min.svg"), format='svg', bbox_inches='tight', pad_inches=0.1)
plt.savefig(os.path.join(save_dir, "mechanics_movement_normalized_zoom5min.png"), dpi=600, bbox_inches='tight', pad_inches=0.1, format='png')
plt.close(fig4)
