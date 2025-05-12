import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler, StandardScaler
import os
pd.set_option('display.float_format', lambda x: '%.5f' % x)


pc_file = "PhysiCell/results/single_diffusion_cell_sink/summary.csv"
pc_df= pd.read_csv(pc_file,index_col=0)
pc_df = pc_df.loc[pc_df.index == 13]

bdm_file = "Biodynamo/unit_test_diffusion_small/data.csv"
bdm_df= pd.read_csv(bdm_file,index_col=None,header=None,sep = " ",names = ['timestep','avg_diff','cen_diff'])


tisim_file = "Tisim/unit_test_diffusion/results/diffusion_1_cell.csv"
tisim_df= pd.read_csv(tisim_file,names = ['timestep','diff'],header=0)
tisim_df = pd.concat([pd.DataFrame({"timestep": [0],"diff":[0]}), tisim_df], ignore_index=True)


chaste_file = "Chaste/unit_test_diffusion/results/TestDiffusionSmall03.dat"
ch_df= pd.read_csv(chaste_file,sep='\s+',names = ['timestep','diff'],header=0)
timesteps = np.concatenate((np.linspace(0, 1, num=11)[:-1], np.arange(1, 11, 1)))
timesteps_rounded = np.round(timesteps, 2)
ch_df['timestep_rounded'] = ch_df['timestep'].round(2)
selected_rows = ch_df[ch_df['timestep_rounded'].isin(timesteps_rounded)]



# Nature/Cell Systems colorblind-friendly palette and correct linestyles
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

# Update font settings with fallback options
plt.rcParams.update({
    'font.family': 'sans-serif',
    'font.sans-serif': ['DejaVu Sans', 'Helvetica', 'Arial', 'sans-serif'],  # DejaVu Sans is usually available by default
    'font.size': 8,
    'axes.labelsize': 8,
    'axes.titlesize': 8,
    'xtick.labelsize': 8,
    'ytick.labelsize': 8,
    'legend.fontsize': 8,
    'lines.linewidth': 1,
    'axes.linewidth': 0.5,
    'xtick.major.width': 0.5,
    'ytick.major.width': 0.5,
    'xtick.major.size': 3,
    'ytick.major.size': 3,
    'figure.dpi': 400
})

fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(10.5, 2.2), dpi=400)  

# Panel a: Full time course
ax1.plot(bdm_df['timestep'], bdm_df['cen_diff'],
         label='BioDynaMo', color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], linewidth=1.5)
ax1.plot(ch_df['timestep'], ch_df['diff'],
         label='Chaste', color=colors['Chaste'], linestyle=linestyles['Chaste'], linewidth=1.5)
ax1.plot(pc_df['timestep'], pc_df['diff']/602.2, 
         label='PhysiCell', color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], linewidth=1.5)
ax1.plot(tisim_df[tisim_df['timestep'] <= 10]['timestep'],
         tisim_df[tisim_df['timestep'] <= 10]['diff'],
         label='TiSim', color=colors['TiSim'], linestyle=linestyles['TiSim'], linewidth=1.5)
ax1.set_ylabel("Concentration (μM)")
ax1.set_xlabel("Time (min)")
ax1.grid(True, alpha=0.3, linewidth=0.5)
# Remove top and right spines for panel a
ax1.spines['top'].set_visible(False)
ax1.spines['right'].set_visible(False)

# Panel b: Early time points
for label, df, y, mask in [
    ('BioDynaMo', bdm_df, bdm_df['cen_diff'], slice(None)),
    ('Chaste', ch_df, ch_df['diff'], slice(None)),
    ('PhysiCell', pc_df, pc_df['diff']/602.2, slice(None)),
    ('TiSim', tisim_df, tisim_df['diff'], tisim_df['timestep'] <= 10)
]:
    x = df['timestep'][mask]
    y = y[mask]
    ax2.plot(x, y, color=colors[label], linestyle=linestyles[label], linewidth=1.5)
    ax2.plot(x[::5], y.iloc[::5], 'o', color=colors[label], markersize=4, alpha=0.8)

ax2.set_xlim(0, 0.5)
ax2.set_ylim(bottom=0)
ax2.set_xlabel("Time (min)")
ax2.grid(True, alpha=0.3, linewidth=0.5)
# Remove top and right spines for panel b
ax2.spines['top'].set_visible(False)
ax2.spines['right'].set_visible(False)

# Panel c: Last 0.5 minutes
for label, df, y in [
    ('BioDynaMo', bdm_df, bdm_df['cen_diff']),
    ('Chaste', ch_df, ch_df['diff']),
    ('PhysiCell', pc_df, pc_df['diff']/602.2),
    ('TiSim', tisim_df, tisim_df['diff'])
]:
    x = df['timestep']
    y = y
    mask = (x >= 9.5) & (x <= 10)
    x_last = x[mask]
    y_last = y[mask]
    ax3.plot(x_last, y_last, color=colors[label], linestyle=linestyles[label], linewidth=1.5)
    ax3.plot(x_last, y_last, 'o', color=colors[label], markersize=2, alpha=0.8)

ax3.set_xlabel("Time (min)")
ax3.set_xlim(9.5, 10)
ax3.grid(True, alpha=0.3, linewidth=0.5)
# Remove top and right spines for panel c
ax3.spines['top'].set_visible(False)
ax3.spines['right'].set_visible(False)

# Add subplot labels
ax1.text(-0.18, 1.1, 'a', transform=ax1.transAxes, fontsize=12, fontweight='bold')
ax2.text(-0.18, 1.1, 'b', transform=ax2.transAxes, fontsize=12, fontweight='bold')
ax3.text(-0.18, 1.1, 'c', transform=ax3.transAxes, fontsize=12, fontweight='bold')

# Shared legend
handles, labels = ax1.get_legend_handles_labels()
fig.legend(
    handles, labels,
    loc='upper center',
    bbox_to_anchor=(0.5, -0.05),
    ncol=4,
    frameon=True,
    framealpha=1.0
)

# Adjust layout
plt.tight_layout()
plt.subplots_adjust(bottom=0.15)

# Save figure in vector format (PDF or SVG)
save_dir = "./ResultAnalysis/plots/diffusion_single_ut_plots"
os.makedirs(save_dir, exist_ok=True)

# Save as PDF (preferred for publications)
plt.savefig(os.path.join(save_dir, "diffusion_single_ut.pdf"), 
            format='pdf',
            bbox_inches='tight', 
            pad_inches=0.1)

# Optionally, also save as SVG
plt.savefig(os.path.join(save_dir, "diffusion_single_ut.svg"), 
            format='svg',
            bbox_inches='tight', 
            pad_inches=0.1)










