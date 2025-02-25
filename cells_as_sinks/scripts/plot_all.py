import sys,glob
from pathlib import Path
import numpy as np
import pandas as pd
import xml.etree.ElementTree as ET
import matplotlib.pyplot as plt
import seaborn as sns

turbine_folder = sys.argv[1]



instance_dirs = glob.glob(f"{turbine_folder}/instance_*")
all_data = []
print(instance_dirs)
# Print the directories
for directory in instance_dirs:
    xml_data = directory+"/output/settings.xml"
    print("hola "+ directory)

    tree = ET.parse(xml_data)
    root = tree.getroot()
    # root = ET.fromstring(xml_data)
    dx = root.find("./domain/dx").text
    uptake = root.find("./cell_definitions/cell_definition/phenotype/secretion/substrate/uptake_rate").text 
    volume = root.find("./cell_definitions/cell_definition/phenotype/volume/total").text
    dt = root.find("./overall/dt_diffusion").text
    mean_df = pd.read_csv(directory+"/microenv_many_diffusion.csv",header=0)
    print(type(dx))
    # mean_df['diff']/=602.2
    if uptake=="12044":
        mean_df['diff']/=602.2
    # Plot: Use seaborn for better styling
    plt.figure(figsize=(10, 6))
    # Add a unique label for each experiment
    mean_df["label"] = f"dx={dx}, uptake={uptake}, volume={volume}"
    mean_df["dx"] = float(dx)
    mean_df["uptake"] = float(uptake)
    mean_df["volume"] = float(volume)
    # Plot data
    plt.figure(figsize=(10, 6))
    sns.lineplot(
        data=mean_df,
        x="dt",
        y="diff",
        hue="label",  # Different lines for different dx and uptake combinations
        palette="tab10",  # Color palette for the lines
    )

    # Customize plot
    plt.title("Diffusion Experiments")
    plt.xlabel("Time (min)")
    plt.ylabel("Concentration")
    plt.legend(title="Experiments")
    plt.grid(True)
    plt.tight_layout()

    # Show plot
    plt.show()

# Append data to the list
    all_data.append(mean_df)

# Combine all data into a single DataFrame
if all_data:
    combined_df = pd.concat(all_data, ignore_index=True)

    # # Plot data
    # plt.figure(figsize=(10, 6))
    # sns.lineplot(
    #     data=combined_df,
    #     x="dt",
    #     y="diff",
    #     hue="label",  # Different lines for different dx and uptake combinations
    #     palette="tab10",  # Color palette for the lines
    # )

    # # Customize plot
    # plt.title("Diffusion Experiments")
    # plt.xlabel("Time (min)")
    # plt.ylabel("Concentration")
    # plt.legend(title="Experiments")
    # plt.grid(True)
    # plt.tight_layout()

    # # Show plot
    # plt.savefig(turbine_folder+"/concentrations602.png",dpi=300)
    # plt.show()
else:
    print("No valid data found to plot.")


conditions = [
    {"volume": 1, "dx": None},  # Fix uptake=12044 and volume=1, vary dx
    {"volume": 1, "dx": 10},     # Fix dx=10 and volume=1, vary uptake
    {"volume": 0.1, "dx": None}  # Fix uptake=12044 and dx=10, vary volume
]

# Generate plots
for i, condition in enumerate(conditions, start=1):
    # Filter data based on condition
    filtered_df = combined_df.copy()
    # print(filtered_df)
    # if condition["uptake"] is not None:
    #     filtered_df = filtered_df[filtered_df["uptake"] == condition["uptake"]]
    if condition["volume"] is not None:
        filtered_df = filtered_df[filtered_df["volume"] == condition["volume"]]
    if condition["dx"] is not None:
        filtered_df = filtered_df[filtered_df["dx"] == condition["dx"]]
    # Create the plot
    plt.figure(figsize=(20, 12))
    sns.lineplot(
        data=filtered_df,
        x="dt",
        y="diff",
        hue="label",
        palette="tab10"  # Adjust palette if needed
    )

    # Customize plot
    title = f"Plot {i}: "
    # title += f"uptake={condition['uptake']}" if condition["uptake"] is not None else "uptake varies"
    title += f", volume={condition['volume']}" if condition["volume"] is not None else ", volume varies"
    title += f", dx={condition['dx']}" if condition["dx"] is not None else ", dx varies"
    plt.title(title)
    plt.xlabel("Time (min)")
    plt.ylabel("Concentration")
    plt.legend(title="Experiments")
    plt.grid(True)
    plt.tight_layout()
    
    # # Save plot
    plot_filename = f"{turbine_folder}/plot_{i}_uptake__volume_{condition['volume']}_dx_{condition['dx']}.png"
    plt.savefig(plot_filename, dpi=300)
    plt.show()
    print(f"Saved plot to {plot_filename}")