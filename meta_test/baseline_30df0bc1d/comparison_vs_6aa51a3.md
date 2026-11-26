# Table 1 regression: `/tmp/run` against `meta_test/baseline_6aa51a3`

Relative tolerance 1e-06. A moved value means that the manuscript text, Table 1 or a figure quoting it must be checked before the new value is accepted.

## Summary

| Output table | Values moved | Rows added or removed | Input files changed | Used in |
|---|---|---|---|---|
| diffusion_decay_finest.csv | 0 | 0 | 2 | Table 1 (decay row), Results, Figure 2 |
| diffusion_uptake_finest.csv | 0 | 0 | 2 | Table 1 (point-sink row), Results, Figure 2 |
| diffusion_decay_all_runs.csv | 0 | 0 | 8 | Supplementary Table S3a (all resolutions) |
| diffusion_uptake_all_runs.csv | 0 | 0 | 8 | Supplementary Table S3a (all resolutions) |
| mechanics_external_impulse.csv | 8 | 0 | 3 | Table 1 (impulse row), Results, Figure 3C, D |
| mechanics_common_extended_hertz.csv | 66 | 0 | 4 | Table 1 (common law row), Results, Figure 3E, Supplementary Table S3b |
| mechanics_builtin_pushing.csv | 16 | 0 | 2 | Table 1 (built-in models row), Results, Figure 3F |
| cell_cycle.csv | 0 | 0 | 7 | Table 1 (cell-cycle row), Results, Figure 4B |
| monolayer.csv | 13 | 3 | 2 | Table 1 (monolayer row), Results, Figure 5 |

## diffusion_decay_finest.csv

Used in: Table 1 (decay row), Results, Figure 2.

Input file changed: Chaste N=48 dx=5: `Chaste/DiffusionNoCells/48.dat` to `Chaste/DiffusionNoCells/results/48.dat`; CompuTiX N=63 dx=3.81 dt=0.006s: `CompuTiX/diffusion_single/Decay/dt-s-0-006_N-63.yaml` to `CompuTiX/diffusion_single/Decay/results/dt-s-0-006_N-63.yaml`.

## diffusion_uptake_finest.csv

Used in: Table 1 (point-sink row), Results, Figure 2.

Input file changed: Chaste N=48 dx=5: `Chaste/DiffusionWithCells/48.txt` to `Chaste/DiffusionWithCells/results/48.txt`; CompuTiX N=63 dx=3.81 dt=0.006s: `CompuTiX/diffusion_single/CellsAtCenter/dt-s-0-006_N-63.yaml` to `CompuTiX/diffusion_single/CellsAtCenter/results/dt-s-0-006_N-63.yaml`.

## diffusion_decay_all_runs.csv

Used in: Supplementary Table S3a (all resolutions).

Input file changed: Chaste N=12 dx=20: `Chaste/DiffusionNoCells/12.dat` to `Chaste/DiffusionNoCells/results/12.dat`; Chaste N=24 dx=10: `Chaste/DiffusionNoCells/24.dat` to `Chaste/DiffusionNoCells/results/24.dat`; Chaste N=48 dx=5: `Chaste/DiffusionNoCells/48.dat` to `Chaste/DiffusionNoCells/results/48.dat`; Chaste N=6 dx=40: `Chaste/DiffusionNoCells/6.dat` to `Chaste/DiffusionNoCells/results/6.dat`; CompuTiX N=15 dx=16.00 dt=0.006s: `CompuTiX/diffusion_single/Decay/dt-s-0-006_N-15.yaml` to `CompuTiX/diffusion_single/Decay/results/dt-s-0-006_N-15.yaml`; CompuTiX N=31 dx=7.74 dt=0.006s: `CompuTiX/diffusion_single/Decay/dt-s-0-006_N-31.yaml` to `CompuTiX/diffusion_single/Decay/results/dt-s-0-006_N-31.yaml`; CompuTiX N=63 dx=3.81 dt=0.006s: `CompuTiX/diffusion_single/Decay/dt-s-0-006_N-63.yaml` to `CompuTiX/diffusion_single/Decay/results/dt-s-0-006_N-63.yaml`; CompuTiX N=7 dx=34.29 dt=0.006s: `CompuTiX/diffusion_single/Decay/dt-s-0-006_N-7.yaml` to `CompuTiX/diffusion_single/Decay/results/dt-s-0-006_N-7.yaml`.

## diffusion_uptake_all_runs.csv

Used in: Supplementary Table S3a (all resolutions).

Input file changed: Chaste N=12 dx=20: `Chaste/DiffusionWithCells/12.txt` to `Chaste/DiffusionWithCells/results/12.txt`; Chaste N=24 dx=10: `Chaste/DiffusionWithCells/24.txt` to `Chaste/DiffusionWithCells/results/24.txt`; Chaste N=48 dx=5: `Chaste/DiffusionWithCells/48.txt` to `Chaste/DiffusionWithCells/results/48.txt`; Chaste N=6 dx=40: `Chaste/DiffusionWithCells/6.txt` to `Chaste/DiffusionWithCells/results/6.txt`; CompuTiX N=15 dx=16.00 dt=0.006s: `CompuTiX/diffusion_single/CellsAtCenter/dt-s-0-006_N-15.yaml` to `CompuTiX/diffusion_single/CellsAtCenter/results/dt-s-0-006_N-15.yaml`; CompuTiX N=31 dx=7.74 dt=0.006s: `CompuTiX/diffusion_single/CellsAtCenter/dt-s-0-006_N-31.yaml` to `CompuTiX/diffusion_single/CellsAtCenter/results/dt-s-0-006_N-31.yaml`; CompuTiX N=63 dx=3.81 dt=0.006s: `CompuTiX/diffusion_single/CellsAtCenter/dt-s-0-006_N-63.yaml` to `CompuTiX/diffusion_single/CellsAtCenter/results/dt-s-0-006_N-63.yaml`; CompuTiX N=7 dx=34.29 dt=0.006s: `CompuTiX/diffusion_single/CellsAtCenter/dt-s-0-006_N-7.yaml` to `CompuTiX/diffusion_single/CellsAtCenter/results/dt-s-0-006_N-7.yaml`.

## mechanics_external_impulse.csv

Used in: Table 1 (impulse row), Results, Figure 3C, D.

Input file changed: CompuTiX: `CompuTiX/external_impulse/impulse_benchmark.yaml` to `CompuTiX/external_impulse/results/external_impulse.yaml`; PhysiCell: `PhysiCell/results/mechanics_external_impulse/dt_0.001/physicell_mechanics_external_impulse_data.csv` to `PhysiCell/results/mechanics_external_impulse/physicell_mechanics_external_impulse_data.csv`; Chaste: `Chaste/MechanicsWithFriction/node_locations.dat; Chaste/MechanicsWithFriction/cell_velocities.dat` to `Chaste/MechanicsWithFriction/results/node_locations.dat`.

| Row | Quantity | Baseline | New | Change (%) |
|---|---|---|---|---|
| PhysiCell | active_from_s | 3.06 | 3 | -1.96 |
| PhysiCell | active_to_s | 6 | 5.94 | -1 |
| TiSim | unit_note | no units in file; velocity read as um/s, position multiplied by 0.01 (as in the notebook) | units in header (s, um, um/s) |  |
| Chaste | unit_note | units not stated: position rises to 8.33333 units, velocity column 4 plateau 0.277778 units; excluded from the error comparison | um and s; velocity from positions |  |
| Chaste | plateau_um_per_s | n/a | 0.000166667 |  |
| Chaste | displacement_um | n/a | 0.0005 |  |
| Chaste | plateau_rel_error_pct | n/a | 3.99908e-11 |  |
| Chaste | displacement_rel_error_pct | n/a | 1.99927e-11 |  |

## mechanics_common_extended_hertz.csv

Used in: Table 1 (common law row), Results, Figure 3E, Supplementary Table S3b.

Input file changed: 0.01 / CompuTiX: `CompuTiX/overlap_relaxation/results_mu_0.01.yaml` to `CompuTiX/overlap_relaxation/results/overlap_relaxation_mu_0.01.yaml`; 0.1 / CompuTiX: `CompuTiX/overlap_relaxation/results_mu_0.1.yaml` to `CompuTiX/overlap_relaxation/results/overlap_relaxation_mu_0.1.yaml`; 1 / CompuTiX: `CompuTiX/overlap_relaxation/results_mu_1.yaml` to `CompuTiX/overlap_relaxation/results/overlap_relaxation_mu_1.yaml`; 1 / Chaste: `Chaste/HertzCellRelaxation/node_locations.dat` to `Chaste/HertzCellRelaxation/results/node_locations.dat`.

| Row | Quantity | Baseline | New | Change (%) |
|---|---|---|---|---|
| 0.01 / BioDynaMo | t_half_overlap_s | 120 | 56.3309 | -53.1 |
| 0.01 / BioDynaMo | ode_t_half_overlap_s | 7.73935 | 7.33521 | -5.22 |
| 0.01 / BioDynaMo | t_overlap_below_0p1um_s | 120 | 112.823 | -5.98 |
| 0.01 / BioDynaMo | ode_t_overlap_below_0p1um_s | 38.579 | 38.2912 | -0.746 |
| 0.01 / BioDynaMo | mean_abs_dev_from_ode_um | 0.000711382 | 0.00029138 | -59 |
| 0.01 / BioDynaMo | mean_abs_dev_from_notebook_curve_um | 0.00279351 | 0.00326064 | +16.7 |
| 0.01 / CompuTiX | t_half_overlap_s | 10 | 5.12263 | -48.8 |
| 0.01 / CompuTiX | ode_t_half_overlap_s | 7.73935 | 7.33521 | -5.22 |
| 0.01 / CompuTiX | t_overlap_below_0p1um_s | 10 | 9.22073 | -7.79 |
| 0.01 / CompuTiX | ode_t_overlap_below_0p1um_s | 38.579 | 38.2912 | -0.746 |
| 0.01 / PhysiCell | t_half_overlap_s | 6 | 2.95147 | -50.8 |
| 0.01 / PhysiCell | ode_t_half_overlap_s | 7.73935 | 7.33521 | -5.22 |
| 0.01 / PhysiCell | t_overlap_below_0p1um_s | 6 | 5.31261 | -11.5 |
| 0.01 / PhysiCell | ode_t_overlap_below_0p1um_s | 38.579 | 38.2912 | -0.746 |
| 0.01 / PhysiCell | mean_abs_dev_from_ode_um | 0.000493975 | 0.00049396 | -0.00299 |
| 0.01 / PhysiCell | mean_abs_dev_from_notebook_curve_um | 0.00607792 | 0.00607796 | +0.000646 |
| 0.01 / TiSim | t_half_overlap_s | 24 | 21.8992 | -8.75 |
| 0.01 / TiSim | ode_t_half_overlap_s | 7.73935 | 7.33521 | -5.22 |
| 0.01 / TiSim | t_overlap_below_0p1um_s | 117 | 116.02 | -0.838 |
| 0.01 / TiSim | ode_t_overlap_below_0p1um_s | 38.579 | 38.2912 | -0.746 |
| 0.1 / BioDynaMo | overlap_end_um | 0.00047 | 0.00026 | -44.7 |
| 0.1 / BioDynaMo | distance_end_um | 9.99953 | 9.99974 | +0.0021 |
| 0.1 / BioDynaMo | t_half_overlap_s | 180 | 135.643 | -24.6 |
| 0.1 / BioDynaMo | ode_t_half_overlap_s | 78.3318 | 73.3521 | -6.36 |
| 0.1 / BioDynaMo | t_overlap_below_0p1um_s | 600 | 443.265 | -26.1 |
| 0.1 / BioDynaMo | ode_t_overlap_below_0p1um_s | 388.222 | 382.912 | -1.37 |
| 0.1 / BioDynaMo | mean_abs_dev_from_ode_um | 0.00814995 | 0.0029823 | -63.4 |
| 0.1 / BioDynaMo | mean_abs_dev_from_notebook_curve_um | 0.0418817 | 0.0470504 | +12.3 |
| 0.1 / CompuTiX | t_half_overlap_s | 60 | 44.967 | -25.1 |
| 0.1 / CompuTiX | ode_t_half_overlap_s | 78.3318 | 73.3521 | -6.36 |
| 0.1 / CompuTiX | t_overlap_below_0p1um_s | 300 | 254.177 | -15.3 |
| 0.1 / CompuTiX | ode_t_overlap_below_0p1um_s | 388.222 | 382.912 | -1.37 |
| 0.1 / PhysiCell | t_half_overlap_s | 72 | 70.1395 | -2.58 |
| 0.1 / PhysiCell | ode_t_half_overlap_s | 78.3318 | 73.3521 | -6.36 |
| 0.1 / PhysiCell | t_overlap_below_0p1um_s | 384 | 380.093 | -1.02 |
| 0.1 / PhysiCell | ode_t_overlap_below_0p1um_s | 388.222 | 382.912 | -1.37 |
| 0.1 / PhysiCell | mean_abs_dev_from_ode_um | 0.000281683 | 0.000281688 | +0.0019 |
| 0.1 / TiSim | t_half_overlap_s | 228 | 225.614 | -1.05 |
| 0.1 / TiSim | ode_t_half_overlap_s | 78.3318 | 73.3521 | -6.36 |
| 0.1 / TiSim | t_overlap_below_0p1um_s | 1191 | 1190.29 | -0.0593 |
| 0.1 / TiSim | ode_t_overlap_below_0p1um_s | 388.222 | 382.912 | -1.37 |
| 1 / BioDynaMo | overlap_end_um | 0.03247 | 0.02002 | -38.3 |
| 1 / BioDynaMo | distance_end_um | 9.96753 | 9.97998 | +0.125 |
| 1 / BioDynaMo | t_half_overlap_s | 1080 | 792.629 | -26.6 |
| 1 / BioDynaMo | ode_t_half_overlap_s | 740.774 | 733.521 | -0.979 |
| 1 / BioDynaMo | t_overlap_below_0p1um_s | 5220 | 3887.5 | -25.5 |
| 1 / BioDynaMo | ode_t_overlap_below_0p1um_s | 3836.77 | 3829.12 | -0.199 |
| 1 / BioDynaMo | mean_abs_dev_from_ode_um | 0.0432226 | 0.00494108 | -88.6 |
| 1 / BioDynaMo | mean_abs_dev_from_notebook_curve_um | 0.237558 | 0.275839 | +16.1 |
| 1 / CompuTiX | t_half_overlap_s | 720 | 702.999 | -2.36 |
| 1 / CompuTiX | ode_t_half_overlap_s | 740.774 | 733.521 | -0.979 |
| 1 / CompuTiX | t_overlap_below_0p1um_s | 3780 | 3726.1 | -1.43 |
| 1 / CompuTiX | ode_t_overlap_below_0p1um_s | 3836.77 | 3829.12 | -0.199 |
| 1 / PhysiCell | t_half_overlap_s | 732 | 730.507 | -0.204 |
| 1 / PhysiCell | ode_t_half_overlap_s | 740.774 | 733.521 | -0.979 |
| 1 / PhysiCell | t_overlap_below_0p1um_s | 3828 | 3826.15 | -0.0484 |
| 1 / PhysiCell | ode_t_overlap_below_0p1um_s | 3836.77 | 3829.12 | -0.199 |
| 1 / PhysiCell | mean_abs_dev_from_ode_um | 0.000272011 | 0.000272012 | +0.00028 |
| 1 / TiSim | t_half_overlap_s | 2265 | 2263 | -0.0883 |
| 1 / TiSim | ode_t_half_overlap_s | 740.774 | 733.521 | -0.979 |
| 1 / TiSim | t_overlap_below_0p1um_s | 11934 | 11933 | -0.00838 |
| 1 / TiSim | ode_t_overlap_below_0p1um_s | 3836.77 | 3829.12 | -0.199 |
| 1 / Chaste | t_half_overlap_s | 900 | 730.584 | -18.8 |
| 1 / Chaste | ode_t_half_overlap_s | 740.774 | 733.521 | -0.979 |
| 1 / Chaste | t_overlap_below_0p1um_s | 3900 | 3780.86 | -3.05 |
| 1 / Chaste | ode_t_overlap_below_0p1um_s | 3836.77 | 3829.12 | -0.199 |

## mechanics_builtin_pushing.csv

Used in: Table 1 (built-in models row), Results, Figure 3F.

Input file changed: CompuTiX: `CompuTiX/mechanics_pushing/benchmark_exmaple_2.yaml` to `CompuTiX/mechanics_pushing/results/mechanics_pushing.yaml`; PhysiCell: `PhysiCell/results/mechanics_pushing/ (snapshots only)` to `PhysiCell/results/mechanics_pushing/physicell_mechanics_pushing.csv`.

| Row | Quantity | Baseline | New | Change (%) |
|---|---|---|---|---|
| BioDynaMo | length_unit_note | um | um; archived run starts at 28 um (question 8.6) |  |
| BioDynaMo | start_distance_um | 30 | 28 | -6.67 |
| BioDynaMo | min_distance_um | 8 | 8.39496 | +4.94 |
| Chaste | length_unit_note | dimensionless; multiplied by 10 as in olderplotscripts/plot_mechanics_pushing.py | 10 um per length unit, time in h (assumed; question 8.12) |  |
| Chaste | t_min | 0.0176667 time units | 1.06 min |  |
| Chaste | t_final | 0.0833333 time units (5 min if hours) | 5 min |  |
| CompuTiX | min_distance_um | 7.9219 | 7.922 | +0.00124 |
| CompuTiX | final_distance_um | 9.09537 | 9.0954 | +0.000341 |
| CompuTiX | residual_overlap_um | 0.904631 | 0.9046 | -0.00342 |
| PhysiCell | length_unit_note | not computable: no derived CSV and the .mat payload is gitignored | um, min; motility off once centres < 10 um |  |
| PhysiCell | start_distance_um | 9 | 30 | +233 |
| PhysiCell | min_distance_um | n/a | 8.99827 |  |
| PhysiCell | t_min | n/a | 1 min |  |
| PhysiCell | final_distance_um | n/a | 9.73733 |  |
| PhysiCell | t_final | n/a | 10 min |  |
| PhysiCell | residual_overlap_um | n/a | 0.262673 |  |

## cell_cycle.csv

Used in: Table 1 (cell-cycle row), Results, Figure 4B.

Input file changed: BioDynaMo: `Biodynamo/fixed_cell_cycle/new_results/cell-0-sim1.csv` to `./Biodynamo/fixed_cell_cycle/results/cell-0.csv`; Chaste: `Chaste/fixed_cell_cycle/results/cellcycle_fixed.dat` to `./Chaste/FixedCellCycle/results/cellcycle_fixed.dat`; CompuTiX: `CompuTiX/fixed_cell_cycle/results/cell_volume.yaml` to `./CompuTiX/fixed_cell_cycle/results/cell_volume.yaml`; CompuTiX (volume_per_child_cell): `CompuTiX/fixed_cell_cycle/results/cell_volume.yaml` to `./CompuTiX/fixed_cell_cycle/results/cell_volume.yaml`; PhysiCell: `PhysiCell/results/cell_cycle_fixed/cell_volumes.csv` to `./PhysiCell/results/cell_cycle_fixed/cell_volumes.csv`; TiSim (file used in Figure 4B): `Tisim/fixed_cell_cycle/cell cycle fix.csv` to `./Tisim/fixed_cell_cycle/cell cycle fix.csv`; Reference data: `experimental_data/Cell cycle volume dynamics.txt` to `./ResultAnalysis/analytical_solutions/experimental_data/Cell cycle volume dynamics.txt`.

## monolayer.csv

Used in: Table 1 (monolayer row), Results, Figure 5.

Rows no longer produced: BioDynaMo (env_dims, the series plotted by plot_monolayer.py); BioDynaMo (tumor_diameter, cell-centre extent).

New rows: BioDynaMo.

Input file changed: Chaste: `Chaste/monolayer/results/monolayer.dat` to `Chaste/MonolayerUseCase/results/monolayer.dat`; PhysiCell: `PhysiCell/results/monolayer/monolayer_t_diam.csv (absent)` to `PhysiCell/results/monolayer_pres/monolayer_disk_summary.csv`.

| Row | Quantity | Baseline | New | Change (%) |
|---|---|---|---|---|
| PhysiCell | note | not computable: derived CSV absent, .mat payload gitignored, archived run stops at day 16.08 | cell-centre extent plus one diameter (diameter_bbox_with_radii), as in monolayer_comparison.ipynb |  |
| PhysiCell | samples_in_window | n/a | 311 |  |
| PhysiCell | d_at_day14_um | n/a | 1200.61 |  |
| PhysiCell | day_of_last_sample | n/a | 28 |  |
| PhysiCell | d_last_um | n/a | 3200.79 |  |
| PhysiCell | deviation_min_um | n/a | -33.9143 |  |
| PhysiCell | deviation_max_um | n/a | 95.8114 |  |
| PhysiCell | deviation_mean_um | n/a | 26.4281 |  |
| PhysiCell | deviation_mean_abs_um | n/a | 34.4038 |  |
| PhysiCell | deviation_max_abs_um | n/a | 95.8114 |  |
| PhysiCell | deviation_max_abs_pct | n/a | 7.02636 |  |
| PhysiCell | cells_first | n/a | 1 |  |
| PhysiCell | cells_last | n/a | 128518 |  |

