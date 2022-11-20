# Tools for benchmarking boolean simulators

This repository contains a singularity definition (benchmark.def) which installs the various simulators to simplify the execution of benchmark.
To build this image, run : 
```
singularity build benchmark.sif benchmark.def
```

## Use case 1 : List reachable fixed points

The first use case performs a search of the existing fixed points of various models. 
To run this use case, use :

```
singularity exec benchmark.sif python3 fp.py <method> <model>
```

Implemented methods : maboss

Available models : 
- corral (https://link.springer.com/article/10.1186/s43556-021-00034-3)
- montagud (https://elifesciences.org/articles/72626)

Detailed usage of the use case : 
```
usage: fp.py [-h] [--condition CONDITION] [--iterations ITERATIONS] [--maxtime MAXTIME] [--nbcores NBCORES] [--replicates REPLICATES] method model

Parse script

positional arguments:
  method                the method used to search for fixed points
  model                 the model used in which to search the fixed points

options:
  -h, --help            show this help message and exit
  --condition CONDITION
                        the condition to simulate
  --iterations ITERATIONS
                        the number of iterations used in the method
  --maxtime MAXTIME     the duration of the simulation in the method
  --nbcores NBCORES     the number of cores used in the simulation of the method
  --replicates REPLICATES
                        the number of replicates of simulations
```
