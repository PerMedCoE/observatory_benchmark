import numpy as np
import matplotlib.pyplot as plt
import os

"""A small 3-D explicit finite-difference diffusion toy
    (cleaned-up version of the code that was corrupted during PDF copy).

The script defines:
  • a constant boundary-condition helper
  • a simple explicit solver ``diffusion_3d``
then runs one call so that the module can be executed directly.

It is *not* optimised – it is meant as a readable reference.
"""

# ----------------------------------------------------------------------------
# Simulation parameters
# ----------------------------------------------------------------------------

x_domain = 240.0  # physical size along x (µm)
y_domain = 240.0  # y-extent
z_domain = 240.0  # z-extent
t_domain = 10.0   # total simulated time (min)

nx = ny = nz = 81         # number of nodes per direction
nu = 2000.0               # diffusion coefficient (µm²/min)
sigma = 0.9               # stability factor for explicit scheme

# Derived grid spacing

dx = x_domain / (nx - 1)
dy = y_domain / (ny - 1)
dz = z_domain / (nz - 1)

# ----------------------------------------------------------------------------
# Initial conditions
# ----------------------------------------------------------------------------

# Match ground-truth: start with 0 µM in the bulk; boundary will be reset to 10 µM each step
u0 = np.zeros((ny, nx, nz))

# ---------------------------------------------------------------------------
# Point sinks (cells consuming nutrient)
# ---------------------------------------------------------------------------
# Each selected voxel *removes* concentration at a constant rate in µM/min.
# To experiment, modify the two parameters below.

N_SINKS = 1000          # how many voxels act as sinks
SINK_RATE = -2000.0     # consumption rate per voxel (µM/min, **negative**)

np.random.seed(0)
P0 = np.zeros_like(u0)
# Pre-generate sink coordinates to allow picking a representative voxel later
sink_coords = np.random.randint(2, nx - 2, size=(N_SINKS, 3))
for iy, ix, iz in sink_coords:
    P0[iy, ix, iz] += SINK_RATE

# Select the first sink as the "single cell" we will track
single_voxel_coord = tuple(sink_coords[0])  # (iy, ix, iz)
print("Total sink strength (µM/min):", P0.sum())
print("Tracking single voxel at (y, x, z) =", single_voxel_coord)

# ----------------------------------------------------------------------------
# Boundary condition helper
# ----------------------------------------------------------------------------

def constant_bc(value: float = 10.0):
    """Return a closure that applies a constant Dirichlet BC."""

    def _bc(field: np.ndarray) -> np.ndarray:  # pylint: disable=unused-argument
        return value

    return _bc


# ----------------------------------------------------------------------------
# Diffusion solver (explicit FTCS scheme)
# ----------------------------------------------------------------------------

def diffusion_3d(
    u_init: np.ndarray,
    t_end: float,
    dx: float,
    dy: float,
    dz: float,
    nu: float,
    sigma: float,
    bc_func,
    source_rate: np.ndarray | None = None,
    sample_coords: tuple[int, int, int] | None = None,
):
    """Solve 3-D diffusion with constant Dirichlet boundaries.

    Additional Parameters
    ---------------------
    sample_coords : tuple[int, int, int] | None, optional
        If provided, record the concentration at this voxel each time-step
        and return the time series as an additional array.
    """

    # time-step from stability criterion (explicit scheme)
    dt = 0.5 * sigma / ((1.0 / dx ** 2) + (1.0 / dy ** 2) + (1.0 / dz ** 2)) / nu
    nt = int(np.ceil(t_end / dt))
    print(f"Δt = {dt:.5e} — total steps: {nt}")

    u = u_init.copy()

    coeff_x = nu * dt / dx ** 2
    coeff_y = nu * dt / dy ** 2
    coeff_z = nu * dt / dz ** 2

    mean_conc = np.empty(nt, dtype=float)
    std_conc = np.empty(nt, dtype=float)
    single_series = np.empty(nt, dtype=float) if sample_coords is not None else None

    iy_s, ix_s, iz_s = sample_coords if sample_coords is not None else (None, None, None)

    for step in range(nt):
        u_old = u.copy()

        # interior update (vectorised)
        lap = (
            u_old[1:-1, 1:-1, 1:-1]
            + coeff_x * (u_old[1:-1, 2:, 1:-1] - 2 * u_old[1:-1, 1:-1, 1:-1] + u_old[1:-1, :-2, 1:-1])
            + coeff_y * (u_old[2:, 1:-1, 1:-1] - 2 * u_old[1:-1, 1:-1, 1:-1] + u_old[:-2, 1:-1, 1:-1])
            + coeff_z * (u_old[1:-1, 1:-1, 2:] - 2 * u_old[1:-1, 1:-1, 1:-1] + u_old[1:-1, 1:-1, :-2])
        )

        if source_rate is not None:
            lap += dt * source_rate[1:-1, 1:-1, 1:-1]

        u[1:-1, 1:-1, 1:-1] = lap

        # apply constant Dirichlet BCs on all six faces
        bc_val = bc_func(u_old)
        u[0, :, :] = bc_val  # y = 0 (bottom)
        u[-1, :, :] = bc_val  # y = max (top)
        u[:, 0, :] = bc_val  # x = 0 (left)
        u[:, -1, :] = bc_val  # x = max (right)
        u[:, :, 0] = bc_val  # z = 0 (front)
        u[:, :, -1] = bc_val  # z = max (back)

        # record statistics
        mean_conc[step] = u.mean()
        std_conc[step] = u.std()
        if sample_coords is not None:
            single_series[step] = u[iy_s, ix_s, iz_s]

    return u, dt, nt, mean_conc, std_conc, single_series


# ----------------------------------------------------------------------------
# Run a quick test if executed as a script
# ----------------------------------------------------------------------------

if __name__ == "__main__":
    u_final, dt, nsteps, mean_ts, std_ts, single_ts = diffusion_3d(
        u0,
        t_end=t_domain,
        dx=dx,
        dy=dy,
        dz=dz,
        nu=nu,
        sigma=sigma,
        bc_func=constant_bc(10.0),
        source_rate=P0,
        sample_coords=single_voxel_coord,
    )

    print("Simulation finished — mean concentration:", u_final.mean())

    # -------------------------------------------------------------------
    # Plot average concentration vs. time
    # -------------------------------------------------------------------

    # For direct comparison with ground-truth snapshots we use the raw step index as the x-axis
    times = np.arange(nsteps)  # 0, 1, 2, ...

    plt.rcParams.update({
        "font.family": "sans-serif",
        "font.size": 8,
        "axes.labelsize": 9,
        "axes.titlesize": 9,
        "xtick.labelsize": 8,
        "ytick.labelsize": 8,
        "lines.linewidth": 1.8,
        "axes.linewidth": 0.8,
        "xtick.major.width": 0.8,
        "ytick.major.width": 0.8,
        "xtick.major.size": 3,
        "ytick.major.size": 3,
        "figure.dpi": 400,
    })

    fig, ax = plt.subplots(figsize=(4, 2.5))
    ax.plot(times, mean_ts, color="#666666", linewidth=1.8)
    ax.set_xlabel("Timestep")
    ax.set_ylabel("Concentration (µM)")
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)
    plt.tight_layout()

    # save outputs
    save_dir = "ResultAnalysis/plots/diffusion_cfd_plots"
    os.makedirs(save_dir, exist_ok=True)

    fname = os.path.join(save_dir, "average_concentration_timecourse")
    fig.savefig(f"{fname}.pdf", format="pdf", bbox_inches="tight", pad_inches=0.05)
    fig.savefig(f"{fname}.svg", format="svg", bbox_inches="tight", pad_inches=0.05)
    fig.savefig(f"{fname}.png", dpi=600, format="png", bbox_inches="tight", pad_inches=0.05)
    plt.close(fig)

    # Save CSV with mean and std
    csv_path = os.path.join(save_dir, "average_concentration_time_series.csv")
    import pandas as pd
    pd.DataFrame({"snap": times, "conc_mean": mean_ts, "conc_std": std_ts}).to_csv(
        csv_path, index=False
    )

    # -------------------------------------------------------------
    # Plot & save single-cell concentration time-course + CSV
    # -------------------------------------------------------------
    fig2, ax2 = plt.subplots(figsize=(4, 2.5))
    ax2.plot(times, single_ts, color="#1f77b4", linewidth=1.8)
    ax2.set_xlabel("Timestep")
    ax2.set_ylabel("Concentration (μM)")
    ax2.spines["top"].set_visible(False)
    ax2.spines["right"].set_visible(False)
    plt.tight_layout()

    fname2 = os.path.join(save_dir, "single_cell_concentration_timecourse")
    fig2.savefig(f"{fname2}.pdf", format="pdf", bbox_inches="tight", pad_inches=0.05)
    fig2.savefig(f"{fname2}.svg", format="svg", bbox_inches="tight", pad_inches=0.05)
    fig2.savefig(f"{fname2}.png", dpi=600, format="png", bbox_inches="tight", pad_inches=0.05)
    plt.close(fig2)

    # CSV for single cell
    csv_single = os.path.join(save_dir, "single_cell_concentration_time_series.csv")
    pd.DataFrame({"snap": times, "conc_single": single_ts}).to_csv(csv_single, index=False)

    # =============================================================
    # SECOND EXPERIMENT: single sink in the centre of the domain
    # =============================================================
    # Define sink field
    P_center = np.zeros_like(u0)
    center_coord = (ny // 2, nx // 2, nz // 2)
    P_center[center_coord] = SINK_RATE

    print("\n[INFO] Running single-centre-sink experiment …")

    (
        u_final2,
        dt2,
        nsteps2,
        mean_ts2,
        std_ts2,
        single_ts2,
    ) = diffusion_3d(
        u0,
        t_end=t_domain,
        dx=dx,
        dy=dy,
        dz=dz,
        nu=nu,
        sigma=sigma,
        bc_func=constant_bc(10.0),
        source_rate=P_center,
        sample_coords=center_coord,
    )

    print("Single-sink simulation finished — mean concentration:", u_final2.mean())

    times2 = np.arange(nsteps2)

    # Plot – global mean
    save_dir2 = "ResultAnalysis/plots/diffusion_cfd_single_sink_plots"
    os.makedirs(save_dir2, exist_ok=True)

    fig3, ax3 = plt.subplots(figsize=(4, 2.5))
    ax3.plot(times2, mean_ts2, color="#666666", linewidth=1.8)
    ax3.set_xlabel("Timestep")
    ax3.set_ylabel("Concentration (μM)")
    ax3.spines["top"].set_visible(False)
    ax3.spines["right"].set_visible(False)
    plt.tight_layout()

    fname3 = os.path.join(save_dir2, "average_concentration_timecourse")
    fig3.savefig(f"{fname3}.pdf", format="pdf", bbox_inches="tight", pad_inches=0.05)
    fig3.savefig(f"{fname3}.svg", format="svg", bbox_inches="tight", pad_inches=0.05)
    fig3.savefig(f"{fname3}.png", dpi=600, format="png", bbox_inches="tight", pad_inches=0.05)
    plt.close(fig3)

    # CSV for global mean
    csv2 = os.path.join(save_dir2, "average_concentration_time_series.csv")
    pd.DataFrame({"snap": times2, "conc_mean": mean_ts2, "conc_std": std_ts2}).to_csv(csv2, index=False)

    # Plot – centre voxel concentration
    fig4, ax4 = plt.subplots(figsize=(4, 2.5))
    ax4.plot(times2, single_ts2, color="#1f77b4", linewidth=1.8)
    ax4.set_xlabel("Timestep")
    ax4.set_ylabel("Concentration (μM)")
    ax4.spines["top"].set_visible(False)
    ax4.spines["right"].set_visible(False)
    plt.tight_layout()

    fname4 = os.path.join(save_dir2, "single_cell_concentration_timecourse")
    fig4.savefig(f"{fname4}.pdf", format="pdf", bbox_inches="tight", pad_inches=0.05)
    fig4.savefig(f"{fname4}.svg", format="svg", bbox_inches="tight", pad_inches=0.05)
    fig4.savefig(f"{fname4}.png", dpi=600, format="png", bbox_inches="tight", pad_inches=0.05)
    plt.close(fig4)

    # CSV for centre voxel
    csv_single2 = os.path.join(save_dir2, "single_cell_concentration_time_series.csv")
    pd.DataFrame({"snap": times2, "conc_single": single_ts2}).to_csv(csv_single2, index=False)





