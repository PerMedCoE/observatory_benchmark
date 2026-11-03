# Single-cell diffusion examples

This folder contains two diffusion simulations that share the same voxel-based model and analysis workflow:

* [CellsAtCenter](CellsAtCenter) – a cell at the centre of a cubic voxel domain consumes the diffusing substance.
* [Decay](Decay) – the substance diffuses while undergoing decay, without a cell.

The README is shared by both examples. Each example has its own `src`, `scripts`, `figures`, and `results` directories.

## Build and run

The commands below apply to either example. First enter the selected example directory, then start the CompuTiX Docker image from there:

```
cd CellsAtCenter  # or: cd Decay
docker run -it -v "$(pwd):/diffusion" registry.gitlab.inria.fr/computix/computix/release:r26.03
```

Inside the container, build and run the simulation:

```
mkdir build
cd build
cmake ../src
make
./simulation --help
./simulation --output-dir .
```

The diffusion examples write `Voxels_%04d.vtp` and `Universes_%04d.xml` to the selected output directory. CellsAtCenter also writes `Cells_%04d.vtp`.

## Extracting and plotting results

From the selected example directory, parse one or more directories containing `Universes_*.xml` files. The parser writes a YAML file next to each input directory, using the directory name as the YAML filename:

```
python3 scripts/parse.py --dirs build
python3 scripts/plot.py --files build.yaml
```

Use `--help` for the available plotting options. The checked-in results in the [CellsAtCenter results](CellsAtCenter/results) and [Decay results](Decay/results) folders, and the corresponding figures in [CellsAtCenter figures](CellsAtCenter/figures) and [Decay figures](Decay/figures), show comparisons with the analytical solution.
