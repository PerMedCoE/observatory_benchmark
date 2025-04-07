import numpy as np
import pandas as pd

# Define parameters
domain_min, domain_max = -120, 120
dx = 10  # voxel size in microns
voxel_half = dx / 2  # center offset

# Create the grid of points within the domain
x_vals = np.arange(domain_min + voxel_half, domain_max, dx)
y_vals = np.arange(domain_min + voxel_half, domain_max, dx)
z_vals = np.arange(domain_min + voxel_half, domain_max, dx)

# Generate voxel centers
grid_points = np.array(np.meshgrid(x_vals, y_vals, z_vals)).T.reshape(-1, 3)
print(grid_points)

# Check for uniqueness in grid_points
assert len(grid_points) == len(np.unique(grid_points, axis=0)), "Duplicate points found in grid_points"

# Filter out wall voxels to retain only internal voxels
internal_voxels = []
for x, y, z in grid_points:
    if (domain_min + dx <= x <= domain_max - dx) and \
       (domain_min + dx <= y <= domain_max - dx) and \
       (domain_min + dx <= z <= domain_max - dx):
        internal_voxels.append([x, y, z])

# Check for uniqueness in internal_voxels
internal_voxels = np.array(internal_voxels)
assert len(internal_voxels) == len(np.unique(internal_voxels, axis=0)), "Duplicate points found in internal_voxels"

# Select the first 1000 internal voxels for cell placement
# if len(internal_voxels) > 1000:
#     print(len(internal_voxels))
#     cell_positions = internal_voxels[:1000]
# else:
#     cell_positions = internal_voxels


# Prepare the data with typeID set to 0
cell_data = pd.DataFrame(internal_voxels, columns=['x', 'y', 'z'])
cell_data['typeID'] = 0

# Write the data to CSV with the required header
with open('cells_1000_10.csv', 'w') as f:
    cell_data.to_csv(f, index=False, header=False)
