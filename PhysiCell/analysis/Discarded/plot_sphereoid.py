import os
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from mpl_toolkits.mplot3d import Axes3D
from scipy.io import loadmat
from natsort import natsorted

# Simulation parameters
output_dir = "/home/tntiniak/Work/physicellforbenchmarknewintegrationwithrandy/PhysiCell/spheriod/"
output_dir = "/home/tntiniak/Work/physicellforbenchmarknewintegrationwithrandy/PhysiCell/output_monolayer/"

mechanical_dt = 0.1  # Minutes between time steps

# Gather and sort .mat files
files = [f for f in os.listdir(output_dir) if f.endswith("_cells.mat")]
files = natsorted([os.path.join(output_dir, f) for f in files])
print(f"Found {len(files)} files.")
# Prepare figure
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
scatter = ax.scatter([], [], [], s=10, c='blue', alpha=0.6)

# Set axes limits (adjust according to your simulation domain)
ax.set_xlim([-150, 150])
ax.set_ylim([-150, 150])
ax.set_zlim([-150, 150])
ax.set_xlabel("X (µm)")
ax.set_ylabel("Y (µm)")
ax.set_zlabel("Z (µm)")
title = ax.set_title("")

# Update function for animation
def update(frame):
    mat = loadmat(files[frame])
    cell_data = mat['cells'][[0,1,2,3]]
    df = pd.DataFrame(cell_data.transpose(), columns=[
        'id','x','y','z'
    ])
    
    scatter._offsets3d = (df['x'], df['y'], df['z'])
    title.set_text(f"Time: {frame * mechanical_dt:.2f} min")

    return scatter,

# scatter._offsets3d = (df['x'], df['y'], df['z'])
# title.set_text(f"Time: {frame * mechanical_dt:.2f} min")
# Create animation
# ani = FuncAnimation(fig, update, frames=len(files), interval=200, blit=False)\
# Load last file
last_file = files[-1]
mat = loadmat(last_file)
cell_data = mat['cells'][[0,1,2,3,17,50,52,57,58,59,51]]
df = pd.DataFrame(cell_data.transpose(), columns=[
    'id','x','y','z','velocity','is_motile','migration_speed',
    'mvx','mvy','mvz','persistence_time'
])

# Plotting
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.scatter(df['x'], df['y'], df['z'], s=10, c='blue', alpha=0.6)

ax.set_xlim([-150, 150])
ax.set_ylim([-150, 150])
# ax.set_zlim([-150, 150])
ax.set_xlabel("X (µm)")
ax.set_ylabel("Y (µm)")
# ax.set_zlabel("Z (µm)")
ax.set_title(f"Last Frame: {len(files)-1}  |  Time: {(len(files)-1) * mechanical_dt:.2f} min")

plt.tight_layout()
plt.show()
file = files[-1]
print(file)
mat = loadmat(file)
cell_data = mat['cells'][[0,1,2,3]]
df = pd.DataFrame(cell_data.transpose(), columns=[
    'id','x','y','z'
])
print(df)
df.to_csv(output_dir+"spheriod.csv", index=False)
plt.show()
