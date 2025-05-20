#!/bin/bash

# filepath: generate_matrix.sh 
# This script generates a grid of points in 3D space with specified intervals.
# The output is formatted as CSV with four columns: x, y, z, and a constant value (0.0).
{
    for x in $(seq -110.0 20.0 110.0); do
        for y in $(seq -110.0 20.0 110.0); do
            for z in $(seq -110.0 20.0 110.0); do
                printf "%.1f,%.1f,%.1f,0.0\n" $x $y $z
            done
        done
    done
} > cells_20.csv

# filepath: generate_matrix.sh 
{
    for x in $(seq -110.0 40.0 110.0); do
        for y in $(seq -110.0 40.0 110.0); do
            for z in $(seq -110.0 40.0 110.0); do
                printf "%.1f,%.1f,%.1f,0.0\n" $x $y $z
            done
        done
    done
} > cells_40.csv

# filepath: generate_matrix.sh 
{
    for x in $(seq -115.0 10.0 115.0); do
        for y in $(seq -115.0 10.0 115.0); do
            for z in $(seq -115.0 10.0 115.0); do
                printf "%.1f,%.1f,%.1f,0.0\n" $x $y $z
            done
        done
    done
} > cells_10.csv

