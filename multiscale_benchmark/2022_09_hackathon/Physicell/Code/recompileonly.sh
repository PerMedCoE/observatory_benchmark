#!/bin/bash

# Check if an argument is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <unit_test>"
    exit 1
fi

# Assign the provided argument to the 'single_diffusion' variable
unit_test="$1"

# Remove files and directories
rm main.cpp
rm -r custom_modules/*
rm custom.o
rm project

# Copy configuration files and source code
cp -r "unit_tests/$unit_test/config/"* config/
cp -r "unit_tests/$unit_test/custom_modules/"* custom_modules/
cp "unit_tests/$unit_test/main.cpp" .

# Build the project
make
