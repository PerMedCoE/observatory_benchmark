#!/bin/bash

module load gcc/8.1.0
# module switch impi openmpi/3.1.1

make heterogeneity-benchmark
make


# make clean; make data-cleanup; make reset
