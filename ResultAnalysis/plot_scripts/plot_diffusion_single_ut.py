import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
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
    'BioDynaMo': '#ff7f00',   # Orange
    'Chaste': '#377eb8',      # Blue
    'PhysiCell': '#4daf4a',   # Green
    'TiSim': '#984ea3'        # Purple
}

linestyles = {
    'BioDynaMo': '-',   # Solid
    'Chaste': '-',     # Solid
    'PhysiCell': '-',  # Solid
    'TiSim': '-'        # Solid
}

# Update figure settings for better readability
plt.rcParams.update({
    'font.family': 'sans-serif',
    'font.sans-serif': ['DejaVu Sans', 'Helvetica', 'Arial', 'sans-serif'],
    'font.size': 8,  # Increased from 7
    'axes.labelsize': 9,  # Increased from 7
    'axes.titlesize': 9,  # Increased from 7
    'xtick.labelsize': 8,  # Increased from 7
    'ytick.labelsize': 8,  # Increased from 7
    'legend.fontsize': 8,  # Increased from 7
    'lines.linewidth': 1.8,  # Increased from 1
    'axes.linewidth': 0.8,  # Increased from 0.5
    'xtick.major.width': 0.8,  # Increased from 0.5
    'ytick.major.width': 0.8,  # Increased from 0.5
    'xtick.major.size': 3,  # Increased from 2
    'ytick.major.size': 3,  # Increased from 2
    'figure.dpi': 400
})

# Create individual figures instead of subplots
def create_plot(data, xlim=None, ylim=None, title=None, filename=None, markers=False, figsize=(3, 3)):
    fig, ax = plt.subplots(figsize=figsize, dpi=400)
    
    # Plot data
    for label, df, y, mask in data:
        x = df['timestep'][mask]
        y = y[mask]
        ax.plot(x, y, color=colors[label], linestyle=linestyles[label], linewidth=1.8, alpha=0.7)
        if markers:
            ax.plot(x[::5], y.iloc[::5], 'o', color=colors[label], markersize=4, alpha=0.7)
    
    # Set limits if provided
    if xlim:
        ax.set_xlim(xlim)
    if ylim:
        ax.set_ylim(ylim)
    
    # Labels (no grid)
    ax.set_xlabel("Time (min)", fontsize=9, labelpad=4)
    ax.set_ylabel("Concentration (μM)", fontsize=9, labelpad=4)
    # ax.grid(True, alpha=0.3, linewidth=0.5)  # <-- REMOVE or comment out this line
    
    # Remove top and right spines
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    
    # Add title if provided
    if title:
        ax.text(-0.18, 1.1, title, transform=ax.transAxes, fontsize=11, fontweight='bold')
    
    plt.tight_layout()
    
    # Save figure
    if filename:
        save_dir = "./ResultAnalysis/plots/diffusion_single_ut_plots"
        os.makedirs(save_dir, exist_ok=True)
        plt.savefig(os.path.join(save_dir, f"{filename}.pdf"), 
                   format='pdf',
                   bbox_inches='tight', 
                   pad_inches=0.1)
        plt.savefig(os.path.join(save_dir, f"{filename}.svg"), 
                   format='svg',
                   bbox_inches='tight', 
                   pad_inches=0.1)
        plt.savefig(os.path.join(save_dir, f"{filename}.png"), 
                   format='png',
                   bbox_inches='tight', 
                   pad_inches=0.1,
                   dpi=600)
    
    plt.close()

# Create and save individual plots
# Full time course (tall and narrow)
create_plot([
    ('BioDynaMo', bdm_df, bdm_df['cen_diff'], slice(None)),
    ('Chaste', ch_df, ch_df['diff'], slice(None)),
    ('PhysiCell', pc_df, pc_df['diff']/602.2, slice(None)),
    ('TiSim', tisim_df, tisim_df['diff'], tisim_df['timestep'] <= 10)
], title='a', filename='diffusion_full_time', figsize=(7, 3.5))

# Early time points (keep square)
create_plot([
    ('BioDynaMo', bdm_df, bdm_df['cen_diff'], slice(None)),
    ('Chaste', ch_df, ch_df['diff'], slice(None)),
    ('PhysiCell', pc_df, pc_df['diff']/602.2, slice(None)),
    ('TiSim', tisim_df, tisim_df['diff'], tisim_df['timestep'] <= 10)
], xlim=(0, 0.5), ylim=(0, None), title='b', filename='diffusion_early_time', markers=True)

# Last 0.5 minutes (keep square)
create_plot([
    ('BioDynaMo', bdm_df, bdm_df['cen_diff'], slice(None)),
    ('Chaste', ch_df, ch_df['diff'], slice(None)),
    ('PhysiCell', pc_df, pc_df['diff']/602.2, slice(None)),
    ('TiSim', tisim_df, tisim_df['diff'], slice(None))
], xlim=(9.5, 10), ylim=(9.3, 9.6), title='c', filename='diffusion_late_time', markers=False)

def create_complete_plot():
    fig = plt.figure(figsize=(8, 5))
    gs = gridspec.GridSpec(2, 2, height_ratios=[0.7, 1.2], width_ratios=[1, 1])

    # Top left: full timecourse
    ax_full = fig.add_subplot(gs[0, 0])
    ax_full.plot(bdm_df['timestep'], bdm_df['cen_diff'],
                 label='BioDynaMo', color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], linewidth=1.8, alpha=0.7)
    ax_full.plot(ch_df['timestep'], ch_df['diff'],
                 label='Chaste', color=colors['Chaste'], linestyle=linestyles['Chaste'], linewidth=1.8, alpha=0.7)
    ax_full.plot(pc_df['timestep'], pc_df['diff']/602.2, 
                 label='PhysiCell', color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], linewidth=1.8, alpha=0.7)
    ax_full.plot(tisim_df[tisim_df['timestep'] <= 10]['timestep'],
                 tisim_df[tisim_df['timestep'] <= 10]['diff'],
                 label='TiSim', color=colors['TiSim'], linestyle=linestyles['TiSim'], linewidth=1.8, alpha=0.7)
    ax_full.set_ylabel("Concentration (μM)", fontsize=12, labelpad=4)
    ax_full.set_xlabel("Time (min)", fontsize=12, labelpad=4)
    ax_full.tick_params(axis='both', which='major', labelsize=11)
    ax_full.spines['top'].set_visible(False)
    ax_full.spines['right'].set_visible(False)

    # Top right: empty (for future drawing)
    ax_empty = fig.add_subplot(gs[0, 1])
    ax_empty.axis('off')

    # Bottom left: zoom into the beginning
    ax_zoom_start = fig.add_subplot(gs[1, 0])
    ax_zoom_start.plot(bdm_df['timestep'], bdm_df['cen_diff'],
                      label='BioDynaMo', color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], linewidth=1.8, alpha=0.7)
    ax_zoom_start.plot(ch_df['timestep'], ch_df['diff'],
                      label='Chaste', color=colors['Chaste'], linestyle=linestyles['Chaste'], linewidth=1.8, alpha=0.7)
    ax_zoom_start.plot(pc_df['timestep'], pc_df['diff']/602.2, 
                      label='PhysiCell', color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], linewidth=1.8, alpha=0.7)
    ax_zoom_start.plot(tisim_df[tisim_df['timestep'] <= 10]['timestep'],
                      tisim_df[tisim_df['timestep'] <= 10]['diff'],
                      label='TiSim', color=colors['TiSim'], linestyle=linestyles['TiSim'], linewidth=1.8, alpha=0.7)
    ax_zoom_start.set_xlim(0, 0.5)
    ax_zoom_start.set_ylim(0, None)
    ax_zoom_start.set_xlabel("Time (min)", fontsize=12, labelpad=4)
    ax_zoom_start.set_ylabel("Concentration (μM)", fontsize=12, labelpad=4)
    ax_zoom_start.tick_params(axis='both', which='major', labelsize=11)
    ax_zoom_start.spines['top'].set_visible(False)
    ax_zoom_start.spines['right'].set_visible(False)

    # Bottom right: zoom into the end
    ax_zoom_end = fig.add_subplot(gs[1, 1])
    ax_zoom_end.plot(bdm_df['timestep'], bdm_df['cen_diff'],
                     label='BioDynaMo', color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], linewidth=1.8, alpha=0.7)
    ax_zoom_end.plot(ch_df['timestep'], ch_df['diff'],
                     label='Chaste', color=colors['Chaste'], linestyle=linestyles['Chaste'], linewidth=1.8, alpha=0.7)
    ax_zoom_end.plot(pc_df['timestep'], pc_df['diff']/602.2, 
                     label='PhysiCell', color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], linewidth=1.8, alpha=0.7)
    ax_zoom_end.plot(tisim_df['timestep'], tisim_df['diff'],
                     label='TiSim', color=colors['TiSim'], linestyle=linestyles['TiSim'], linewidth=1.8, alpha=0.7)
    ax_zoom_end.set_xlim(9.5, 10)
    ax_zoom_end.set_ylim(9.3, 9.6)
    ax_zoom_end.set_xlabel("Time (min)", fontsize=12, labelpad=4)
    ax_zoom_end.set_ylabel("Concentration (μM)", fontsize=12, labelpad=4)
    ax_zoom_end.tick_params(axis='both', which='major', labelsize=11)
    ax_zoom_end.spines['top'].set_visible(False)
    ax_zoom_end.spines['right'].set_visible(False)

    # Shared legend (move above the plots)
    handles, labels = ax_full.get_legend_handles_labels()
    fig.legend(
        handles, labels,
        loc='lower center',
        bbox_to_anchor=(0.5, 1.02),
        ncol=4,
        frameon=True,
        framealpha=1.0,
        fontsize=11
    )

    plt.tight_layout(rect=[0, 0, 1, 0.98])
    plt.subplots_adjust(hspace=0.32)
    save_dir = "./ResultAnalysis/plots/diffusion_single_ut_plots"
    os.makedirs(save_dir, exist_ok=True)
    plt.savefig(os.path.join(save_dir, "diffusion_single_ut.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
    plt.savefig(os.path.join(save_dir, "diffusion_single_ut.svg"), format='svg', bbox_inches='tight', pad_inches=0.1)
    plt.savefig(os.path.join(save_dir, "diffusion_single_ut.png"), format='png', bbox_inches='tight', pad_inches=0.1, dpi=600)
    plt.close()

# Create complete plot
create_complete_plot()

def create_complete_scatter_plot():
    fig = plt.figure(figsize=(8, 5))
    gs = gridspec.GridSpec(2, 2, height_ratios=[0.7, 1.2], width_ratios=[1, 1])

    marker_dict = {
        'BioDynaMo': 'o',
        'Chaste': 's',
        'PhysiCell': '^',
        'TiSim': 'D'
    }
    point_size = 4

    # Top left: full timecourse
    ax_full = fig.add_subplot(gs[0, 0])
    ax_full.scatter(bdm_df['timestep'], bdm_df['cen_diff'],
                 label='BioDynaMo', color=colors['BioDynaMo'], marker=marker_dict['BioDynaMo'], alpha=0.7, s=point_size)
    ax_full.scatter(ch_df['timestep'], ch_df['diff'],
                 label='Chaste', color=colors['Chaste'], marker=marker_dict['Chaste'], alpha=0.7, s=point_size)
    ax_full.scatter(pc_df['timestep'], pc_df['diff']/602.2, 
                 label='PhysiCell', color=colors['PhysiCell'], marker=marker_dict['PhysiCell'], alpha=0.7, s=point_size)
    ax_full.scatter(tisim_df[tisim_df['timestep'] <= 10]['timestep'],
                 tisim_df[tisim_df['timestep'] <= 10]['diff'],
                 label='TiSim', color=colors['TiSim'], marker=marker_dict['TiSim'], alpha=0.7, s=point_size)
    ax_full.set_ylabel("Concentration (μM)", fontsize=12, labelpad=4)
    ax_full.set_xlabel("Time (min)", fontsize=12, labelpad=4)
    ax_full.tick_params(axis='both', which='major', labelsize=11)
    ax_full.spines['top'].set_visible(False)
    ax_full.spines['right'].set_visible(False)

    # Top right: empty (for future drawing)
    ax_empty = fig.add_subplot(gs[0, 1])
    ax_empty.axis('off')

    # Bottom left: zoom into the beginning
    ax_zoom_start = fig.add_subplot(gs[1, 0])
    ax_zoom_start.scatter(bdm_df['timestep'], bdm_df['cen_diff'],
                      label='BioDynaMo', color=colors['BioDynaMo'], marker=marker_dict['BioDynaMo'], alpha=0.7, s=point_size)
    ax_zoom_start.scatter(ch_df['timestep'], ch_df['diff'],
                      label='Chaste', color=colors['Chaste'], marker=marker_dict['Chaste'], alpha=0.7, s=point_size)
    ax_zoom_start.scatter(pc_df['timestep'], pc_df['diff']/602.2, 
                      label='PhysiCell', color=colors['PhysiCell'], marker=marker_dict['PhysiCell'], alpha=0.7, s=point_size)
    ax_zoom_start.scatter(tisim_df[tisim_df['timestep'] <= 10]['timestep'],
                      tisim_df[tisim_df['timestep'] <= 10]['diff'],
                      label='TiSim', color=colors['TiSim'], marker=marker_dict['TiSim'], alpha=0.7, s=point_size)
    ax_zoom_start.set_xlim(0, 0.5)
    ax_zoom_start.set_ylim(0, None)
    ax_zoom_start.set_xlabel("Time (min)", fontsize=12, labelpad=4)
    ax_zoom_start.set_ylabel("Concentration (μM)", fontsize=12, labelpad=4)
    ax_zoom_start.tick_params(axis='both', which='major', labelsize=11)
    ax_zoom_start.spines['top'].set_visible(False)
    ax_zoom_start.spines['right'].set_visible(False)

    # Bottom right: zoom into the end
    ax_zoom_end = fig.add_subplot(gs[1, 1])
    ax_zoom_end.scatter(bdm_df['timestep'], bdm_df['cen_diff'],
                     label='BioDynaMo', color=colors['BioDynaMo'], marker=marker_dict['BioDynaMo'], alpha=0.7, s=point_size)
    ax_zoom_end.scatter(ch_df['timestep'], ch_df['diff'],
                     label='Chaste', color=colors['Chaste'], marker=marker_dict['Chaste'], alpha=0.7, s=point_size)
    ax_zoom_end.scatter(pc_df['timestep'], pc_df['diff']/602.2, 
                     label='PhysiCell', color=colors['PhysiCell'], marker=marker_dict['PhysiCell'], alpha=0.7, s=point_size)
    ax_zoom_end.scatter(tisim_df['timestep'], tisim_df['diff'],
                     label='TiSim', color=colors['TiSim'], marker=marker_dict['TiSim'], alpha=0.7, s=point_size)
    ax_zoom_end.set_xlim(9.5, 10)
    ax_zoom_end.set_ylim(9.3, 9.6)
    ax_zoom_end.set_xlabel("Time (min)", fontsize=12, labelpad=4)
    ax_zoom_end.set_ylabel("Concentration (μM)", fontsize=12, labelpad=4)
    ax_zoom_end.tick_params(axis='both', which='major', labelsize=11)
    ax_zoom_end.spines['top'].set_visible(False)
    ax_zoom_end.spines['right'].set_visible(False)

    # Shared legend (move above the plots)
    handles, labels = ax_full.get_legend_handles_labels()
    fig.legend(
        handles, labels,
        loc='lower center',
        bbox_to_anchor=(0.5, 1.02),
        ncol=4,
        frameon=True,
        framealpha=1.0,
        fontsize=11
    )

    plt.tight_layout(rect=[0, 0, 1, 0.98])
    plt.subplots_adjust(hspace=0.32)
    save_dir = "./ResultAnalysis/plots/diffusion_single_ut_plots"
    os.makedirs(save_dir, exist_ok=True)
    plt.savefig(os.path.join(save_dir, "diffusion_single_ut_scatter.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.1)
    plt.savefig(os.path.join(save_dir, "diffusion_single_ut_scatter.svg"), format='svg', bbox_inches='tight', pad_inches=0.1)
    plt.savefig(os.path.join(save_dir, "diffusion_single_ut_scatter.png"), format='png', bbox_inches='tight', pad_inches=0.1, dpi=600)
    plt.close()

# Create complete scatter plot
create_complete_scatter_plot()










