import sys,glob
from pathlib import Path
import numpy as np
import pandas as pd
import xml.etree.ElementTree as ET
import matplotlib.pyplot as plt
import seaborn as sns

turbine_folder = sys.argv[1]



instance_dirs = glob.glob(f"{turbine_folder}/instances_*")
all_data = []
print(instance_dirs)
# Print the directories
for directory in instance_dirs:
    xml_data = directory+"/settings.xml"
    print("hola "+ directory)

    tree = ET.parse(xml_data)
    root = tree.getroot()
    # root = ET.fromstring(xml_data)
    dx = root.find("./domain/dx").text
    uptake = root.find("./user_parameters/uptake").text
    dt = root.find("./overall/dt_diffusion").text
    mean_df = pd.read_csv(directory+"/microenv_many_diffusion.csv",header=0)
    approach = directory
    print(uptake)
    # mean_df['diff']/=602.2
    if uptake=="12044":
        mean_df['diff']/=602.2
    # Plot: Use seaborn for better styling
    plt.figure(figsize=(10, 6))

    # Add a unique label for each experiment
    mean_df["label"] = f"dx={dx}, uptake={uptake}, approach{approach}"

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

    # Plot data
    plt.figure(figsize=(10, 6))
    sns.lineplot(
        data=combined_df,
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
    plt.savefig(turbine_folder+"/concentrations602.png",dpi=300)
    plt.show()
else:
    print("No valid data found to plot.")
