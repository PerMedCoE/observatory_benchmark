# BDM chemotaxis

This folder implements the small scale diffusion test. To run, you need to have 
BioDynaMo sourced and be in the folder `code_scripts/chemotaxis`. Then, 
simply execute `bdm run` in your terminal. You'll find the results in 
`code_scripts/chemotaxis/output`.

Alternatively, execute the script `run.sh` which checks if BDM is sourced, 
executes the simulation, and moves the results to the results directory.

## Known issues

* The results in the folder `results/` have been taken on and Apple MacBook Pro
  with M1 chip

## Performance

The CSV export has been hacked together for this event and is very slow. Please
set the flag `export_to_csv = false` in the header file.

