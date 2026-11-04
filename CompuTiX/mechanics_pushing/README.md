# Mechanics: pushing spheres

This example simulates two initially separated spheres pushed towards each other by an external force. It measures their motion and contact response.

## Contents

* [src](src) – C++ source and CMake configuration.
* [scripts](scripts) – extraction and plotting scripts.
* [results](results) – parsed simulation results.
* [figures](figures) – generated plots.

## Build and run

```
docker run -it -v "$(pwd):/mechanics_pushing" registry.gitlab.inria.fr/computix/computix/release:r26.03
```

Inside the container, from /mechanics_pushing:

```
mkdir build
cd build
cmake ../src
make
./simulation --help
./simulation --output-dir .
```

The executable writes `Cells_%03d.vtp` and `Universes_%03d.xml` files to the selected output directory. Use `--sim-time`, `--dt`, and `--output-dir` to control the run. The parser currently searches for `Simulation_*.xml`, so its input filename pattern must match the XML files being analyzed.

## Extract and plot

The parser takes one or more directories containing its expected XML output and writes a YAML file next to each directory:

```
python3 scripts/parse.py --dirs build
python3 scripts/plot.py --files build.yaml
```

The parsed data are stored in the [results](results) folder and the generated plots in the [figures](figures) folder.
