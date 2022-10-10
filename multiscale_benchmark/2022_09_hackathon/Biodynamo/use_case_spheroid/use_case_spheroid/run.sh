#!/bin/bash

# This script runs the spheroid and moves the results to the
# correct folder.

# Retun if any command fails
set -e

cd /gpfs/projects/bsc08/shared_projects/PerMedCoE/Benchmarks/biodynamo_benchmark/container/barcelona
export PATH="/gpfs/projects/bsc08/shared_projects/PerMedCoE/Benchmarks/biodynamo_benchmark/container/barcelona/usr/bin:$PATH"
source /gpfs/projects/bsc08/shared_projects/PerMedCoE/Benchmarks/biodynamo_benchmark/container/barcelona/biodynamo/build/bin/thisbdm.sh

# Check if BioDynaMo is sourced by checking if the environment variable
# BDMSYS is set
if [ -z "$BDMSYS" ]; then
    echo "BioDynaMo is not sourced. Please source BioDynaMo first."
    exit 1
fi

# Get the directory of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Go to the folder where the simulation is located
cd $DIR/code_scripts/spheroid

# Run the simulation
./build/spheroid

# Move the results to the correct folder
mv output/spheroid/metadata $DIR/results
[ -f output/spheroid/time-series-data.json ] && \
  mv output/spheroid/time-series-data.json $DIR/results
[ -f output/spheroid/spheroid.png ] && \
  mv output/spheroid/spheroid.png $DIR/results
[ -f output/spheroid/spheroid.svg ] && \
  mv output/spheroid/spheroid.svg $DIR/results
