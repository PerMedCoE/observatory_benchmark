import numpy as np
import csv

def generate_internal_centers(dx):
    """
    Generates the centers of internal voxels in a cubic domain from -120 to 120 in x, y, z.
    Ensures only internal voxels are selected.
    """
    # Define the valid range for internal voxel centers
    valid_range = np.arange(-120 + dx/2, 120, dx)[1:-1]  # Remove boundary voxels
    
    # Generate the 1000 internal voxel centers
    centers = np.array(np.meshgrid(valid_range, valid_range, valid_range)).T.reshape(-1, 3)
    
    # Add an extra column of zeros
    extra_column = np.zeros((centers.shape[0], 1),dtype=int)
    return np.hstack((centers, extra_column))

def subdivide_centers(centers, dx):
    """Subdivides each voxel center into smaller voxels based on new dx."""
    factor = int(20 / dx)  # How many subdivisions per dimension
    step = dx * (np.arange(factor) - (factor-1)/2)  # Center offsets for subdivision

    # Generate offsets in all 3 dimensions
    offsets = np.array(np.meshgrid(step, step, step)).T.reshape(-1, 3)
    
    # Apply offsets to original voxel centers
    new_centers = np.vstack([centers[:, :3] + offset for offset in offsets])
    extra_column = np.zeros((len(new_centers), 1),dtype=int)
    return np.hstack((new_centers, extra_column))

def save_to_csv(filename, centers):
    """Saves centers to a CSV file."""
    with open(filename, "w", newline="") as f:
        writer = csv.writer(f)
        # writer.writerow(["x", "y", "z", "extra"])
        writer.writerows(centers)

# Generate and save voxel centers for dx = 20 µm (exact 1000 internal voxels)
centers_20um = generate_internal_centers(20)
save_to_csv("code/config/centers_20um.csv", centers_20um)

# Generate and save voxel centers for dx = 10 µm (subdivided from 20 µm centers)
centers_10um = subdivide_centers(centers_20um, 10)
save_to_csv("code/config/centers_10um.csv", centers_10um)

centers_5um = subdivide_centers(centers_20um, 5)
save_to_csv("code/config/centers_5um.csv", centers_5um)

centers_2um = subdivide_centers(centers_20um, 2)
save_to_csv("code/config/centers_2um.csv", centers_2um)
