#!/bin/bash
#SBATCH --job-name="physicell"
#SBATCH --workdir=.
#SBATCH --output=%j.out
#SBATCH --error=%j.err
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=48
#SBATCH --time=01:59:00
##SBATCH --time=00:03:00
#SBATCH --qos=debug

./heterogeneity config/PhysiCell_settings_1024.xml
