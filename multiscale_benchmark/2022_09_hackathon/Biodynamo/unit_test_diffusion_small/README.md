# BDM Small Scale Diffusion

This folder implements the small scale diffusion test. To run, you need to have
BioDynaMo sourced and be in this folder: `unit_test_diffusion_small`. Then,
simply execute `bdm run` in your terminal. Running this will output the data to 
a csv file called `data.csv` in the current directory (not in the output directory).
You can then run `python plot.py` to get a graph of the data against concentration in
central voxel. 
