# Overlap relaxation

This example simulates two initially overlapping spheres relaxing towards their equilibrium contact distance.

## Contents

* [src](src) – C++ source and CMake configuration.
* [scripts](scripts) – extraction and plotting scripts.
* [results](results) – example parsed results for the three values of mu.
* [figures](figures) – distance plots for the three values of mu.

## Build and run

```
docker run -it -v "$(pwd):/overlap_relaxation" registry.gitlab.inria.fr/computix/computix/release:r26.03
```

Inside the container, from /overlap_relaxation:

```
mkdir build
cd build
cmake ../src
make
./simulation --help
./simulation --output-dir .
```

The executable writes `Cells_%03d.vtp` and `Universes_%03d.xml` files to the selected output directory. Use `--sim-time`, `--dt`, and `--output-dir` to control the run.

## Extract and plot

From the example directory, parse the directory containing the XML output and plot the generated YAML file:

```
python3 scripts/parse.py --dirs build
python3 scripts/plot.py --files build.yaml
```

The parsed data are stored in the [results](results) folder and the generated plots in the [figures](figures) folder.
