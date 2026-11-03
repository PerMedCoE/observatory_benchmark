# Monolayer growth

This example simulates the growth of a cell monolayer. The analysis extracts the number of cells and the monolayer diameter over time.

## Contents

* [src](src) – C++ source and CMake configuration.
* [scripts](scripts) – extraction and plotting scripts.
* [results](results) – aggregated monolayer results.
* [figures](figures) – simulation and growth figures.

## Build and run

```
docker run -it -v "$(pwd):/monolayer" registry.gitlab.inria.fr/computix/computix/release:r26.03
```

Inside the container, from /monolayer:

```
mkdir build
cd build
cmake ../src
make
./simulation --help
./simulation
```

The simulation writes `CellCycle_%04d.xml` files to the current directory. Use `--sim-time` to change the target simulation time and `--without-io` to disable file output. The extractor currently searches for `Universes_%04d.xml`, so its input filename pattern must match the XML files being analyzed.

## Extract and plot

From the example directory, extract the monolayer measurements and plot them:

```
python3 scripts/extract_monolayer.py build
python3 scripts/plot_monolayer.py --results results/monolayer.yaml --output figures/monolayer_growth.svg
```

The extracted YAML stores time in hours, diameter in micrometres, and the number of cells. The aggregated data are stored in the [results](results) folder and the generated plots in the [figures](figures) folder.
