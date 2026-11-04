# Fixed cell cycle

This example simulates a growing cell whose volume follows a prescribed cell-cycle growth law. It produces cell-cycle output for comparison with the fitted growth parameters.

## Contents

* [src](src) – C++ source and CMake configuration.
* [scripts](scripts) – fitting, extraction, and plotting scripts.
* [results](results) – aggregated simulation results.
* [figures](figures) – cell-cycle plots and simulation snapshots.

## Build and run

```
docker run -it -v "$(pwd):/fixed_cell_cycle" registry.gitlab.inria.fr/computix/computix/release:r26.03
```

Inside the container, from /fixed_cell_cycle:

```
mkdir build
cd build
cmake ../src
make
./simulation --help
./simulation
```

The simulation writes `CellCycle_%04d.xml` files to the current directory. Use `--sim-time` to change the target simulation time and `--without-io` to disable file output.

## Analysis

Run the analysis scripts from this example directory, or provide paths with their command-line options:

```
python3 scripts/extract_cell_cycle.py build
python3 scripts/plot_cell_cycle.py --results results/cell_volume.yaml --output figures/cell_volume.svg
```

The aggregated data are stored in the [results](results) folder, and the generated plots in the [figures](figures) folder show the simulated child and parent-cell volumes over time.
