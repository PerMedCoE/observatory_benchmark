# External impulse

This example simulates the motion of one sphere representing a cell under a short constant external impulse and viscous friction. It compares explicit and implicit integration schemes.

## Contents

* [src](src) – C++ source and CMake configuration.
* [scripts](scripts) – extraction and plotting scripts.
* [results](results) – parsed simulation results.
* [figures](figures) – generated plots.

## Build and run

```
docker run -it -v "$(pwd):/external_impulse" registry.gitlab.inria.fr/computix/computix/release:r26.03
```

Inside the container, from /external_impulse:

```
mkdir build
cd build
cmake ../src
make
./simulation --output-dir .
```

Use `./simulation --help` to see the runtime, time-step, and output-directory options. The simulation writes `Cells_%03d.vtp` and `Universes_%03d.xml` files.

## Extract and plot

From the example directory, parse the directory containing the `Universes_*.xml` output. The parser writes the YAML file next to that directory:

```
python3 scripts/parse.py --dirs build
python3 scripts/plot.py --files build.yaml
```

The parsed data are stored in the [results](results) folder and the generated plots in the [figures](figures) folder.
