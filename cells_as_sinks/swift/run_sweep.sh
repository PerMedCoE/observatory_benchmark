#! /usr/bin/env bash

set -eu

if [ "$#" -ne 2 ]; then
  script_name=$(basename $0)
  echo "Usage: ${script_name} EXPERIMENT_ID INPUT (e.g. ${script_name} experiment_1 data/input.txt)"
  exit 1
fi


# uncomment to turn on swift/t logging. Can also set TURBINE_LOG,
# TURBINE_DEBUG, and ADLB_DEBUG to 0 to turn off logging
export TURBINE_LOG=1 TURBINE_DEBUG=1 ADLB_DEBUG=1
export EMEWS_PROJECT_ROOT=$( cd $( dirname $0 )/.. ; /bin/pwd )
# source some utility functions used by EMEWS in this script
source "${EMEWS_PROJECT_ROOT}/etc/emews_utils.sh"

export EXPID=$1
# export TURBINE_OUTPUT=$EMEWS_PROJECT_ROOT/experiments/$EXPID
export TURBINE_OUTPUT=/gpfs/scratch/bsc08/bsc008602/diffusion_official_results/$EXPID
check_directory_exists
# export TURBINE_SBATCH_ARGS=--qos=bsc_ls

# TODO edit the number of processes as required.
# export PROCS=768
export PROCS=384

# TODO edit QUEUE, WALLTIME, PPN, AND TURNBINE_JOBNAME
# as required. Note that QUEUE, WALLTIME, PPN, AND TURNBINE_JOBNAME will
# be ignored if the MACHINE variable (see below) is not set.
# export QUEUE=gp_debug
export QUEUE=gp_bscls
# gp_debug
export PROJECT=bsc08
# export WALLTIME=02:00:00
export WALLTIME=48:00:00
export PPN=24
export TURBINE_JOBNAME="${EXPID}_job"

# Extra argument passed to SLURM script
# options debug, bsc_ls
export TURBINE_SBATCH_ARGS=--qos=gp_bscls
export TURBINE_LAUNCHER="srun"

# if R cannot be found, then these will need to be
# uncommented and set correctly.
# export R_HOME=/path/to/R
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$R_HOME/lib
# if python packages can't be found, then uncommited and set this
# export PYTHONPATH=/path/to/python/packages
export PYTHONPATH=$EMEWS_PROJECT_ROOT/python


# TODO edit command line arguments as appropriate
# for your run. Note that the default $* will pass all of this script's
# command line arguments to the swift script.
mkdir -p $TURBINE_OUTPUT


EXECUTABLE_SOURCE=$EMEWS_PROJECT_ROOT/code/project
DEFAULT_XML_SOURCE=$EMEWS_PROJECT_ROOT/code/config/*
PARAMS_FILE_SOURCE=$2

EXECUTABLE_OUT=$TURBINE_OUTPUT/$(basename $EXECUTABLE_SOURCE)
DEFAULT_XML_OUT=$TURBINE_OUTPUT
PARAMS_FILE_OUT=$TURBINE_OUTPUT/$(basename $PARAMS_FILE_SOURCE)

cp $EXECUTABLE_SOURCE $EXECUTABLE_OUT
cp -r $DEFAULT_XML_SOURCE $DEFAULT_XML_OUT
cp $PARAMS_FILE_SOURCE $PARAMS_FILE_OUT

CMD_LINE_ARGS="$* -exe=$EXECUTABLE_OUT -settings=$DEFAULT_XML_OUT/PhysiCell_settings.xml -parameters=$PARAMS_FILE_OUT"
# /gpfs/scratch/bsc08/bsc008602/emews_diffusion/Physicell/Code/config/PhysiCell_settings.xml
# set machine to your schedule type (e.g. pbs, slurm, cobalt etc.),
# or empty for an immediate non-queued unscheduled run
MACHINE="slurm"

if [ -n "$MACHINE" ]; then
  MACHINE="-m $MACHINE"
fi

# Add any script variables that you want to log as
# part of the experiment meta data to the USER_VARS array,
# for example, USER_VARS=("VAR_1" "VAR_2")
USER_VARS=()
# log variables and script to to TURBINE_OUTPUT directory
log_script

# module load gcc R/3.4.0 python intel impi mkl java/8u131 swiftt/1.5.0 julia/1.8.3
# module load python java R/3.4.0 swiftt/1.5.0 # Running on MN4
# module load python java intel/2021.4.0 impi/2021.4.0 mkl/2021.4.0 R java/8u131 swiftt/1.5.0 # Running on Nord III
# module load python java intel impi mkl R/3.4.0 java/8u131 swiftt/1.5.0 # Running on MN4
# module load swig zsh/5.9 java-jdk/8u131 ant/1.10.14 hdf5 python/3.12.1 intel impi mkl R  swiftt/1.6.2-python-3.12.1   # Running on MN5
module load intel impi mkl swig zsh/5.9 java-jdk/8u131 ant/1.10.14 hdf5 python/3.12.1 R  swiftt/1.6.2-python-3.12.1
# module load ANACONDA/2021.11 java R/3.4.0 
# source activate SwiftT

#export PYTHONPATH=${PYTHONPATH}:$EMEWS_PROJECT_ROOT/python
export PYTHONPATH=$EMEWS_PROJECT_ROOT/python
# export R_HOME=${R_HOME}:$EMEWS_PROJECT_ROOT/R
export R_HOME=$EMEWS_PROJECT_ROOT/R



# echo's anything following this standard out
set -x
SWIFT_FILE=swift_run_sweep.swift
swift-t -n $PROCS $MACHINE -p $EMEWS_PROJECT_ROOT/swift/$SWIFT_FILE $CMD_LINE_ARGS
