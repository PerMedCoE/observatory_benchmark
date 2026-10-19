# TiSim Benchmark Outputs

This folder contains TiSim output files for the seven benchmark cases. TiSim input files are not included. The TiSim version and case parameter tables are documented in the manuscript (page 22).

## Folder contents

```text
diffusion_decay_test/       CSV outputs for diffusion and decay
diffusion_uptake_test/      CSV outputs for diffusion and uptake
fixed_cell_cycle/           Cell-cycle output
mechanics_external_impulse/ External-impulse output
mechanics_pushing/          Pushing outputs, analysis script, and animation
mechanics_relaxation/       Hertz-relaxation outputs for three drag values
monolayer/                  2D disk output and related scripts
results/                    Consolidated CSV and spreadsheet results
xlsx_to_csv.py              Spreadsheet-to-CSV conversion helper
```

## Benchmark notes

- Diffusion uses FreeFEM finite elements with forward Euler time stepping under the CFL condition; the time step is 0.1 min. Uptake is limited to prevent negative concentrations.
- The mechanical contact parameters include Young's modulus of 450 Pa and Poisson's ratio of 0.4. Relaxation drag datasets cover 0.01, 0.1, and 1 N s m-1; the drag coefficient is multiplied by contact area to obtain this effective unit.
- Cell-radius growth was calibrated to the volume curve shown in the manuscript. Monolayer proliferation stops above a pressure of 50 Pa; the reported cycle-time range of 34,451 to 90,943 s is intended.
- The cell-cycle output used for Figure 4B is phase-resolved. The corrected pushing run applies force through 9 µm.

For the full TiSim version and parameter tables, see the manuscript. A contact address for requesting the closed-source software is not listed in this repository.
