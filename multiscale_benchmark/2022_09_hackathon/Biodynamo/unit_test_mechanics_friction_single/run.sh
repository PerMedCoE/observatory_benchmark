#!/bin/bash

# This script runs the mechanics friction single unit test and moves the results
# to the correct folder.


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

# Create the results dir if it does not exist yet
RESULTS=$DIR/results
if [ ! -d "$RESULTS" ]; then
    mkdir $RESULTS
fi

# Move the results to the correct folder
mv positions.csv $RESULTS
mv output/unit-test-mechanics/metadata $DIR/results
