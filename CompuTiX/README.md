# CompuTiX examples

This directory contains the CompuTiX simulation examples, their post-processing scripts, and the figures and result files produced from them.

## Examples

* [diffusion_single](diffusion_single) – two single-cell diffusion examples, documented together: [CellsAtCenter](diffusion_single/CellsAtCenter) and [Decay](diffusion_single/Decay).
* [external_impulse](external_impulse) – motion of a sphere under a short external impulse, using explicit and implicit integration schemes.
* [fixed_cell_cycle](fixed_cell_cycle) – cell-cycle simulation with prescribed growth.
* [mechanics_pushing](mechanics_pushing) – two initially separated spheres pushed towards each other.
* [monolayer](monolayer) – growth of a cell monolayer.
* [overlap_relaxation](overlap_relaxation) – relaxation of two initially overlapping spheres.

Each example contains its C++ source and CMake files in src, analysis scripts in scripts, generated figures in figures, and aggregated results in results where applicable.
