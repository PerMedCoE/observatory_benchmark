# BDM 1k Cells Diffusion

This folder implements the 1k cells diffusion test. To run, you need to have
BioDynaMo sourced and be in this folder: `unit_test_diffusion_1k`. Then,
simply execute `bdm run` in your terminal. Running this will output the data to 
a csv file called `data.csv` in the current directory (not in the output directory).
This file contains two columns aranged: time (minutes) | average concentration across
all voxels. You can then run `python plot.py` to get a graph of the data against 
average concentration across all voxels. 
