#!/bin/bash

# This script runs pushing test and moves the results to the
# correct folder.

# Retun if any command fails
set -e

# Check if BioDynaMo is sourced by checking if the environment variable
# BDMSYS is set
if [ -z "$BDMSYS" ]; then
    echo "BioDynaMo is not sourced. Please source BioDynaMo first."
    exit 1
fi

# Get the directory of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Go to the folder where the simulation is located
cd $DIR/code_scripts

# If the directories 'build' and 'output' exist, delete them
if [ -d "build" ]; then
    rm -r build
fi
if [ -d "output" ]; then
    rm -r output
fi

# If the directory 'results' does not exist, create it
if [ ! -d "$DIR/results" ]; then
    mkdir $DIR/results
else
    # If it exists, delete its contents
    rm -r $DIR/results/* 2>/dev/null || true
fi


# Run the simulation with single thread for reproducibility
export OMP_NUM_THREADS=1
bdm run

# Move the results to the correct folder
mv output/unit-test-mechanics-two-cells-hertz-relaxation/metadata $DIR/results
mv positions.csv $DIR/results
mv forces.csv $DIR/results
