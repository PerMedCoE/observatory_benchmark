import pandas as pd
import matplotlib.pyplot as plt
import os

# Path to PhysiCell output (adapt to your run folder)
output_file = "PhysiCell/results/custom_stochastic_cell_cycle_100/cell_volumes.csv"

# Load PhysiCell results
pc_df = pd.read_csv(output_file, float_precision='round_trip').sort_values(by=['dt']).reset_index(drop=True)

# Convert minutes → hours
pc_df['dt'] = pc_df['dt'] / 60  

init_vol = pc_df.iloc[0]["total_volume"]

stats = pc_df.groupby('dt')['total_volume'].agg(['mean', 'std'])
time = stats.index
mean_vol = (stats['mean'] / init_vol) * 100
std_vol = (stats['std'] / init_vol) * 100

# Plot mean ± std
plt.figure(figsize=(6, 3))
plt.plot(time, mean_vol, label="PhysiCell (100 cells)", color="#4daf4a", linewidth=2)
plt.fill_between(time, mean_vol - std_vol, mean_vol + std_vol, 
                 color="#4daf4a", alpha=0.2, label="±1 std")

plt.xlabel("Time (hours)", fontsize=12)
plt.ylabel("% of initial volume", fontsize=12)
plt.title("PhysiCell Simulation – Starting from 100 Cells")
plt.legend()
plt.tight_layout()

# Save results
save_dir = "./ResultAnalysis/plots/physicell_only"
os.makedirs(save_dir, exist_ok=True)
plt.savefig(os.path.join(save_dir, "physicell_100cells_std.png"), dpi=300)

plt.show()