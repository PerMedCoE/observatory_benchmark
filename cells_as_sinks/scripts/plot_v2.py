import sys, glob
from pathlib import Path
import numpy as np
import pandas as pd
import xml.etree.ElementTree as ET
import matplotlib.pyplot as plt
import seaborn as sns

turbine_folder = sys.argv[1]

instance_dirs = glob.glob(f"{turbine_folder}/instance_*")
all_data = []

for directory in instance_dirs:
    xml_data = directory + "/output/settings.xml"
    
    tree = ET.parse(xml_data)
    root = tree.getroot()
    dx = float(root.find("./domain/dx").text)
    uptake = float(root.find("./cell_definitions/cell_definition/phenotype/secretion/substrate/uptake_rate").text)
    volume = float(root.find("./cell_definitions/cell_definition/phenotype/volume/total").text)
    dt = float(root.find("./overall/dt_diffusion").text)
    
    mean_df = pd.read_csv(directory + "/microenv_many_diffusion.csv", header=0)
    
    if uptake == 12044.0 or uptake == 6.17e-05:
        mean_df['diff'] /= 602.2
    
    mean_df["dx"] = dx
    mean_df["uptake"] = uptake
    mean_df["volume"] = volume
    mean_df["label"] = f"dx={dx}, uptake={uptake}, volume={volume}"
    all_data.append(mean_df)

if all_data:
    combined_df = pd.concat(all_data, ignore_index=True)
    
    dx_values = sorted(combined_df["dx"].unique())
    uptake_values = sorted(combined_df["uptake"].unique())
    
    fig, axes = plt.subplots(len(uptake_values), 1, figsize=(10, len(uptake_values) * 3), sharex=True)
    
    for i, uptake in enumerate(uptake_values):
        for dx in dx_values:
            subset = combined_df[(combined_df["dx"] == dx) & (combined_df["uptake"] == uptake)]
            if not subset.empty:
                sns.scatterplot(
                    data=subset, x="dt", y="diff", label=f"dx={dx}", ax=axes[i]
                )
        
        axes[i].set_title(f"Uptake Rate = {uptake}")
        axes[i].set_ylabel("Concentration")
        axes[i].legend()
    
    axes[-1].set_xlabel("Time (min)")
    plt.tight_layout()
    plt.show()

    pairs_df = pd.DataFrame([
        {"volume": v, "dx": d, "uptake": 20.0} 
        for v, d in zip([0.8, 12.5, 100, 800], [2, 5, 10, 20])
    ])

    pairs_merged = combined_df.merge(pairs_df, on=["volume", "dx","uptake"], how="inner")

    plt.figure(figsize=(12, 6))
    sns.lineplot(
        data=pairs_merged, x="dt", y="diff", hue="label", palette="tab10"
    )

    plt.title("Plot Pairs: volume varies, dx varies")
    plt.xlabel("Time (min)")
    plt.ylabel("Concentration")
    plt.legend(title="Experiments")
    plt.grid(True)
    plt.tight_layout()

    plot_filename = f"{turbine_folder}/plot_pairs.png"
    plt.savefig(plot_filename, dpi=300)
    plt.show()

    # Conditions plotting
    conditions = [
        {"volume": None, "uptake": 6.17e-05, "dx": None},
        {"volume": None, "uptake": 12044.0, "dx": 10},
        {"volume": None, "uptake": 20, "dx": 10},
        {"volume": None, "uptake": 20, "dx": 20},
        {"volume": [0.08, 1.25, 10, 80], "uptake": 20, "dx": None},
        {"volume": 10, "uptake": None, "dx": None}
    ]

    for i, condition in enumerate(conditions, start=1):
        filtered_df = combined_df.copy()
        if condition["volume"] is not None:
            if isinstance(condition["volume"], list):  
                filtered_df = filtered_df[filtered_df["volume"].isin(condition["volume"])]
            else:
                filtered_df = filtered_df[filtered_df["volume"] == condition["volume"]]
    
        if condition["dx"] is not None:
            filtered_df = filtered_df[filtered_df["dx"] == condition["dx"]]
        if condition["uptake"] is not None:
            filtered_df = filtered_df[filtered_df["uptake"] == condition["uptake"]]
        
        if filtered_df.empty:
            continue  # Skip if no data matches the condition
        
        plt.figure(figsize=(12, 6))
        sns.lineplot(
            data=filtered_df, x="dt", y="diff", hue="label", palette="tab10"
        )

        title = f"Plot {i}: "
        title += f", volume={condition['volume']}" if condition["volume"] is not None else ", volume varies"
        title += f", dx={condition['dx']}" if condition["dx"] is not None else ", dx varies"
        plt.title(title)
        plt.xlabel("Time (min)")
        plt.ylabel("Concentration")
        plt.legend(title="Experiments")
        plt.grid(True)
        plt.tight_layout()

        plot_filename = f"{turbine_folder}/plot_{i}.png"
        plt.savefig(plot_filename, dpi=300)
        plt.show()
