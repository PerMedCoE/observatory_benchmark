# this is meant for unit test 2 to plot the diffusion of each voxel
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
# select a pallet of colors to display the different diffusion in each substrate and then make a gif of the different timepoints

# Load data into a pandas dataframe
output_folder= "/home/thalia/BSC/NEW_BENCH/Physicell_template/out_single_diffusion/"
pc_me = pd.read_csv(output_folder+"coordinates_diffusion.csv",index_col=0)

grouped = pc_me.groupby(by="timestep")
# Create a 3D scatter plot
for t,timestep in grouped:
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Add voxels to the plot
    ax.scatter(timestep['x'], timestep['y'], timestep['z'], c=timestep['diff'], cmap='jet')

    # Set the axis labels
    ax.set_xlabel('x')
    ax.set_ylabel('y')

    # Show the plot
    # plt.show()
    plt.title(t)
    num_ite = t*100
    plt.savefig(output_folder+"/diff_timepoint"+str(int(num_ite))+".png")
    plt.close()
    