import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
from sklearn.preprocessing import MinMaxScaler, StandardScaler
import os
import yaml
from pathlib import Path

pd.set_option('display.float_format', lambda x: '%.5f' % x)
# diffusion_single


ROOT = Path('/home/tntiniak/Work/observatory_benchmark')
if not ROOT.is_dir():
    raise FileNotFoundError(f'Repository root does not exist: {ROOT}')

PLOT_OUTPUT_DIR = ROOT / 'ResultAnalysis' / 'plots' / 'diffusion_single_ut_plots'
pd.set_option('display.float_format', lambda x: '%.5f' % x)

pc_file = ROOT / "PhysiCell/results/diffusion_single_cell_sink/physicell_diffusion_single_sink_plot_data.csv"
pc_df= pd.read_csv(pc_file,index_col=0)
pc_df = pc_df.loc[pc_df.index == 13]

# bdm_file = "../Biodynamo/diffusion_single/data.csv"
bdm_file = ROOT / "Biodynamo/diffusion_single/data.csv"
bdm_df= pd.read_csv(bdm_file,index_col=None,header=None,sep = " ",names = ['timestep','avg_diff','cen_diff'])


tisim_file = ROOT / "Tisim/diffusion_single/results/diffusion_1_cell.csv"
tisim_df= pd.read_csv(tisim_file,names = ['timestep','diff'],header=0)
tisim_df = pd.concat([pd.DataFrame({"timestep": [0],"diff":[0]}), tisim_df], ignore_index=True)


chaste_file = ROOT / "Chaste/diffusion_single/results/TestDiffusionSmall03.dat"
ch_df= pd.read_csv(chaste_file,sep='\s+',names = ['timestep','diff'],header=0)
timesteps = np.concatenate((np.linspace(0, 1, num=11)[:-1], np.arange(1, 11, 1)))
timesteps_rounded = np.round(timesteps, 2)
ch_df['timestep_rounded'] = ch_df['timestep'].round(2)
selected_rows = ch_df[ch_df['timestep_rounded'].isin(timesteps_rounded)]

with open(ROOT / "CompuTiX/diffusion_single/SinglePointSink/dt-s-0-6_N-3.yaml", "r") as f:
    mf_data = yaml.safe_load(f)
    
# ct_t = np.array( mf_data["t"]["values"] ) #[s]
# ct_x = np.array( mf_data['x']['values'] ) #[m]
# ct_v = np.array( mf_data['v']['values'] ) #[m/s]

ct_t = np.array( mf_data["time_series"]["values"]["t"]["values"] ) #[s]
ct_cdomain = np.array( mf_data["time_series"]["values"]["c_domain"]["values"] ) #[mol/m^3]
ct_ccentral = np.array( mf_data["time_series"]["values"]["c_central"]["values"] ) #[mol/m^3]
# create dataframe with the above values of computix
ct_df = pd.DataFrame({
    'timestep': ct_t/ 60 ,
    'c_domain': ct_cdomain*1e3 ,
    'c_central': ct_ccentral *1e3 
})
# -------------------------------------------------------------------------
# Load theoretical reference curves (CFD explicit solver & deal.II snapshots)
# -------------------------------------------------------------------------
cfd_csv = (
    ROOT / "ResultAnalysis" / "plots" / "diffusion_cfd_single_sink_plots" / "average_concentration_time_series.csv"
)
deal_csv = (
    ROOT / "ResultAnalysis" / "plots" / "diffusion_ground_truth_single_sink_plots" / "average_concentration_time_series.csv"
)
ct_df
def _load_theory(csv_path: str, label: str) -> pd.DataFrame:
    df = pd.read_csv(csv_path)
    # Rescale snap index (0 .. N-1) → minutes (0 .. 10)
    nsteps = len(df)
    df["timestep"] = df["snap"] / (nsteps - 1) * 10.0
    df.rename(columns={"conc_mean": "diff"}, inplace=True)
    df["label"] = label
    return df[["timestep", "diff", "label"]]

# cfd_df_ref = _load_theory(cfd_csv, "CFD theory")
# deal_df_ref = _load_theory(deal_csv, "deal.II theory")

# Nature/Cell Systems colorblind-friendly palette and correct linestyles
colors = {
    'BioDynaMo': '#ff7f00',   # Orange
    'Chaste': '#377eb8',      # Blue
    'PhysiCell': '#4daf4a',   # Green
    'TiSim': '#984ea3',       # Purple
    'Computix': "#fd2a2aff",  # Pink
    'CFD theory': '#000000',  # Black
    'deal.II theory': '#555555'  # Darker gray for visibility
}

linestyles = {
    'BioDynaMo': '-',   # Solid
    'Chaste': '-',     # Solid
    'PhysiCell': '-',  # Solid
    'TiSim': '-',       # Solid
    'Computix': '-',       # Solid
    'CFD theory': '--',
    'deal.II theory': ':'
}

# Optional per-label linewidth override – default handled later
linewidths = {
    'deal.II theory': 2.5,
}

# Marker dictionary (scatter)
marker_dict_theory = {
    'CFD theory': 'P',  # plus filled
    'deal.II theory': 'X',
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
    print(data[0])
    for label, df, y, mask in data:
        x = df['timestep'][mask]
        y = y[mask]
        ax.plot(x, y, color=colors[label], linestyle=linestyles[label], linewidth=linewidths.get(label, 1.8), alpha=0.7)
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
    
    plt.tight_layout(rect=[0.06, 0.06, 1, 0.97])  # add 6% left & bottom, 3% top margin
    plt.subplots_adjust(left=0.08, top=0.97, hspace=0.45, wspace=0.3)
    
    # Save figure
    if filename:
        save_dir = "./ResultAnalysis/plots/diffusion_single_ut_plots"
        os.makedirs(save_dir, exist_ok=True)
        # plt.savefig(os.path.join(save_dir, f"{filename}.pdf"), 
        #            format='pdf',
        #            bbox_inches='tight', 
        #            pad_inches=0.2)
        # plt.savefig(os.path.join(save_dir, f"{filename}.svg"), 
        #            format='svg',
        #            bbox_inches='tight', 
        #            pad_inches=0.2)
        plt.savefig(os.path.join(save_dir, f"{filename}.png"), 
                   format='png',
                   bbox_inches='tight', 
                   pad_inches=0.2,
                   dpi=600)
    
    plt.close()

# Helper to build the dataset list for create_plot
def _plot_entries():
    entries = [
        ('BioDynaMo', bdm_df, bdm_df['cen_diff'], slice(None)),
        ('Chaste', ch_df, ch_df['diff'], slice(None)),
        ('PhysiCell', pc_df, pc_df['center_uM'], slice(None)),
        ('TiSim', tisim_df, tisim_df['diff'], tisim_df['timestep'] <= 10),
        ('Computix', ct_df, ct_df['c_central'], slice(None))
        # Reference curves
        # ('CFD theory', cfd_df_ref, cfd_df_ref['diff'], slice(None)),
        # ('deal.II theory', deal_df_ref, deal_df_ref['diff'], slice(None)),
    ]

    return entries


# Create and save individual plots
create_plot(_plot_entries(), title='a', filename='diffusion_full_time', figsize=(7, 3.5))

create_plot(_plot_entries(), xlim=(0, 0.5), ylim=(0, None), title='b', filename='diffusion_early_time', markers=True)

create_plot(_plot_entries(), xlim=(9.5, 10), ylim=(9.1, 9.6), title='c', filename='diffusion_late_time', markers=False)


def create_complete_plot():
    fig = plt.figure(figsize=(8, 5))
    gs = gridspec.GridSpec(
        2,
        2,
        height_ratios=[0.7, 1.2],
        width_ratios=[1, 1],
        hspace=0.45,
        wspace=0.3,
    )

    # Top left: empty (blank)
    ax_empty = fig.add_subplot(gs[0, 0])
    ax_empty.axis('off')

    # Top right: full timecourse
    ax_full = fig.add_subplot(gs[0, 1])
    # Reference curves (full plot first to keep them behind if desired)
    # ax_full.plot(cfd_df_ref['timestep'], cfd_df_ref['diff'],
    #              label='CFD', color=colors['CFD theory'], linestyle=linestyles['CFD theory'], linewidth=linewidths.get('CFD theory', 1.8), alpha=0.7)
    # ax_full.plot(deal_df_ref['timestep'], deal_df_ref['diff'],
    #              label='deal.II', color=colors['deal.II theory'], linestyle=linestyles['deal.II theory'], linewidth=linewidths.get('deal.II theory', 1.8), alpha=0.7)

    ax_full.plot(bdm_df['timestep'], bdm_df['cen_diff'],
                 label='BioDynaMo', color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], linewidth=linewidths.get('BioDynaMo', 1.8), alpha=0.7)
    ax_full.plot(ch_df['timestep'], ch_df['diff'],
                 label='Chaste', color=colors['Chaste'], linestyle=linestyles['Chaste'], linewidth=linewidths.get('Chaste', 1.8), alpha=0.7)
    ax_full.plot(pc_df['timestep'], pc_df['center_uM'], 
                 label='PhysiCell', color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], linewidth=linewidths.get('PhysiCell', 1.8), alpha=0.7)
    ax_full.plot(tisim_df[tisim_df['timestep'] <= 10]['timestep'],
                 tisim_df[tisim_df['timestep'] <= 10]['diff'],
                 label='TiSim', color=colors['TiSim'], linestyle=linestyles['TiSim'], linewidth=linewidths.get('TiSim', 1.8), alpha=0.7)
    ax_full.plot(ct_df['timestep'], ct_df['c_central'],
                 label='Computix', color=colors['Computix'], linestyle=linestyles['Computix'], linewidth=linewidths.get('Computix', 1.8), alpha=0.7)
    # ax_full.plot(cfd_df_ref['timestep'], cfd_df_ref
    ax_full.set_ylabel("Concentration (μM)", fontsize=12, labelpad=4)
    ax_full.set_xlabel("Time (min)", fontsize=12, labelpad=4)
    ax_full.tick_params(axis='both', which='major', labelsize=11)
    ax_full.spines['top'].set_visible(False)
    ax_full.spines['right'].set_visible(False)

    # Bottom left: zoom into the beginning
    ax_zoom_start = fig.add_subplot(gs[1, 0])
    ax_zoom_start.plot(bdm_df['timestep'], bdm_df['cen_diff'],
                      label='BioDynaMo', color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], linewidth=linewidths.get('BioDynaMo', 1.8), alpha=0.7)
    ax_zoom_start.plot(ch_df['timestep'], ch_df['diff'],
                      label='Chaste', color=colors['Chaste'], linestyle=linestyles['Chaste'], linewidth=linewidths.get('Chaste', 1.8), alpha=0.7)
    ax_zoom_start.plot(pc_df['timestep'], pc_df['center_uM'], 
                      label='PhysiCell', color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], linewidth=linewidths.get('PhysiCell', 1.8), alpha=0.7)
    ax_zoom_start.plot(tisim_df[tisim_df['timestep'] <= 10]['timestep'],
                      tisim_df[tisim_df['timestep'] <= 10]['diff'],
                      label='TiSim', color=colors['TiSim'], linestyle=linestyles['TiSim'], linewidth=linewidths.get('TiSim', 1.8), alpha=0.7)
    ax_zoom_start.scatter(ct_df['timestep'], ct_df['c_central'],
                          label='Computix', color=colors['Computix'],linestyle=linestyles['Computix'], linewidth=linewidths.get('Computix', 1.8), alpha=0.7)
    # Reference curves (zoomed in)
    # ax_zoom_start.plot(cfd_df_ref['timestep'], cfd_df_ref['diff'], label='CFD', color=colors['CFD theory'], linestyle=linestyles['CFD theory'], linewidth=linewidths.get('CFD theory', 1.8), alpha=0.7)
    # ax_zoom_start.plot(deal_df_ref['timestep'], deal_df_ref['diff'], label='deal.II', color=colors['deal.II theory'], linestyle=linestyles['deal.II theory'], linewidth=linewidths.get('deal.II theory', 1.8), alpha=0.7)
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
                     label='BioDynaMo', color=colors['BioDynaMo'], linestyle=linestyles['BioDynaMo'], linewidth=linewidths.get('BioDynaMo', 1.8), alpha=0.7)
    ax_zoom_end.plot(ch_df['timestep'], ch_df['diff'],
                     label='Chaste', color=colors['Chaste'], linestyle=linestyles['Chaste'], linewidth=linewidths.get('Chaste', 1.8), alpha=0.7)
    ax_zoom_end.plot(pc_df['timestep'], pc_df['center_uM'], 
                     label='PhysiCell', color=colors['PhysiCell'], linestyle=linestyles['PhysiCell'], linewidth=linewidths.get('PhysiCell', 1.8), alpha=0.7)
    ax_zoom_end.plot(tisim_df['timestep'], tisim_df['diff'],
                     label='TiSim', color=colors['TiSim'], linestyle=linestyles['TiSim'], linewidth=linewidths.get('TiSim', 1.8), alpha=0.7)
    ax_zoom_end.scatter(ct_df['timestep'], ct_df['c_central'],
                        label='Computix', color=colors['Computix'], linestyle=linestyles['Computix'], linewidth=linewidths.get('Computix', 1.8), alpha=0.7)
    # Reference curves (zoomed in)
    # ax_zoom_end.plot(cfd_df_ref['timestep'], cfd_df_ref['diff'], label='CFD', color=colors['CFD theory'], linestyle=linestyles['CFD theory'], linewidth=linewidths.get('CFD theory', 1.8), alpha=0.7)
    # ax_zoom_end.plot(deal_df_ref['timestep'], deal_df_ref['diff'], label='deal.II', color=colors['deal.II theory'], linestyle=linestyles['deal.II theory'], linewidth=linewidths.get('deal.II theory', 1.8), alpha=0.7)
    ax_zoom_end.set_xlim(9.5, 10)
    ax_zoom_end.set_ylim(9.1, 10.1)
    ax_zoom_end.set_xlabel("Time (min)", fontsize=12, labelpad=4)
    ax_zoom_end.set_ylabel("Concentration (μM)", fontsize=12, labelpad=4)
    ax_zoom_end.tick_params(axis='both', which='major', labelsize=11)
    ax_zoom_end.spines['top'].set_visible(False)
    ax_zoom_end.spines['right'].set_visible(False)

    # Shared legend (move above the plots)
    handles, labels = ax_full.get_legend_handles_labels()
    fig.legend(
        handles,
        labels,
        loc='upper center',
        bbox_to_anchor=(0.5, -0.04),
        ncol=8,
        frameon=True,
        framealpha=1.0,
        fontsize=11,
    )

    # Ensure sufficient left margin so y-axis labels are fully visible
    plt.tight_layout(rect=[0.06, 0.06, 1, 0.97])  # add 6% left & bottom, 3% top margin
    plt.subplots_adjust(left=0.08, top=0.97, hspace=0.45, wspace=0.3)
    save_dir = ROOT / "ResultAnalysis" / "plots" / "diffusion_single_ut_plots"
    os.makedirs(save_dir, exist_ok=True)
    # plt.savefig(os.path.join(save_dir, "diffusion_single_ut.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.2)
    plt.savefig(os.path.join(save_dir, "diffusion_single_ut.svg"), format='svg', bbox_inches='tight', pad_inches=0.2)
    plt.savefig(os.path.join(save_dir, "diffusion_single_ut.png"), format='png', bbox_inches='tight', pad_inches=0.2, dpi=600)
    plt.close()


# Create complete plot
create_complete_plot()


def create_complete_scatter_plot():
    fig = plt.figure(figsize=(8, 5))
    gs = gridspec.GridSpec(
        2,
        2,
        height_ratios=[0.7, 1.2],
        width_ratios=[1, 1],
        hspace=0.45,
        wspace=0.3,
    )

    marker_dict = {
        'BioDynaMo': 'o',
        'Chaste': 's',
        'PhysiCell': '^',
        'TiSim': 'D',
        'Computix': 'x',
        'CFD': 'P',
        'deal.II': 'X',
    }
    point_size = 4

    # Top left: empty (blank)
    ax_empty = fig.add_subplot(gs[0, 0])
    ax_empty.axis('off')

    # Top right: full timecourse scatter
    ax_full = fig.add_subplot(gs[0, 1])
    ax_full.scatter(bdm_df['timestep'], bdm_df['cen_diff'],
                 label='BioDynaMo', color=colors['BioDynaMo'], marker=marker_dict['BioDynaMo'], alpha=0.7, s=point_size)
    ax_full.scatter(ch_df['timestep'], ch_df['diff'],
                 label='Chaste', color=colors['Chaste'], marker=marker_dict['Chaste'], alpha=0.7, s=point_size)
    ax_full.scatter(pc_df['timestep'], pc_df['center_uM'], 
                 label='PhysiCell', color=colors['PhysiCell'], marker=marker_dict['PhysiCell'], alpha=0.7, s=point_size)
    ax_full.scatter(tisim_df[tisim_df['timestep'] <= 10]['timestep'],
                 tisim_df[tisim_df['timestep'] <= 10]['diff'],
                 label='TiSim', color=colors['TiSim'], marker=marker_dict['TiSim'], alpha=0.7, s=point_size)
    ax_full.scatter(ct_df['timestep'], ct_df['c_central'],
                 label='Computix', color=colors['Computix'], marker=marker_dict['Computix'], s=point_size, alpha=0.7)
    # Reference curves (full plot first to keep them
    # ax_full.scatter(cfd_df_ref['timestep'], cfd_df_ref['diff'], label='CFD', color=colors['CFD theory'], marker=marker_dict['CFD'], alpha=0.7, s=point_size)
    # ax_full.scatter(deal_df_ref['timestep'], deal_df_ref['diff'], label='deal.II', color=colors['deal.II theory'], marker=marker_dict['deal.II'], alpha=0.7, s=point_size)
    ax_full.set_ylabel("Concentration (μM)", fontsize=12, labelpad=4)
    ax_full.set_xlabel("Time (min)", fontsize=12, labelpad=4)
    ax_full.tick_params(axis='both', which='major', labelsize=11)
    ax_full.spines['top'].set_visible(False)
    ax_full.spines['right'].set_visible(False)

    # Bottom left: zoom into the beginning
    ax_zoom_start = fig.add_subplot(gs[1, 0])
    ax_zoom_start.scatter(bdm_df['timestep'], bdm_df['cen_diff'],
                      label='BioDynaMo', color=colors['BioDynaMo'], marker=marker_dict['BioDynaMo'], alpha=0.7, s=point_size)
    ax_zoom_start.scatter(ch_df['timestep'], ch_df['diff'],
                      label='Chaste', color=colors['Chaste'], marker=marker_dict['Chaste'], alpha=0.7, s=point_size)
    ax_zoom_start.scatter(pc_df['timestep'], pc_df['center_uM'], 
                      label='PhysiCell', color=colors['PhysiCell'], marker=marker_dict['PhysiCell'], alpha=0.7, s=point_size)
    ax_zoom_start.scatter(tisim_df[tisim_df['timestep'] <= 10]['timestep'],
                      tisim_df[tisim_df['timestep'] <= 10]['diff'],
                      label='TiSim', color=colors['TiSim'], marker=marker_dict['TiSim'], alpha=0.7, s=point_size)
    ax_zoom_start.scatter(ct_df['timestep'], ct_df['c_central'],
                          label='Computix', color=colors['Computix'], marker=marker_dict['Computix'], s=point_size, alpha=0.7)
    # Reference curves (zoomed in)
    # ax_zoom_start.scatter(cfd_df_ref['timestep'], cfd_df_ref['diff'], label='CFD', color=colors['CFD theory'], marker=marker_dict['CFD'], alpha=0.7, s=point_size)
    # ax_zoom_start.scatter(deal_df_ref['timestep'], deal_df_ref['diff'], label='deal.II', color=colors['deal.II theory'], marker=marker_dict['deal.II'], alpha=0.7, s=point_size)
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
    ax_zoom_end.scatter(pc_df['timestep'], pc_df['center_uM'], 
                     label='PhysiCell', color=colors['PhysiCell'], marker=marker_dict['PhysiCell'], alpha=0.7, s=point_size)
    ax_zoom_end.scatter(tisim_df['timestep'], tisim_df['diff'],
                     label='TiSim', color=colors['TiSim'], marker=marker_dict['TiSim'], alpha=0.7, s=point_size)
    ax_zoom_end.scatter(ct_df['timestep'], ct_df['c_central'],
                        label='Computix', color=colors['Computix'], marker=marker_dict['Computix'], s= point_size, alpha=0.7)
    # Reference curves (zoomed in)
    # ax_zoom_end.scatter(cfd_df_ref['timestep'], cfd_df_ref['diff'], label='CFD', color=colors['CFD theory'], marker=marker_dict['CFD'], alpha=0.7, s=point_size)
    # ax_zoom_end.scatter(deal_df_ref['timestep'], deal_df_ref['diff'], label='deal.II', color=colors['deal.II theory'], marker=marker_dict['deal.II'], alpha=0.7, s=point_size)
    ax_zoom_end.set_xlim(9.5, 10)
    ax_zoom_end.set_ylim(9.1, 10.1)
    ax_zoom_end.set_xlabel("Time (min)", fontsize=12, labelpad=4)
    ax_zoom_end.set_ylabel("Concentration (μM)", fontsize=12, labelpad=4)
    ax_zoom_end.tick_params(axis='both', which='major', labelsize=11)
    ax_zoom_end.spines['top'].set_visible(False)
    ax_zoom_end.spines['right'].set_visible(False)

    # Shared legend (move above the plots)
    handles, labels = ax_full.get_legend_handles_labels()
    fig.legend(
        handles,
        labels,
        loc='upper center',
        bbox_to_anchor=(0.5, -0.04),
        ncol=8,
        frameon=True,
        framealpha=1.0,
        fontsize=11,
    )

    # Ensure sufficient left margin so y-axis labels are fully visible
    plt.tight_layout(rect=[0.06, 0.06, 1, 0.97])  # add 6% left & bottom, 3% top margin
    plt.subplots_adjust(left=0.08, top=0.97, hspace=0.45, wspace=0.3)
    save_dir = "./ResultAnalysis/plots/diffusion_single_ut_plots"
    os.makedirs(save_dir, exist_ok=True)
    plt.savefig(os.path.join(save_dir, "diffusion_single_ut_scatter.pdf"), format='pdf', bbox_inches='tight', pad_inches=0.2)
    plt.savefig(os.path.join(save_dir, "diffusion_single_ut_scatter.svg"), format='svg', bbox_inches='tight', pad_inches=0.2)
    plt.savefig(os.path.join(save_dir, "diffusion_single_ut_scatter.png"), format='png', bbox_inches='tight', pad_inches=0.2, dpi=600)
    plt.close()

# Create complete scatter plot
create_complete_scatter_plot()