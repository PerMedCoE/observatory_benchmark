# Open Benchmarking for Cell-Based Multiscale Models

A community-driven benchmark initiative for evaluating and comparing Center-based agent-Based Models (CBM) in biomedical applications.

## Overview

This repository contains the benchmark framework and results for comparing various cell-based multiscale models, specifically focusing on off-lattice center-based agent-based models (CBM). The initiative aims to establish standardized benchmarks for evaluating different CBM tools, similar to successful benchmarking efforts like CASP or the MICCAI's medical segmentation one.

## Participating Tools

The benchmark includes the following CBM tools:

- [BioDynaMo](https://biodynamo.org/)
- [Chaste](https://www.cs.ox.ac.uk/chaste/)
- CompuTiX
- [PhysiCell](http://physicell.org/)
- TiSim

## Benchmark Tests

The repository includes several unit tests designed to evaluate different aspects of CBM implementations:

### 1. Diffusion Tests
- Single-cell diffusion scenarios (`diffusion_single/`)
- Multiple-cell diffusion interactions (work in progress)

### 2. Mechanics Tests
- Friction-based mechanics (`mechanics_friction/`)
- Pushing mechanics (`mechanics_pushing/`)

### 3. Cell Cycle Tests
- Fixed cell cycle simulations (`fixed_cell_cycle/`)
- Stochastic cell cycle simulations (work in progress)

### 4. Growth Scenarios
- Monolayer growth simulations (`monolayer/`)
- Complex multi-cellular organization (work in progress)

## Repository Structure

```
├── Biodynamo/           # BioDynaMo implementation and results
├── Chaste/             # Chaste implementation and results
├── CompuTiX/           # CompuTiX implementation and results
├── PhysiCell/          # PhysiCell implementation and results
├── Tisim/              # TiSim implementation and results
├── experimental_data/  # Reference experimental datasets
└── ResultAnalysis/     # Analysis scripts and comparative results
```

Each tool's directory contains:
- Source code for benchmark implementations (when available)
- Results from benchmark runs
- Tool-specific configuration files
- Analysis and visualization scripts

## Experimental Data

The `experimental_data/` directory contains reference datasets used for validation:
- 2D monolayer growth data from Bru et al. 1998
- Cell cycle volume dynamics measurements

## Result Analysis

The `ResultAnalysis/` directory provides:
- Scripts for analyzing benchmark results
- Comparative analysis across different tools
- Ground truth data for validation
- Visualization and plotting tools

## Getting Started

Each tool's directory contains specific instructions for running the benchmarks. Please refer to the individual README files in each directory for detailed setup and execution instructions.

## Contributing

This is a community-driven initiative, and contributions are welcome. Please contact the repository maintainers or create an issue to discuss potential contributions.

## Publications

This work is associated with the following publication:
- Ntiniakou et al., "Open Benchmarking for Cell-Based Multiscale Models: Lessons from a Community Initiative", 2025, DOI:TBD

## License

Please refer to the LICENSE file of each tool for terms of use and distribution.

## Acknowledgments

This work is part of a collaborative effort to strengthen the computational biology simulation community and advance the development of Virtual Human Twins (VHT) in biomedical research.

## Contact

For questions or feedback about this benchmark initiative, please open an issue in this repository or send a mail to [Arnau Montagud](mailto:arnau.montagud@csic.es).

---
Initiative created and maintained as part of the [PerMedCoE project](https://permedcoe.eu/).
