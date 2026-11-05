# Table 1 quantities recomputed from the repository

Repository: commit 6aa51a3 (30 September 2026). Criteria and unit conventions are documented in the header of `table1_summary.py`.

## Reaction-diffusion, decay

Analytical reference `analytical_solutions/diffusion/Decay/analytical_values.csv` at 10 min: average 6.8580 uM, centre 2.7699 uM; analytical steady state (1 %) at 2.18 min (average) and 2.44 min (centre).

| Tool, finest run | Average at t_end (uM) | Rel. error (%) | Centre at t_end (uM) | Centre rel. error (%) | t_ss average (min) | t_ss centre (min) | File |
|---|---|---|---|---|---|---|---|
| BioDynaMo N=48 dx=5 | 7.1296 | +3.96 | 2.9037 | +4.83 | 2.14 | 2.38 | `Biodynamo/diffusion_decay_test/data_48.csv` |
| Chaste N=48 dx=5 | 7.0537 | +2.85 | 2.7709 | +0.04 | 2.18 | 2.42 | `Chaste/DiffusionNoCells/48.dat` |
| CompuTiX N=63 dx=3.81 dt=0.006s | 6.6483 | -3.06 | 2.6777 | -3.33 | 2.30 | 2.50 | `CompuTiX/diffusion_single/Decay/dt-s-0-006_N-63.yaml` |
| PhysiCell dx=5 | 6.7837 | -1.08 | 2.7277 | -1.52 | 2.23 | 2.48 | `PhysiCell/results/diffusion_decay/size_5/physicell_decay_plot_data.csv` |
| TiSim N=40 dx=6 | 7.1842 | +4.76 | 2.9334 | +5.90 | 2.16 | 2.40 | `Tisim/diffusion_decay_test/data_40.csv` |

Across the five finest runs: average 6.65 to 7.18 uM against 6.86 uM (relative errors -3.06 % to +4.76 %, largest magnitude 4.76 %); centre 2.68 to 2.93 uM against 2.77 uM (magnitudes 0.04 % to 5.90 %); steady state at 2.1 to 2.3 min against 2.2 min.

Average-concentration relative error at t_end for every resolution (coarsest to finest):

- BioDynaMo: dx = 40 um: +29.50 % (centre +66.88 %); dx = 20 um: +15.78 % (centre +24.97 %); dx = 10 um: +7.94 % (centre +10.56 %); dx = 5 um: +3.96 % (centre +4.83 %)
- Chaste: dx = 40 um: +20.52 % (centre -3.53 %); dx = 20 um: +11.00 % (centre -0.77 %); dx = 10 um: +5.64 % (centre -0.15 %); dx = 5 um: +2.85 % (centre +0.04 %)
- CompuTiX: dx = 34.29 um: -24.02 % (centre -20.58 %); dx = 16 um: -12.06 % (centre -11.81 %); dx = 7.74 um: -6.02 % (centre -6.32 %); dx = 3.81 um: -3.06 % (centre -3.33 %)
- PhysiCell: dx = 40 um: +29.29 % (centre +65.79 %); dx = 20 um: +14.94 % (centre +23.30 %); dx = 10 um: +5.70 % (centre +7.32 %); dx = 5 um: -1.08 % (centre -1.52 %)
- TiSim: dx = 24 um: +18.78 % (centre +31.91 %); dx = 12 um: +9.53 % (centre +13.12 %); dx = 6 um: +4.76 % (centre +5.90 %)

## Reaction-diffusion, twelve point sinks

Analytical reference `analytical_solutions/diffusion/Cellsatcenter/analytical_values.csv` at 10 min: average 9.7837 uM, centre 7.1277 uM; analytical steady state (1 %) at 4.66 min (average) and 3.47 min (centre).

| Tool, finest run | Average at t_end (uM) | Rel. error (%) | Centre at t_end (uM) | Centre rel. error (%) | t_ss average (min) | t_ss centre (min) | File |
|---|---|---|---|---|---|---|---|
| BioDynaMo N=48 dx=5 | 9.7934 | +0.10 | 7.1574 | +0.42 | 4.47 | 3.35 | `Biodynamo/diffusion_uptake_test/data_48.csv` |
| Chaste N=48 dx=5 | 9.7986 | +0.15 | 7.1698 | +0.59 | 4.30 | 3.40 | `Chaste/DiffusionWithCells/48.txt` |
| CompuTiX N=63 dx=3.81 dt=0.006s | 9.7771 | -0.07 | 7.4084 | +3.94 | 4.90 | 3.70 | `CompuTiX/diffusion_single/CellsAtCenter/dt-s-0-006_N-63.yaml` |
| PhysiCell dx=5 | 9.7788 | -0.05 | 7.2308 | +1.45 | 4.79 | 3.59 | `PhysiCell/results/diffusion_uptake/size_5_uptake/physicell_uptake_plot_data.csv` |
| TiSim N=40 dx=6 | 9.7966 | +0.13 | 7.4969 | +5.18 | 4.50 | 3.50 | `Tisim/diffusion_uptake_test/data_40.csv` |

Across the five finest runs: average 9.78 to 9.80 uM against 9.78 uM (relative errors -0.07 % to +0.15 %, largest magnitude 0.15 %); centre 7.16 to 7.50 uM against 7.13 uM (magnitudes 0.42 % to 5.18 %); steady state at 4.3 to 4.9 min against 4.7 min.

Average-concentration relative error at t_end for every resolution (coarsest to finest):

- BioDynaMo: dx = 40 um: +0.84 % (centre +9.85 %); dx = 20 um: +0.40 % (centre -2.72 %); dx = 10 um: +0.20 % (centre +0.80 %); dx = 5 um: +0.10 % (centre +0.42 %)
- Chaste: dx = 40 um: +0.96 % (centre +11.57 %); dx = 20 um: +0.52 % (centre +1.41 %); dx = 10 um: +0.28 % (centre +2.41 %); dx = 5 um: +0.15 % (centre +0.59 %)
- CompuTiX: dx = 34.29 um: -0.63 % (centre -8.41 %); dx = 16 um: -0.27 % (centre +11.99 %); dx = 7.74 um: -0.15 % (centre -6.78 %); dx = 3.81 um: -0.07 % (centre +3.94 %)
- PhysiCell: dx = 40 um: +0.82 % (centre +29.36 %); dx = 20 um: +0.36 % (centre +16.65 %); dx = 10 um: +0.13 % (centre +5.23 %); dx = 5 um: -0.05 % (centre +1.45 %)
- TiSim: dx = 24 um: +0.57 % (centre +5.38 %); dx = 12 um: +0.25 % (centre +1.04 %); dx = 6 um: +0.13 % (centre +5.18 %)

## Mechanics, external impulse

Analytical reference `analytical_solutions/mechanics/analytical_values.csv`: plateau velocity 1.666667e-04 um/s (0.01 um/min), displacement 5.000000e-04 um.

| Tool | Plateau (um/s) | Rel. error (%) | Active window (s) | Displacement (um) | Rel. error (%) | Notes |
|---|---|---|---|---|---|---|
| BioDynaMo | 1.666670e-04 | +0.00 | 3 to 5.8 | 5.0000e-04 | +0.00 | nm and nm/s in file |
| CompuTiX | 1.666670e-04 | +0.00 | 3.1 to 6.1 | 5.1667e-04 | +3.33 | SI (m, m/s); implicit overdamped series |
| PhysiCell | 1.666667e-04 | +0.00 | 3.06 to 6 | 5.0000e-04 | +0.00 | dt in min, x in um, mvx in um/min |
| TiSim | 1.700000e-04 | +2.00 | 3 to 5.8 | 5.0000e-04 | +0.00 | no units in file; velocity read as um/s, position multiplied by 0.01 (as in the notebook) |
| Chaste | n/a | n/a | 3.2 to 6 | n/a | n/a | units not stated: position rises to 8.33333 units, velocity column 4 plateau 0.277778 units; excluded from the error comparison |

## Mechanics, two-cell relaxation with the common extended Hertz law

Reference ODE: d(delta)/dt = -2 F/zeta, F = (4/3) E* sqrt(R~) delta^1.5 - pi gamma R~, E* = 267.86 Pa, R~ = 2.5 um, gamma = 8.56e-15 J/m2; equilibrium overlap 2.42e-07 um.

| Drag (N s/m) | Tool | Overlap at t_end (um) | ODE at t_end (um) | t_half tool / ODE (s) | t(overlap < 0.1 um) (s) | Mean abs. dev. from ODE, t <= 3 h (um) | Mean abs. dev. from notebook curve (um) | t_end (s) | File |
|---|---|---|---|---|---|---|---|---|---|
| 0.01 | BioDynaMo | 1e-05 | 2.72e-06 | 120 / 7.7 | 120 | 0.0007 | 0.0028 | 10800 | `Biodynamo/mechanics_hertz_relaxation/results_drag_0.01/positions.csv` |
| 0.01 | CompuTiX | 4e-06 | 8.71e-06 | 10 / 7.7 | 10 | 0.0018 | 0.0118 | 5990 | `CompuTiX/overlap_relaxation/results_mu_0.01.yaml` |
| 0.01 | PhysiCell | 3.16e-05 | 1.03e-06 | 6 / 7.7 | 6 | 0.0005 | 0.0061 | 18000 | `PhysiCell/results/mechanics_pushing_extended_hertz/drag_0.01/physicell_mechanics_pushing_extended_hertz.csv` |
| 0.01 | TiSim | 0.00052 | 1.03e-06 | 24 / 7.7 | 117 | 0.0037 | 0.0025 | 18000 | `Tisim/mechanics_relaxation/data_drag_0.01.csv` |
| 0.1 | BioDynaMo | 0.00047 | 0.00026 | 180 / 78.3 | 600 | 0.0081 | 0.0419 | 10800 | `Biodynamo/mechanics_hertz_relaxation/results_drag_0.1/positions.csv` |
| 0.1 | CompuTiX | 0.000744 | 0.000838 | 60 / 78.3 | 300 | 0.0089 | 0.0964 | 5940 | `CompuTiX/overlap_relaxation/results_mu_0.1.yaml` |
| 0.1 | PhysiCell | 9.49e-05 | 9.49e-05 | 72 / 78.3 | 384 | 0.0003 | 0.0524 | 18000 | `PhysiCell/results/mechanics_pushing_extended_hertz/drag_0.1/physicell_mechanics_pushing_extended_hertz.csv` |
| 0.1 | TiSim | 0.00109 | 9.49e-05 | 228 / 78.3 | 1191 | 0.0324 | 0.0198 | 18000 | `Tisim/mechanics_relaxation/data_drag_0.1.csv` |
| 1 | BioDynaMo | 0.0325 | 0.0198 | 1080 / 740.8 | 5220 | 0.0432 | 0.2376 | 10800 | `Biodynamo/mechanics_hertz_relaxation/results_drag_1/positions.csv` |
| 1 | CompuTiX | 0.051 | 0.0527 | 720 / 740.8 | 3780 | 0.0059 | 0.3456 | 5940 | `CompuTiX/overlap_relaxation/results_mu_1.yaml` |
| 1 | PhysiCell | 0.00802 | 0.00802 | 732 / 740.8 | 3828 | 0.0003 | 0.2824 | 18000 | `PhysiCell/results/mechanics_pushing_extended_hertz/drag_1/physicell_mechanics_pushing_extended_hertz.csv` |
| 1 | TiSim | 0.0553 | 0.00802 | 2265 / 740.8 | 11934 | 0.1959 | 0.0863 | 18000 | `Tisim/mechanics_relaxation/data_drag_1.csv` |
| 1 | Chaste | 0.00792 | 0.00802 | 900 / 740.8 | 3900 | 0.0019 | 0.2780 | 18000 | `Chaste/HertzCellRelaxation/node_locations.dat` |

At 1 N s/m: time to halve the overlap BioDynaMo 1080 s; CompuTiX 720 s; PhysiCell 732 s; TiSim 2265 s; Chaste 900 s; ODE 740.8 s. Final centre-to-centre distances at 1 N s/m: BioDynaMo 9.9675 um at 10800 s; CompuTiX 9.9490 um at 5940 s; PhysiCell 9.9920 um at 18000 s; TiSim 9.9447 um at 18000 s; Chaste 9.9921 um at 18000 s.

## Mechanics, pushing with the built-in contact models

| Tool | Start (um) | Minimum distance (um) at | Final distance (um) at | Residual overlap (um) | Notes | File |
|---|---|---|---|---|---|---|
| BioDynaMo | 30 | 8.0000 (step 10) | 9.3750 (step 99 (10 min at dt = 0.1 min)) | 0.6250 | um | `Biodynamo/mechanics_pushing/results_timestep0.1/positions.csv` |
| Chaste | 30 | 8.8308 (0.0176667 time units) | 9.9790 (0.0833333 time units (5 min if hours)) | 0.0210 | dimensionless; multiplied by 10 as in olderplotscripts/plot_mechanics_pushing.py | `Chaste/mechanics_pushing/results/results.viznodelocations` |
| CompuTiX | 30 | 7.9219 (72 s) | 9.0954 (594 s) | 0.9046 | m in file; overdamped JKR run matching main.cpp | `CompuTiX/mechanics_pushing/benchmark_exmaple_2.yaml` |
| PhysiCell | 9 | n/a | n/a | n/a | not computable: no derived CSV and the .mat payload is gitignored | `PhysiCell/results/mechanics_pushing/ (snapshots only)` |
| TiSim | 30 | 8.9703 (1.05167 min) | 9.8788 (9.99833 min) | 0.1212 | um; approach stopped at 9.0 um | `Tisim/mechanics_pushing/mechanics_pushing.csv` |
| TiSim (older run, force never removed) | 30 | 3.2168 (2.5 min) | 3.2168 (10 min) | 6.7832 | um | `Tisim/mechanics_pushing/mechanical pushing.csv` |

## Cell cycle and volume growth

| Tool | V0 | Vmax (% of V0) at (h) | Division events (h) | Samples, span (h) | Notes | File |
|---|---|---|---|---|---|---|
| BioDynaMo | 523.599 | 1045.8 (199.7 %) at 17.36 | 18.000->18.010;36.020->36.030 | 4800, 0.01 to 48 | mother cell; time in hours, volume in um3 | `Biodynamo/fixed_cell_cycle/new_results/cell-0-sim1.csv` |
| Chaste | 0.523599 | 1.0522 (201.0 %) at 18.00 | 18.000->18.100;36.000->36.100 | 481, 0 to 48 | first cell record; dimensionless volume | `Chaste/fixed_cell_cycle/results/cellcycle_fixed.dat` |
| CompuTiX | 523.599 | 1047.2 (200.0 %) at 16.00 | 18.000->18.100;36.000->36.100 | 380, 0 to 37.9 | volume_per_parent_cell (the simulation; the notebook plots data/cell_cycle.csv, which is the reference) | `CompuTiX/fixed_cell_cycle/results/cell_volume.yaml` |
| CompuTiX (volume_per_child_cell) | 523.599 | 1047.2 (200.0 %) at 16.00 | none | 380, 0 to 37.9 | per daughter during division, hence no drop | `CompuTiX/fixed_cell_cycle/results/cell_volume.yaml` |
| PhysiCell | 523.6 | 1038.9 (198.4 %) at 17.50 | 17.500->18.000;35.500->36.000 | 97, 0 to 48 | cell id 0; 30 min sampling; um3 | `PhysiCell/results/cell_cycle_fixed/cell_volumes.csv` |
| TiSim (file used in Figure 4B) | 1 | 2 (200.0 %) at 17.77 | 17.769->18.249;35.529->36.009 | 100, 0.488889 to 48.0089 | relative volume; phase-resolved output (0.48 h sampling) since commit 6aa51a3, hourly export before | `Tisim/fixed_cell_cycle/cell cycle fix.csv` |
| Reference data | 2494 | 4996.4 (200.3 %) at 17.50 | 17.500->18.000 | 49, 0 to 24 | reference trajectory of Figure 4B; identical to CompuTiX/fixed_cell_cycle/data/cell_cycle.csv | `experimental_data/Cell cycle volume dynamics.txt` |

Maximum volume across the five tools (TiSim file used in Figure 4B): 198.4 % to 201.0 % of V0.

## Monolayer growth use case

Reference `experimental_data/2D monolayer data from Bru et al 1998.txt`: diameters [1140.0, 1400.0, 1590.0, 2040.0, 2250.0, 3040.0] um at days [14.0, 16.08, 17.0, 20.04, 21.08, 26.92].

| Tool | d at day 14 (um) | d at last sample (um, day) | Deviation range (um) | Mean abs. dev. (um) | Max abs. dev. (um, % of reference) | Cells first to last | Notes | File |
|---|---|---|---|---|---|---|---|---|
| BioDynaMo (env_dims, the series plotted by plot_monolayer.py) | 1240 | 3000 (day 26.50) | -26.4 to +100.0 | 36.3 | 100.0 (8.77 %) | 3249 to 93206 | uniform-grid extent in 40 um steps | `Biodynamo/monolayer/results/monolayer_growth.json` |
| BioDynaMo (tumor_diameter, cell-centre extent) | 1120 | 2909 (day 26.50) | -126.2 to -15.0 | 75.8 | 126.2 (5.47 %) | 3249 to 93206 | max of x and y extent of cell centres | `Biodynamo/monolayer/results/monolayer_growth.json` |
| Chaste | 1115 | 3114 (day 27.00) | -48.3 to +58.5 | 20.9 | 58.5 (1.96 %) | 9124 to 75835 | undocumented run (monolayer_readme.txt) | `Chaste/monolayer/results/monolayer.dat` |
| CompuTiX | 1170 | 3004 (day 26.96) | -83.9 to +61.7 | 41.2 | 83.9 (3.68 %) | 1 to 99252 | largest pairwise centre distance | `CompuTiX/monolayer/results/monolayer.yaml` |
| PhysiCell | n/a | n/a | n/a | n/a | n/a | n/a | not computable: derived CSV absent, .mat payload gitignored, archived run stops at day 16.08 | `PhysiCell/results/monolayer/monolayer_t_diam.csv (absent)` |
| TiSim | 1089 | 2941 (day 25.90) | -66.9 to +38.9 | 29.4 | 66.9 (2.97 %) | 1 to 146919 | twice the population radius | `Tisim/monolayer/2D disk.csv` |

