# PhysiCell analysis

This directory stays flat on purpose.

Many notebooks here assume the current layout by:
- importing sibling helpers such as `potentials.py`
- reading data with relative paths such as `../results/...` and `../code/...`
- saving local artifacts such as `diffusion_single.png`

Moving notebooks into topic subfolders would require updating many hard-coded paths. For now, the safest organization is an indexed flat layout.

## Workflow groups

### Generation and export notebooks

- `generate_diffusion_csv.ipynb`: export diffusion benchmark data
- `generate_fixed_cell_cycle_csv.ipynb`: export fixed cell cycle outputs
- `generate_mechanics_movement_csv.ipynb`: export mechanics movement outputs
- `generate_mechanics_pushing.ipynb`: generate mechanics pushing analysis data
- `generate_monolayer.ipynb`: monolayer experiment notebook
- `generate_monolayer_csv.ipynb`: export monolayer outputs
- `generate_stochastic_cell_cycle_csv.ipynb`: export stochastic cell cycle outputs

### Diffusion and decay studies

- `decay_tools_comparison.ipynb`
- `diffusion_many_voxels.ipynb`
- `pc_decay_study_decay.ipynb`
- `pc_decay_study_uptake_by_cells.ipynb`

### Mechanics studies

- `analysismechanicalmodel.ipynb`
- `mechanics_movement_implementations_analysis.ipynb`
- `mechanics_pushing_extended_hertz_analytical_solution.ipynb`
- `mechanics_pushing_physicell_comparison.ipynb`
- `overlap_relaxation_analytic.ipynb`
- `standard_update_velocity_analytical.ipynb`
- `standard_velocity_position_analytical.ipynb`

### Shared helpers and supporting scripts

- `potentials.py`: shared mechanics helper used by multiple notebooks
- `Potentials_simulations.ipynb`: exploratory notebook for `potentials.py`
- `plot_sphereoid.ipynb`
- `plot_sphereoid.py`

## File naming convention for new work

- Use `generate_*.ipynb` for notebooks that export CSVs or benchmark-ready summaries.
- Use `*_analysis.ipynb` for comparison or interpretation notebooks.
- Use `*_analytic.ipynb` or `*_analytical.ipynb` for derivations and closed-form checks.
- Keep shared Python helpers in `.py` files beside the notebooks that import them.

## Housekeeping

- Generated caches and temporary notebook checkpoints should stay out of version control.
- If you later want a physical folder split, do it as a dedicated refactor and update relative paths in the affected notebooks at the same time.