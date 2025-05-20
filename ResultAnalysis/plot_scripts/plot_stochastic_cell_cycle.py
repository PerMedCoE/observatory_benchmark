import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os
import matplotlib as mpl
import joypy
from scipy.stats import gaussian_kde

output_folder = "PhysiCell/results/custom_stochastic_cell_cycle/cell_volumes.csv"
pc_dt = 30.0

pc_df = pd.read_csv(output_folder, float_precision='round_trip', usecols=['id', "dt", "current_phase",'elapsed_time_in_phase'])
pc_df.replace({"current_phase":{4.0: "G0/G1", 10.0: "S", 12.0: "G2", 13.0: "M"}}, inplace=True)
pc_df.rename(columns={'id':'cell_id','current_phase':'phase'}, inplace=True)
pc_phase_times = pc_df.groupby(['cell_id', 'elapsed_time_in_phase'])['dt'].sum()


pc_df['phase_shift'] = pc_df['phase'] != pc_df.groupby('cell_id')['phase'].shift(1)
pc_df['phase_visit'] = pc_df.groupby('cell_id')['phase_shift'].cumsum()
phase_durations = (
    pc_df.groupby(['cell_id', 'phase', 'phase_visit'])
    .agg(start_time=('dt', 'first'), end_time=('dt', 'last'))
    .reset_index()
)
phase_durations['duration'] = phase_durations['end_time'] - phase_durations['start_time']
pc_phases= phase_durations.groupby(['cell_id', 'phase'])['duration'].sum().reset_index()
pc_phases['tool']= 'PhysiCell'
pc_phases['duration'] = pc_phases['duration'] / 60


output_folder = "Chaste/unit_test_cellcycle/results/cellcycle_fixed.dat"
ch_dt = 0.1
ch_df = pd.DataFrame(columns=["dt","cell_id","x","y","z","g1_duration","s_duration","g2_duration","m_duration","current_phase","target_area","volume"])
with open(output_folder, "r") as f:
    for line in f.read().splitlines():
        data = line.split()
        data = [float(x) if x.replace('.', '', 1).isdigit() else x for x in data]
        dt = data[0]
        for i in range(0,len(data)//11):
            row = {'dt': dt, 'cell_id': data[1+11*i], 'x': data[2+11*i], 'y': data[3+11*i], 'z': data[4+11*i], 'g1_duration': data[5+11*i], 's_duration': data[6+11*i], 'g2_duration': data[7+11*i], 'm_duration': data[8+11*i], 'current_phase': data[9+11*i], 'target_area': data[10+11*i], 'volume': data[11+11*i]}
            row = pd.Series(row)
            df2 = pd.DataFrame(row).transpose()
            df2['current_phase'] = df2['current_phase'].replace({'G1': 'G0/G1'})

            ch_df =pd.concat([ch_df,df2],ignore_index=True)


results = []

for cell_id, group in ch_df.groupby("cell_id"):
    group = group.sort_values("dt").reset_index(drop=True)
    
    last_phase = None
    start_time = None

    for i, row in group.iterrows():
        current_phase = row["current_phase"]
        current_time = row["dt"]
        
        if last_phase is None:
            # Initial phase
            last_phase = current_phase
            start_time = current_time
            continue

        if current_phase != last_phase:
            # Phase change detected
            duration = current_time - start_time
            results.append({
                "cell_id": cell_id,
                "phase": last_phase,
                "start_time": start_time,
                "end_time": current_time,
                "duration": duration
            })
            # Start new phase
            last_phase = current_phase
            start_time = current_time

    # Final stretch
    if start_time is not None and start_time != current_time:
        duration = current_time - start_time
        results.append({
            "cell_id": cell_id,
            "phase": last_phase,
            "start_time": start_time,
            "end_time": current_time,
            "duration": duration,
            'tool' : 'Chaste'
        })

# Convert to DataFrame
phase_durations_df2 = pd.DataFrame(results)
ch_phases = phase_durations_df2.groupby(['cell_id', 'phase'])['duration'].sum().reset_index()
ch_phases['tool'] = 'Chaste'


output_folder = "Biodynamo/unit_test_cellcycle_stoch/new_results/output/"
cell_indices = [0, 2, 3, 4]
bd_dt = 0.01

phase_map = {1: "G0/G1", 2: "S", 3: "G2", 4: "M"}
all_cells = []

for idx in cell_indices:
    fname = os.path.join(output_folder, f'cell-{idx}.csv')
    df = pd.read_csv(fname, names=['timestep', 'volume', 'current_phase', 'Age'], header=None)
    df = df[df.current_phase != 0]  # skip unknowns
    df["cell_id"] = idx
    df["dt"] = bd_dt
    df = df.sort_values(by='timestep').reset_index(drop=True)
    all_cells.append(df)

bd_df = pd.concat(all_cells, ignore_index=True)
bd_df['current_phase'] = bd_df['current_phase'].replace(phase_map)
bd_df

results = []

for cell_id, group in bd_df.groupby("cell_id"):
    group = group.sort_values("timestep").reset_index(drop=True)

    last_phase = None
    start_time = None

    for i, row in group.iterrows():
        current_phase = row["current_phase"]
        current_time = row["timestep"]

        if last_phase is None:
            last_phase = current_phase
            start_time = current_time
            continue

        if current_phase != last_phase:
            duration = current_time - start_time
            results.append({
                "cell_id": cell_id,
                "phase": last_phase,
                "start_time": start_time,
                "end_time": current_time,
                "duration": duration
            })
            last_phase = current_phase
            start_time = current_time

    # Handle final stretch
    if start_time is not None and start_time != current_time:
        duration = current_time - start_time
        results.append({
            "cell_id": cell_id,
            "phase": last_phase,
            "start_time": start_time,
            "end_time": current_time,
            "duration": duration
        })

# Convert to DataFrame
phase_durations_bd = pd.DataFrame(results)

bd_phases = phase_durations_bd.groupby(['cell_id', 'phase'])['duration'].sum().reset_index()
bd_phases['tool'] = "Biodynamo"
bd_phases

output_folder = "Tisim/unit_test_cellcycle_stoch/cell cycle stochastic.csv"
df = pd.read_csv(output_folder, float_precision='round_trip',header=0)
df


rows = []
n_cells = (len(df.columns) - 1) // 2
time_col = df.columns[0]

# Iterate over each cell
for i in range(1,n_cells):

    print(i)
    vol_col = f"cell {i+1} volume"
    phase_col = f"cell {i+1} phase"

    # Drop rows with missing phase (cell not born yet or already dead)
    cell_df = df[[time_col, phase_col]].dropna()
    cell_df = cell_df.rename(columns={time_col: "time", phase_col: "phase"})
    cell_df ['cell_id'] = i
    # Identify phase transitions
    prev_phase = None
    start_time = None

    for _, row in cell_df.iterrows():
        current_time = row["time"]
        current_phase = row["phase"]

        if current_phase != prev_phase:
            if prev_phase is not None:
                duration = current_time - start_time
                rows.append({
                    "phase": prev_phase,
                    "duration": duration,
                    "tool": "Tisim",  
                    "cell_id": i
                })
            start_time = current_time
            prev_phase = current_phase

    # Add last phase duration if needed
    if prev_phase is not None and start_time is not None:
        duration = cell_df["time"].iloc[-1] - start_time
        rows.append({
            "phase": prev_phase,
            "duration": duration,
            "tool": "Tisim",
            "cell_id": i
        })

# Create final DataFrame
converted_df = pd.DataFrame(rows)
converted_df

ts_phases = converted_df.groupby(['cell_id', 'phase'])['duration'].sum().reset_index()
ts_phases['tool'] = "Tisim"
ts_phases.replace({"phase":{"G1": "G0/G1"}}, inplace=True)

total_phase_times = pd.concat([pc_phases, ch_phases, bd_phases,ts_phases], ignore_index=True)
total_phase_times

# total_phase_times["phase"] = total_phase_times["phase"].map(phase_map).fillna(df["phase"])

# Standardize tool names before plotting
total_phase_times['tool'] = total_phase_times['tool'].replace({
    'Biodynamo': 'BioDynaMo',
    'Tisim': 'TiSim',
    'biodynamo': 'BioDynaMo',
    'tisim': 'TiSim',
    'physicell': 'PhysiCell',
    'chaste': 'Chaste'
})

# Define phase and tool order after standardization
phase_order = ["G0/G1", "S", "G2", "M"]
tool_order = ["PhysiCell", "Chaste", "BioDynaMo", "TiSim"]

# Set as categorical
total_phase_times["phase"] = pd.Categorical(total_phase_times["phase"], categories=phase_order, ordered=True)
total_phase_times["tool"] = pd.Categorical(total_phase_times["tool"], categories=tool_order, ordered=True)

# Set up colorblind-friendly palette (include all variants)
tool_colors = {
    'PhysiCell': '#4daf4a',
    'Chaste': '#377eb8',
    'BioDynaMo': '#e41a1c',
    'TiSim': '#984ea3',
}

# Update font and axes settings for publication
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

# Create the boxplot with tools on the Y axis and phases as columns
g = sns.catplot(
    data=total_phase_times,
    y="tool",
    x="duration",
    col="phase",
    kind="box",
    order=tool_order,
    col_order=phase_order,
    palette=tool_colors,
    height=3.5,
    aspect=1,
    linewidth=1,
    fliersize=2,
    showmeans=True,
    meanprops={"marker":"o",
               "markerfacecolor":"white", 
               "markeredgecolor":"black",
               "markersize":"5"}
)

# Overlay stripplot (jittered points) and set y-ticks/labels
letters = ['a', 'b', 'c', 'd']
for i, phase in enumerate(phase_order):
    ax = g.axes[0][i]
    sns.stripplot(
        data=total_phase_times[total_phase_times["phase"] == phase],
        y="tool",
        x="duration",
        order=tool_order,
        palette=tool_colors,
        ax=ax,
        dodge=True,
        alpha=0.6,
        jitter=True,
        size=3,
        linewidth=0.5,
        edgecolor='gray'
    )
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.spines['left'].set_visible(False)
    ax.grid(True, axis='x', alpha=0.3, linewidth=0.5)
    # Add subplot letter
    ax.text(-0.12, 1.05, letters[i], transform=ax.transAxes, fontsize=14, fontweight='bold', va='top', ha='right')
    # Show x-axis label and ticks for all subplots
    ax.set_xlabel("Duration (hours)", fontsize=10)
    # Explicitly set y-ticks and labels for all tools
    ax.set_yticks(range(len(tool_order)))
    ax.set_yticklabels(tool_order, fontsize=10)
    if i == 0:
        ax.set_ylabel("Tool", fontsize=10)
    else:
        ax.set_ylabel("")

g.set_titles("{col_name} phase")
g.tight_layout()
g.fig.subplots_adjust(top=0.95)
g.fig.suptitle("")

# Save the full panel
save_dir = "./ResultAnalysis/plots/stochastic_cell_cycle_plots"
os.makedirs(save_dir, exist_ok=True)
g.savefig(os.path.join(save_dir, "stochastic_cell_cycle_boxplot_toolsYaxis.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
g.savefig(os.path.join(save_dir, "stochastic_cell_cycle_boxplot_toolsYaxis.png"), dpi=300, bbox_inches='tight', pad_inches=0.1)

# Save each phase subplot alone as PNG and PDF at 300 DPI
for i, phase in enumerate(phase_order):
    ax = g.axes[0][i]
    safe_phase = phase.replace("/", "_")
    fig = ax.get_figure()
    # Hide other axes for saving
    for j, other_ax in enumerate(g.axes[0]):
        if j != i:
            other_ax.set_visible(False)
    fig.savefig(os.path.join(save_dir, f"stochastic_cell_cycle_boxplot_{safe_phase}.png"), dpi=300, bbox_inches='tight', pad_inches=0.1)
    fig.savefig(os.path.join(save_dir, f"stochastic_cell_cycle_boxplot_{safe_phase}.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
    # Restore visibility for next iteration
    for j, other_ax in enumerate(g.axes[0]):
        other_ax.set_visible(True)