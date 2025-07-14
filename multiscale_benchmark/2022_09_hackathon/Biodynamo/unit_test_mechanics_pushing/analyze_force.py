import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

def calculate_force(delta, k, gamma, r):
    """
    Calculates the interaction force based on the formula from cell_cell_force.cc
    f = k * delta - gamma * sqrt(r * delta)
    """
    # Use np.where to handle array and scalar inputs correctly.
    # It applies the calculation only where delta >= 0, and returns 0 otherwise.
    delta = np.asanyarray(delta)
    # Ensure sqrt is only taken for non-negative values to avoid warnings/errors.
    sqrt_term = np.sqrt(np.maximum(0, r * delta))
    force = np.where(delta >= 0, k * delta - gamma * sqrt_term, 0)
    return force

def plot_force_vs_overlap():
    """
    Generates a plot of force vs. overlap for fixed k and gamma values.
    """
    # Fixed parameters from sim_param.h
    k = 2e-10  # repulsion_coeff in N/m
    gamma = 1e-10  # attraction_coeff in N/m

    # Delta values from 0 to 15 um
    delta_um = np.linspace(0, 15, 100)
    delta_m = delta_um * 1e-6  # convert um to m

    plt.figure(figsize=(10, 6))

    radius_multipliers = [1.00, 1.03]
    for multiplier in radius_multipliers:
        # Parameters from the simulation
        diameter_um = 10.0  # um
        diameter_m = diameter_um * 1e-6 # convert um to m
        
        # Virtual radius
        r_virt_m = 0.5 * diameter_m * multiplier
        
        # Effective radius 'r' for the force calculation
        # r = (r1 * r2) / (r1 + r2) with r1=r2=r_virt
        r1 = r_virt_m
        r2 = r1
        r = (r1 * r2) / (r1 + r2)

        # Calculate force in Newtons
        force_N = calculate_force(delta_m, k, gamma, r)
        
        plt.plot(delta_um, force_N, label=f'Radius Multiplier = {multiplier}')

    plt.xlabel('Overlap (delta) [µm]')
    plt.ylabel('Force [N]')
    title_text = f'Force vs. Overlap\n(k = {k:.1e} N/m, γ = {gamma:.1e} N/m)'
    plt.title(title_text)
    plt.legend()
    plt.grid(True)
    
    # Save the figure
    plt.savefig('force_vs_overlap.png')
    plt.close()
    
    print("\nForce vs. overlap plot has been generated and saved as force_vs_overlap.png.")

def generate_combined_heatmap(radius_multiplier):
    """
    Generates and saves a single plot with subplots for different delta values
    for a given radius_multiplier.
    The color scale is normalized across all subplots.
    """
    # Parameters from the simulation
    diameter = 10.0  # um
    
    # Virtual radius
    r_virt = 0.5 * diameter * radius_multiplier
    
    # Effective radius 'r' for the force calculation
    # r = (r1 * r2) / (r1 + r2) with r1=r2=r_virt
    r1 = r_virt
    r2 = r1
    r = (r1 * r2) / (r1 + r2)

    # Delta values to investigate
    delta_values = np.arange(0, 15.1, 1.0)

    # Define ranges for k and gamma
    k_values = np.linspace(0, 0.00000001, 100)
    gamma_values = np.linspace(0, 0.00000001, 100)
    K, G = np.meshgrid(k_values, gamma_values)

    # Calculate all force matrices to find global min and max for normalization
    force_matrices = [calculate_force(delta, K, G, r) for delta in delta_values]
    
    # Handle case where all forces might be zero or constant
    all_mins = [F.min() for F in force_matrices]
    all_maxs = [F.max() for F in force_matrices]
    global_min = min(all_mins)
    global_max = max(all_maxs)
    
    if global_min == global_max:
        global_min -= 1
        global_max += 1

    # Setup the plot grid
    n_plots = len(delta_values)
    n_cols = 4
    n_rows = int(np.ceil(n_plots / n_cols))
    
    fig, axes = plt.subplots(n_rows, n_cols, figsize=(n_cols * 5, n_rows * 4), constrained_layout=True)
    axes = axes.flatten() # Flatten the 2D array of axes to easily iterate

    print(f"Generating combined force heatmap plot for radius_multiplier = {radius_multiplier}...")

    for i, delta in enumerate(delta_values):
        ax = axes[i]
        F = force_matrices[i]
        
        im = ax.imshow(F, origin='lower', extent=[gamma_values.min(), gamma_values.max(), k_values.min(), k_values.max()], 
                       aspect='auto', cmap='viridis', vmin=global_min, vmax=global_max)
        
        ax.set_xlabel('Attraction coefficient (gamma)')
        ax.set_ylabel('Repulsion coefficient (k)')
        ax.set_title(f'delta = {delta:.2f} um')

    # Hide any unused subplots
    for i in range(n_plots, len(axes)):
        axes[i].set_visible(False)

    # Add a single colorbar for the entire figure
    fig.colorbar(im, ax=axes.tolist(), label='Force (f)', orientation='vertical', shrink=0.8)
    
    fig.suptitle(f'Force Heatmaps for Varying Overlap (delta)\nRadius Multiplier = {radius_multiplier}', fontsize=16)
    
    # Save the figure
    plt.savefig(f'force_heatmaps_multiplier_{radius_multiplier:.2f}.png')
    plt.close()
    
    print(f"\nCombined plot has been generated and saved as force_heatmaps_multiplier_{radius_multiplier:.2f}.png.")

def main():
    """
    Main function to run the analysis for different radius multipliers.
    """
    # Generate the force vs overlap plot
    plot_force_vs_overlap()

    # Generate the heatmaps
    radius_multipliers = [1.03, 1.00]
    for multiplier in radius_multipliers:
        generate_combined_heatmap(multiplier)

if __name__ == '__main__':
    main()
