#!/bin/bash

# This script runs the monolayer use case and moves the results to the
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

# If the directories `build` and `output` exist, delete them
if [ -d "build" ]; then
    rm -r build
fi
if [ -d "output" ]; then
    rm -r output
fi

# Run the simulation
bdm run

# Move the results to the correct folder
mv output/sphere/metadata $DIR/results
mv $DIR/code_scripts/*.csv $DIR/results
mv $DIR/code_scripts/output/result.svg $DIR/results
mv $DIR/code_scripts/output/result.C $DIR/results
mv $DIR/code_scripts/output/result.root $DIR/results
