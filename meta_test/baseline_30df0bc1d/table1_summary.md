# Table 1 quantities recomputed from the repository

Repository: `.`. Criteria and unit conventions are documented in the header of `table1_summary.py`.

## Reaction-diffusion, decay

Analytical reference `ResultAnalysis/analytical_solutions/diffusion/Decay/analytical_values.csv` at 10 min: average 6.8580 uM, centre 2.7699 uM; analytical steady state (1 %) at 2.18 min (average) and 2.44 min (centre).

| Tool, finest run | Average at t_end (uM) | Rel. error (%) | Centre at t_end (uM) | Centre rel. error (%) | t_ss average (min) | t_ss centre (min) | File |
|---|---|---|---|---|---|---|---|
| BioDynaMo N=48 dx=5 | 7.1296 | +3.96 | 2.9037 | +4.83 | 2.14 | 2.38 | `Biodynamo/diffusion_decay_test/data_48.csv` |
| Chaste N=48 dx=5 | 7.0537 | +2.85 | 2.7709 | +0.04 | 2.18 | 2.42 | `Chaste/DiffusionNoCells/results/48.dat` |
| CompuTiX N=63 dx=3.81 dt=0.006s | 6.6483 | -3.06 | 2.6777 | -3.33 | 2.30 | 2.50 | `CompuTiX/diffusion_single/Decay/results/dt-s-0-006_N-63.yaml` |
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

Analytical reference `ResultAnalysis/analytical_solutions/diffusion/Cellsatcenter/analytical_values.csv` at 10 min: average 9.7837 uM, centre 7.1277 uM; analytical steady state (1 %) at 4.66 min (average) and 3.47 min (centre).

| Tool, finest run | Average at t_end (uM) | Rel. error (%) | Centre at t_end (uM) | Centre rel. error (%) | t_ss average (min) | t_ss centre (min) | File |
|---|---|---|---|---|---|---|---|
| BioDynaMo N=48 dx=5 | 9.7934 | +0.10 | 7.1574 | +0.42 | 4.47 | 3.35 | `Biodynamo/diffusion_uptake_test/data_48.csv` |
| Chaste N=48 dx=5 | 9.7986 | +0.15 | 7.1698 | +0.59 | 4.30 | 3.40 | `Chaste/DiffusionWithCells/results/48.txt` |
| CompuTiX N=63 dx=3.81 dt=0.006s | 9.7771 | -0.07 | 7.4084 | +3.94 | 4.90 | 3.70 | `CompuTiX/diffusion_single/CellsAtCenter/results/dt-s-0-006_N-63.yaml` |
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

Analytical reference `ResultAnalysis/analytical_solutions/mechanics/analytical_values.csv`: plateau velocity 1.666667e-04 um/s (0.01 um/min), displacement 5.000000e-04 um.

| Tool | Plateau (um/s) | Rel. error (%) | Active window (s) | Displacement (um) | Rel. error (%) | Notes |
|---|---|---|---|---|---|---|
| BioDynaMo | 1.666670e-04 | +0.00 | 3 to 5.8 | 5.0000e-04 | +0.00 | nm and nm/s in file |
| CompuTiX | 1.666670e-04 | +0.00 | 3.1 to 6.1 | 5.1667e-04 | +3.33 | SI (m, m/s); implicit overdamped series |
| PhysiCell | 1.666667e-04 | +0.00 | 3 to 5.94 | 5.0000e-04 | +0.00 | dt in min, x in um, mvx in um/min |
| TiSim | 1.700000e-04 | +2.00 | 3 to 5.8 | 5.0000e-04 | +0.00 | units in header (s, um, um/s) |
| Chaste | 1.666667e-04 | +0.00 | 3.2 to 6 | 5.0000e-04 | +0.00 | um and s; velocity from positions |

## Mechanics, two-cell relaxation with the common extended Hertz law

Reference ODE: d(delta)/dt = -2 F/zeta, F = (4/3) E* sqrt(R~) delta^1.5 - pi gamma R~, E* = 267.86 Pa, R~ = 2.5 um, gamma = 8.56e-15 J/m2; equilibrium overlap 2.42e-07 um.

| Drag (N s/m) | Tool | Overlap at t_end (um) | ODE at t_end (um) | t_half tool / ODE (s) | t(overlap < 0.1 um) (s) | Mean abs. dev. from ODE, t <= 3 h (um) | Mean abs. dev. from notebook curve (um) | t_end (s) | File |
|---|---|---|---|---|---|---|---|---|---|
| 0.01 | BioDynaMo | 1e-05 | 2.72e-06 | 56.3309 / 7.3 | 112.823 | 0.0003 | 0.0033 | 10800 | `Biodynamo/mechanics_hertz_relaxation/results_drag_0.01/positions.csv` |
| 0.01 | CompuTiX | 4e-06 | 8.71e-06 | 5.12263 / 7.3 | 9.22073 | 0.0018 | 0.0118 | 5990 | `CompuTiX/overlap_relaxation/results/overlap_relaxation_mu_0.01.yaml` |
| 0.01 | PhysiCell | 3.16e-05 | 1.03e-06 | 2.95147 / 7.3 | 5.31261 | 0.0005 | 0.0061 | 18000 | `PhysiCell/results/mechanics_pushing_extended_hertz/drag_0.01/physicell_mechanics_pushing_extended_hertz.csv` |
| 0.01 | TiSim | 0.00052 | 1.03e-06 | 21.8992 / 7.3 | 116.02 | 0.0037 | 0.0025 | 18000 | `Tisim/mechanics_relaxation/data_drag_0.01.csv` |
| 0.1 | BioDynaMo | 0.00026 | 0.00026 | 135.643 / 73.4 | 443.265 | 0.0030 | 0.0471 | 10800 | `Biodynamo/mechanics_hertz_relaxation/results_drag_0.1/positions.csv` |
| 0.1 | CompuTiX | 0.000744 | 0.000838 | 44.967 / 73.4 | 254.177 | 0.0089 | 0.0964 | 5940 | `CompuTiX/overlap_relaxation/results/overlap_relaxation_mu_0.1.yaml` |
| 0.1 | PhysiCell | 9.49e-05 | 9.49e-05 | 70.1395 / 73.4 | 380.093 | 0.0003 | 0.0524 | 18000 | `PhysiCell/results/mechanics_pushing_extended_hertz/drag_0.1/physicell_mechanics_pushing_extended_hertz.csv` |
| 0.1 | TiSim | 0.00109 | 9.49e-05 | 225.614 / 73.4 | 1190.29 | 0.0324 | 0.0198 | 18000 | `Tisim/mechanics_relaxation/data_drag_0.1.csv` |
| 1 | BioDynaMo | 0.02 | 0.0198 | 792.629 / 733.5 | 3887.5 | 0.0049 | 0.2758 | 10800 | `Biodynamo/mechanics_hertz_relaxation/results_drag_1/positions.csv` |
| 1 | CompuTiX | 0.051 | 0.0527 | 702.999 / 733.5 | 3726.1 | 0.0059 | 0.3456 | 5940 | `CompuTiX/overlap_relaxation/results/overlap_relaxation_mu_1.yaml` |
| 1 | PhysiCell | 0.00802 | 0.00802 | 730.507 / 733.5 | 3826.15 | 0.0003 | 0.2824 | 18000 | `PhysiCell/results/mechanics_pushing_extended_hertz/drag_1/physicell_mechanics_pushing_extended_hertz.csv` |
| 1 | TiSim | 0.0553 | 0.00802 | 2263 / 733.5 | 11933 | 0.1959 | 0.0863 | 18000 | `Tisim/mechanics_relaxation/data_drag_1.csv` |
| 1 | Chaste | 0.00792 | 0.00802 | 730.584 / 733.5 | 3780.86 | 0.0019 | 0.2780 | 18000 | `Chaste/HertzCellRelaxation/results/node_locations.dat` |

At 1 N s/m: time to halve the overlap BioDynaMo 792.629 s; CompuTiX 702.999 s; PhysiCell 730.507 s; TiSim 2263 s; Chaste 730.584 s; ODE 733.5 s. Final centre-to-centre distances at 1 N s/m: BioDynaMo 9.9800 um at 10800 s; CompuTiX 9.9490 um at 5940 s; PhysiCell 9.9920 um at 18000 s; TiSim 9.9447 um at 18000 s; Chaste 9.9921 um at 18000 s.

## Mechanics, pushing with the built-in contact models

| Tool | Start (um) | Minimum distance (um) at | Final distance (um) at | Residual overlap (um) | Notes | File |
|---|---|---|---|---|---|---|
| BioDynaMo | 28 | 8.3950 (step 10) | 9.3750 (step 99 (10 min at dt = 0.1 min)) | 0.6250 | um; archived run starts at 28 um (question 8.6) | `Biodynamo/mechanics_pushing/results_timestep0.1/positions.csv` |
| Chaste | 30 | 8.8308 (1.06 min) | 9.9790 (5 min) | 0.0210 | 10 um per length unit, time in h (assumed; question 8.12) | `Chaste/mechanics_pushing/results/results.viznodelocations` |
| CompuTiX | 30 | 7.9220 (72 s) | 9.0954 (594 s) | 0.9046 | m in file; overdamped JKR run matching main.cpp | `CompuTiX/mechanics_pushing/results/mechanics_pushing.yaml` |
| PhysiCell | 30 | 8.9983 (1 min) | 9.7373 (10 min) | 0.2627 | um, min; motility off once centres < 10 um | `PhysiCell/results/mechanics_pushing/physicell_mechanics_pushing.csv` |
| TiSim | 30 | 8.9703 (1.05167 min) | 9.8788 (9.99833 min) | 0.1212 | um; approach stopped at 9.0 um | `Tisim/mechanics_pushing/mechanics_pushing.csv` |
| TiSim (older run, force never removed) | 30 | 3.2168 (2.5 min) | 3.2168 (10 min) | 6.7832 | um | `Tisim/mechanics_pushing/mechanical pushing.csv` |

## Cell cycle and volume growth

| Tool | V0 | Vmax (% of V0) at (h) | Division events (h) | Samples, span (h) | Notes | File |
|---|---|---|---|---|---|---|
| BioDynaMo | 523.599 | 1045.8 (199.7 %) at 17.36 | 18.000->18.010;36.020->36.030 | 4800, 0.01 to 48 | mother cell; time in hours, volume in um3 | `./Biodynamo/fixed_cell_cycle/results/cell-0.csv` |
| Chaste | 0.523599 | 1.0522 (201.0 %) at 18.00 | 18.000->18.100;36.000->36.100 | 481, 0 to 48 | first cell record; dimensionless volume | `./Chaste/FixedCellCycle/results/cellcycle_fixed.dat` |
| CompuTiX | 523.599 | 1047.2 (200.0 %) at 16.00 | 18.000->18.100;36.000->36.100 | 380, 0 to 37.9 | volume_per_parent_cell (the simulation; the notebook plots data/cell_cycle.csv, which is the reference) | `./CompuTiX/fixed_cell_cycle/results/cell_volume.yaml` |
| CompuTiX (volume_per_child_cell) | 523.599 | 1047.2 (200.0 %) at 16.00 | none | 380, 0 to 37.9 | per daughter during division, hence no drop | `./CompuTiX/fixed_cell_cycle/results/cell_volume.yaml` |
| PhysiCell | 523.6 | 1038.9 (198.4 %) at 17.50 | 17.500->18.000;35.500->36.000 | 97, 0 to 48 | cell id 0; 30 min sampling; um3 | `./PhysiCell/results/cell_cycle_fixed/cell_volumes.csv` |
| TiSim (file used in Figure 4B) | 1 | 2 (200.0 %) at 17.77 | 17.769->18.249;35.529->36.009 | 100, 0.488889 to 48.0089 | relative volume; phase-resolved output (0.48 h sampling) since commit 6aa51a3, hourly export before | `./Tisim/fixed_cell_cycle/cell cycle fix.csv` |
| Reference data | 2494 | 4996.4 (200.3 %) at 17.50 | 17.500->18.000 | 49, 0 to 24 | reference trajectory of Figure 4B; identical to CompuTiX/fixed_cell_cycle/data/cell_cycle.csv | `./ResultAnalysis/analytical_solutions/experimental_data/Cell cycle volume dynamics.txt` |

Maximum volume across the five tools (TiSim file used in Figure 4B): 198.4 % to 201.0 % of V0.

## Monolayer growth use case

Reference `ResultAnalysis/analytical_solutions/experimental_data/2D monolayer data from Bru et al 1998.txt`: diameters [1140.0, 1400.0, 1590.0, 2040.0, 2250.0, 3040.0] um at days [14.0, 16.08, 17.0, 20.04, 21.08, 26.92].

| Tool | d at day 14 (um) | d at last sample (um, day) | Deviation range (um) | Mean abs. dev. (um) | Max abs. dev. (um, % of reference) | Cells first to last | Notes | File |
|---|---|---|---|---|---|---|---|---|
| BioDynaMo | 1120 | 2902 (day 26.50) | -131.0 to -20.0 | 80.0 | 131.0 (5.68 %) | 3249 to 92960 | max of x and y extent of cell centres | `Biodynamo/monolayer/results/monolayer_growth.json` |
| Chaste | 1115 | 3114 (day 27.00) | -48.3 to +58.5 | 20.9 | 58.5 (1.96 %) | 9124 to 75835 | undocumented run (monolayer_readme.txt) | `Chaste/MonolayerUseCase/results/monolayer.dat` |
| CompuTiX | 1170 | 3004 (day 26.96) | -83.9 to +61.7 | 41.2 | 83.9 (3.68 %) | 1 to 99252 | largest pairwise centre distance | `CompuTiX/monolayer/results/monolayer.yaml` |
| PhysiCell | 1201 | 3201 (day 28.00) | -33.9 to +95.8 | 34.4 | 95.8 (7.03 %) | 1 to 128518 | cell-centre extent plus one diameter (diameter_bbox_with_radii), as in monolayer_comparison.ipynb | `PhysiCell/results/monolayer_pres/monolayer_disk_summary.csv` |
| TiSim | 1089 | 2941 (day 25.90) | -66.9 to +38.9 | 29.4 | 66.9 (2.97 %) | 1 to 146919 | twice the population radius | `Tisim/monolayer/2D disk.csv` |

## Table 1 cells

- Decay: average at 10 min, relative error -3.1 % to +4.8 % (BioDynaMo +4.0 %, Chaste +2.9 %, CompuTiX -3.1 %, PhysiCell -1.1 %, TiSim +4.8 %)
- Point sinks: average at 10 min, relative error -0.1 % to +0.2 % (BioDynaMo +0.1 %, Chaste +0.2 %, CompuTiX -0.1 %, PhysiCell -0.1 %, TiSim +0.1 %)
- External impulse: plateau 0.01 um/min; tool plateau errors BioDynaMo +0.00 %, CompuTiX +0.00 %, PhysiCell +0.00 %, TiSim +2.00 %, Chaste +0.00 %; displacement 0.5 nm; tool displacements BioDynaMo 0.5 nm, CompuTiX 0.517 nm, PhysiCell 0.5 nm, TiSim 0.5 nm, Chaste 0.5 nm
- Common law, 0.01 N s/m: time to halve the overlap, reference 7.3 s; BioDynaMo 56 s (output every 60 s), CompuTiX 5 s (output every 10 s), PhysiCell 3 s (output every 6 s), TiSim 22 s (output every 3 s)
- Common law, 0.1 N s/m: time to halve the overlap, reference 73.4 s; BioDynaMo 136 s (output every 60 s), CompuTiX 45 s (output every 60 s), PhysiCell 70 s (output every 6 s), TiSim 226 s (output every 3 s)
- Common law, 1 N s/m: time to halve the overlap, reference 733.5 s; BioDynaMo 793 s (output every 60 s), CompuTiX 703 s (output every 60 s), PhysiCell 731 s (output every 6 s), TiSim 2263 s (output every 3 s), Chaste 731 s (output every 300 s)
- Built-in contact: final centre-to-centre distance 9.10 um (CompuTiX, 594 s), 9.38 um (BioDynaMo, step 99 (10 min at dt = 0.1 min)), 9.74 um (PhysiCell, 10 min), 9.88 um (TiSim, 9.99833 min), 9.98 um (Chaste, 5 min)
- Cell cycle: maximum volume 198.4 % to 201.0 % of V0
- Monolayer: maximum absolute deviation 58 to 131 um (2.0 % to 7.0 %); BioDynaMo 131 um (5.7 %), Chaste 58 um (2.0 %), CompuTiX 84 um (3.7 %), PhysiCell 96 um (7.0 %), TiSim 67 um (3.0 %)

