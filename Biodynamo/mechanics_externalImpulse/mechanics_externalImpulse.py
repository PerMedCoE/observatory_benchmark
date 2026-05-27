import sys,os,re,argparse,glob
sys.path.append('./pctk')
import pandas as pd
import numpy as np
from scipy.io import loadmat
from pathlib import Path
import matplotlib.pyplot as plt
from PIL import Image
from matplotlib.animation import FuncAnimation

def create_parser():
    parser = argparse.ArgumentParser(description="Perform analysis of Biodynamo Mechanics External Impulse")

    parser.add_argument("--data_folder", action="store", dest="data_folder", 
                        help="folder where the output data is stored", default="results/")
    parser.add_argument("--positions_csv", action="store", dest="positions_csv", 
                        default="positions.csv",
                        help="CSV file with position data")
    parser.add_argument("--speeds_csv", action="store", dest="speeds_csv", 
                        default="speeds.csv",
                        help="CSV file with speed data")
    parser.add_argument("--output_folder", action="store", dest="output_folder", 
                        default="results/",
                        help="folder to save output plots and images")

    return parser

def parse_position_data(filepath):
    """Parse position CSV with format: time, position_x, position_y, position_z"""
    data = []
    with open(filepath, 'r') as f:
        for line in f:
            parts = line.strip().split()
            if len(parts) >= 4:
                # Extract time and position vector
                time = float(parts[0])
                # Position is in format [x,y,z]
                pos_str = ' '.join(parts[1:])
                pos_str = pos_str.strip('[]')
                coords = [float(x) for x in pos_str.split(',')]
                data.append([time, coords[0], coords[1], coords[2]])
    return pd.DataFrame(data, columns=['time', 'position_x', 'position_y', 'position_z'])

def parse_speed_data(filepath):
    """Parse speed CSV with format: time, speed_x, speed_y, speed_z"""
    data = []
    with open(filepath, 'r') as f:
        for line in f:
            parts = line.strip().split()
            if len(parts) >= 4:
                # Extract time and speed vector
                time = float(parts[0])
                # Speed is in format [x,y,z]
                speed_str = ' '.join(parts[1:])
                speed_str = speed_str.strip('[]')
                coords = [float(x) for x in speed_str.split(',')]
                data.append([time, coords[0], coords[1], coords[2]])
    return pd.DataFrame(data, columns=['time', 'speed_x', 'speed_y', 'speed_z'])

def generate_plots(positions_df, speeds_df, output_folder):
    """Generate position and speed plots"""
    os.makedirs(output_folder, exist_ok=True)
    
    # Plot position vs time
    fig, ax = plt.subplots(figsize=(10, 6))
    ax.plot(positions_df['time'], positions_df['position_x'], 'x', color='blue', markersize=8, markeredgewidth=2)
    ax.set_xlabel('Time (s)', fontsize=12)
    ax.set_ylabel('Position X (nm)', fontsize=12)
    ax.set_title('Cell Position vs Time', fontsize=14, fontweight='bold')
    ax.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig(f"{output_folder}/position_vs_time.png", dpi=150)
    plt.close()
    print(f"Saved position plot to {output_folder}/position_vs_time.png")
    
    # Plot speed vs time
    fig, ax = plt.subplots(figsize=(10, 6))
    ax.plot(speeds_df['time'], speeds_df['speed_x'], 'x', color='red', markersize=8, markeredgewidth=2)
    ax.set_xlabel('Time (s)', fontsize=12)
    ax.set_ylabel('Speed X (nm/s)', fontsize=12)
    ax.set_title('Cell Speed vs Time', fontsize=14, fontweight='bold')
    ax.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig(f"{output_folder}/speed_vs_time.png", dpi=150)
    plt.close()
    print(f"Saved speed plot to {output_folder}/speed_vs_time.png")

def generate_pngs(positions_df, output_folder):
    """Generate PNG files for each time point showing the cell position"""
    os.makedirs(output_folder, exist_ok=True)
    
    # Determine axis limits based on data
    x_min = positions_df['position_x'].min() - 10
    x_max = positions_df['position_x'].max() + 10
    
    for idx, row in positions_df.iterrows():
        fig, ax = plt.subplots(figsize=(10, 6))
        
        # Draw the cell as a circle
        cell_radius = 5  # radius in nm
        circle = plt.Circle((row['position_x'], row['position_y']), cell_radius, 
                           color='blue', alpha=0.6, edgecolor='darkblue', linewidth=2)
        
        # Set the axis properties
        ax.set_aspect('equal')
        ax.add_artist(circle)
        ax.set_xlabel('X Position (nm)', fontsize=12)
        ax.set_ylabel('Y Position (nm)', fontsize=12)
        ax.set_xlim([x_min, x_max])
        ax.set_ylim([-15.0, 15.0])
        ax.grid(True, alpha=0.3)
        ax.axhline(y=0, color='k', linestyle='--', alpha=0.3)
        ax.axvline(x=0, color='k', linestyle='--', alpha=0.3)
        
        # Title with time information
        plt.title(f"BioDynaMo External Impulse - Time: {row['time']:.1f}s", 
                 fontsize=14, fontweight='bold')
        
        # Save the figure
        plt.savefig(f"{output_folder}/position_timepoint_{idx:04d}.png", dpi=100)
        plt.close()
    
    print(f"Generated {len(positions_df)} PNG files in {output_folder}")
    
def get_key(fp):
    """Extract numerical index from filename for sorting"""
    filename = os.path.splitext(os.path.basename(fp))[0]
    matches = re.findall(r'\d+', filename)
    if matches:
        # Return the last sequence of digits as an integer
        return int(matches[-1])
    else:
        # Return a default value if no digits are found
        return 0
    
def generate_gif(positions_df, output_folder):
    """Generate GIF animation from PNG files"""
    # Generate PNGs first
    generate_pngs(positions_df, output_folder)
        
    # List of image file paths sorted by time point
    image_files = sorted(glob.glob(f"{output_folder}/position_timepoint_*.png"), key=get_key)
    
    if not image_files:
        print(f"No PNG files found in {output_folder}")
        return
        
    # Open images one by one and append to frames
    frames = []
    for image in image_files:
        with Image.open(image) as img:
            frames.append(img.copy())  # Copy the image to store in memory
        
    # Save the frames as a GIF
    if frames:
        gif_path = f"{output_folder}/Biodynamo_externalImpulse.gif"
        frame_one = frames[0]
        frame_one.save(gif_path, format="GIF", append_images=frames[1:],
                      save_all=True, duration=200, loop=0)
        print(f"Saved GIF animation to {gif_path}")

def main():
    parser = create_parser()
    args = parser.parse_args()
    
    data_folder = args.data_folder
    positions_csv = os.path.join(data_folder, args.positions_csv)
    speeds_csv = os.path.join(data_folder, args.speeds_csv)
    output_folder = args.output_folder
    
    # Check if input files exist
    if not os.path.exists(positions_csv):
        print(f"Error: Positions file not found: {positions_csv}")
        print(f"Please run the BioDynaMo simulation first to generate the data.")
        return
    
    if not os.path.exists(speeds_csv):
        print(f"Error: Speeds file not found: {speeds_csv}")
        print(f"Please run the BioDynaMo simulation first to generate the data.")
        return
    
    # Parse the CSV files
    print(f"Reading position data from {positions_csv}...")
    positions_df = parse_position_data(positions_csv)
    print(f"Found {len(positions_df)} time points")
    
    print(f"Reading speed data from {speeds_csv}...")
    speeds_df = parse_speed_data(speeds_csv)
    print(f"Found {len(speeds_df)} time points")
    
    # Generate plots
    print("Generating plots...")
    generate_plots(positions_df, speeds_df, output_folder)
    
    # Generate GIF
    print("Generating GIF animation...")
    generate_gif(positions_df, output_folder)
    
    print("Analysis complete!")


if __name__ == '__main__':
    main()