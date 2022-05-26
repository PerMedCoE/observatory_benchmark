#!/bin/bash

#SBATCH --job-name="timothy"
#SBATCH --qos=debug
#SBATCH --output=%j.out
#SBATCH --error=%j.err
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=48
#SBATCH -t 01:59:00


module load intel impi mkl sprng/2.0 zoltan/3.83 HYPRE/2.24.0 parmetis/4.0.3 gcc timothy boost/1.68.0 povray ffmpeg
srun -n 1 timothy -p run/parameters_bnch.txt
#cd "results_physicell"
#pwd
#/gpfs/projects/bsc08/PERMEDCOE/benchmarks/timothy/timothy-0.9/vis/povray.sh "/gpfs/projects/bsc08/PERMEDCOE/benchmarks/timothy/timothy-0.9/results_524288" 48
