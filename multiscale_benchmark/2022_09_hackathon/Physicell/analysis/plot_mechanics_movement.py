import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation

# Load data into a pandas dataframe

data = pd.read_csv("/home/thalia/BSC/NEW_BENCH/Physicell_template/mechanics_movement/position_step.csv",index_col=0).sort_values(by=['dt']).reset_index(drop=True)
data_biod = pd.read_csv("/home/thalia/BSC/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_friction_single/results/positions.csv"
,header = None,sep='\t|,',engine='python')
data_biod = data_biod.rename(columns={1: "x", 2: "y", 3: "z"})
fig = plt.figure()
ax = fig.add_subplot(111)
ax.set_xlim([-21.0, 21.0])
ax.set_ylim([-1.0, 1.0])
ax.set_xlabel('X')
ax.set_ylabel('Y')
print(data)
print(data_biod)
# exit()
# Define a function that will update the plot for each frame of the animation
def update(frame):
    ax.clear()
    ax.set_xlim([-15.0, 15.0])
    ax.set_ylim([-15.0, 15.0])
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.scatter(data.iloc[frame]['x'], data.iloc[frame]['y'], c='b', marker='o')
    return ax
def update(frame, sphere_df, cube_df):
    ax.clear()
    ax.set_xlim([-15.0, 15.0])
    ax.set_ylim([-15.0, 15.00])
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.scatter(sphere_df.iloc[frame]['x'], sphere_df.iloc[frame]['y'], c='b', marker='o',label="Physicell")
    ax.scatter(cube_df.iloc[frame]['x'], cube_df.iloc[frame]['y'], c='r', marker='s',label="BioDynamo")
    ax.legend()
    return ax

# Create the animation
# anim = FuncAnimation(fig, update, frames=len(data), interval=10)

# Save the animation as a GIF
# anim.save('sphere_positions.gif', writer='imagemagick')\


anim = FuncAnimation(fig, update, frames=len(data_biod), fargs=(data, data_biod), interval=50)
anim.save('mechanics_movement.gif', writer='Pillow')
