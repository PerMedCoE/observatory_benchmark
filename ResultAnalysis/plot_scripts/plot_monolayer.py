import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import re
from scipy.interpolate import interp1d
import os
expe_dt = [336,386,408,481,506,646]
expe_dt = [x/24. for x in expe_dt]
expe_diam = [ 1140 , 1400 , 1590 , 2040 , 2250 , 3040 ]

biodynamo_dt = [14, 14.8333333333333, 15.6666666666667, 16.5, 17.3333333333333, 18.1666666666666, 18.9999999999999, 19.8333333333332, 20.6666666666665, 21.4999999999998, 22.333333333333, 23.1666666666663, 23.9999999999996, 24.8333333333329, 25.6666666666665, 26.5]
biodynamo_diam =  [1240, 1320, 1440, 1560, 1680, 1800, 1920, 2040, 2160, 2280, 2400, 2520, 2640, 2760, 2880, 3000]

df_tsim_pre = pd.read_csv('Tisim/use_case_2Ddisk/old_results/result_2d_10_8_3.9_50.txt', sep='\t', engine='python')
df_tisim = pd.DataFrame({
    'dt': df_tsim_pre['Time [s]'].iloc[140:] / 86400,  # Convert to days
    'diam': 2 * df_tsim_pre["Radius of cell population [μm]"].iloc[140:],
    'Results': 'TiSim'
})

with open("Chaste/use_case_2Ddisk/results/multiple-cells/tissuewidth.dat") as results_file:
    times = []
    tissue_widths = []
    for line in results_file:
        line = line.replace('\n', '')
        values = re.split('\t|,', line)
        if len(values) == 1:
            continue
        
        times.append(float(values[0]))
        tissue_widths.append(float(values[3]))
df_chaste = pd.DataFrame(data = zip(times,tissue_widths),columns=['dt','diam'])
df_chaste["dt"]=(df_chaste["dt"]+336)/24
df_chaste['Results'] = 'Chaste'

# Fix PhysiCell data loading - start from 14 days
df_pc = pd.read_csv('PhysiCell/results/monolayer/monolayer_t_diam.csv', sep=',', engine='python')
df_pc = df_pc.rename(columns={df_pc.columns[0]: 'dt', df_pc.columns[1]: 'diam'})
# Filter data to start from 14 days
df_pc = df_pc[df_pc['dt'] >= 14]
df_pc['Results'] = 'PhysiCell'

df_exp = pd.DataFrame(data=zip(expe_dt,expe_diam),columns=['dt','diam'])
df_exp.insert(loc=2, column='Results', value='Experimental')

df_biod = pd.DataFrame(data=zip(biodynamo_dt,biodynamo_diam),columns=['dt','diam'])
df_biod.insert(loc=2, column='Results', value='BioDynaMo')

df_all = pd.concat([
    df_exp,  # Experimental
    df_biod,  # BioDynaMo
    df_tisim,  # TiSim
    df_pc,    # PhysiCell
    df_chaste # Chaste
], ignore_index=True)

# Remove any NaN values that might have been introduced
df_all = df_all.dropna(subset=['dt', 'diam'])

# Sort by time for better plotting
df_all = df_all.sort_values('dt')

# Print some diagnostic information
print("\nDataFrame Info:")
print(df_all.info())
print("\nSample of combined data:")
print(df_all.head())
print("\nNumber of points per simulator:")
print(df_all['Results'].value_counts())

# Set plotting order and color/marker mapping
results_order = ['BioDynaMo', 'Chaste', 'PhysiCell', 'TiSim', 'Experimental']
color_map = {
    'BioDynaMo': '#e41a1c',   # red
    'Chaste': '#377eb8',      # blue
    'Experimental': '#000000',# black
    'PhysiCell': '#4daf4a',   # green
    'TiSim': '#984ea3'        # purple (changed from yellow)
}
linestyle_map = {
    'BioDynaMo': '-',
    'Chaste': '--',
    'PhysiCell': '-.',
    'TiSim': ':',
    'Experimental': '-'  # solid for experimental
}
linewidth_map = {
    'BioDynaMo': 2,
    'Chaste': 2,
    'PhysiCell': 2,
    'TiSim': 2,
    'Experimental': 3.5  # thicker for experimental
}
marker_map = {
    'Experimental': 'X'
}

# Set up the figure with specific dimensions (Nature's column width is 89mm)
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(8.9, 4))  # 89mm width, height adjusted for readability

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
    'figure.dpi': 300
})

# Create interpolated experimental line for deviation plot
exp_times = df_exp['dt'].values
exp_diams = df_exp['diam'].values
exp_interp = interp1d(exp_times, exp_diams, kind='linear', bounds_error=False, fill_value=(exp_diams[0], exp_diams[-1]))

# First plot (original)
df_exp_plot = df_all[df_all['Results'] == 'Experimental']
ax1.plot(
    df_exp_plot['dt'], df_exp_plot['diam'],
    color=color_map['Experimental'],
    label='Experimental',
    linestyle=linestyle_map['Experimental'],
    linewidth=1.5,  # Slightly thicker for experimental
    marker=marker_map.get('Experimental', None),
    markersize=4,   # Smaller markers
    markeredgecolor='k',
    markerfacecolor=color_map['Experimental'],
    alpha=0.4,
    zorder=1
)

# Plot all other results
for result in ['BioDynaMo', 'Chaste', 'PhysiCell', 'TiSim']:
    df = df_all[df_all['Results'] == result]
    ax1.plot(
        df['dt'], df['diam'],
        color=color_map[result],
        label=result,
        linestyle=linestyle_map[result],
        linewidth=1,
        zorder=2
    )

# Customize first plot
ax1.set_xlabel("Time (days)", labelpad=2)
ax1.set_ylabel("Diameter (μm)", labelpad=2)
ax1.set_xlim(left=df_all['dt'].min() - 0.5, right=df_all['dt'].max() + 0.5)
ax1.set_ylim(bottom=df_all['diam'].min() - 100, top=df_all['diam'].max() + 100)

# Add grid to first plot (subtle)
ax1.grid(True, which='major', axis='both', color='grey', linestyle='-', linewidth=0.2, alpha=0.2)
ax1.set_axisbelow(True)

# Remove top and right spines
ax1.spines['top'].set_visible(False)
ax1.spines['right'].set_visible(False)

# Second plot (deviations)
for result in ['BioDynaMo', 'Chaste', 'PhysiCell', 'TiSim']:
    df = df_all[df_all['Results'] == result]
    exp_values = exp_interp(df['dt'])
    deviations = df['diam'] - exp_values
    
    ax2.plot(
        df['dt'], 
        deviations,
        color=color_map[result],
        label=result,
        linestyle=linestyle_map[result],
        linewidth=1,
        zorder=2
    )

# Add zero line for reference
ax2.axhline(y=0, color='black', linestyle='-', alpha=0.3, linewidth=0.5, zorder=1)

# Customize second plot
ax2.set_xlabel("Time (days)", labelpad=2)
ax2.set_ylabel("Deviation from Experimental (μm)", labelpad=2)
ax2.set_xlim(left=df_all['dt'].min() - 0.5, right=df_all['dt'].max() + 0.5)

# Add grid to second plot (subtle)
ax2.grid(True, which='major', axis='both', color='grey', linestyle='-', linewidth=0.2, alpha=0.2)
ax2.set_axisbelow(True)

# Remove top and right spines
ax2.spines['top'].set_visible(False)
ax2.spines['right'].set_visible(False)

# Add shared legend
handles, labels = ax1.get_legend_handles_labels()
fig.legend(handles, labels, title="Results", 
          loc='center left', bbox_to_anchor=(1.02, 0.5), 
          borderaxespad=0., frameon=False)

# Add subplot labels
ax1.text(-0.1, 1.1, 'a', transform=ax1.transAxes, fontsize=12, fontweight='bold')
ax2.text(-0.1, 1.1, 'b', transform=ax2.transAxes, fontsize=12, fontweight='bold')

# Adjust layout
plt.tight_layout()


save_dir = "./ResultAnalysis/plots/monolayer_plots"
os.makedirs(save_dir, exist_ok=True)

# Save as PDF (preferred for publications)
plt.savefig(os.path.join(save_dir, "monolayer_comparison_combined.pdf"), 
            format='pdf',
            bbox_inches='tight', 
            pad_inches=0.1)

# Optionally, also save as SVG
plt.savefig(os.path.join(save_dir, "monolayer_comparison_combined.svg"), 
            format='svg',
            bbox_inches='tight', 
            pad_inches=0.1)

# Keep PNG for quick previews if needed
plt.savefig(os.path.join(save_dir, "monolayer_comparison_combined.png"), 
            dpi=300, 
            bbox_inches='tight', 
            pad_inches=0.1,
            format='png')



