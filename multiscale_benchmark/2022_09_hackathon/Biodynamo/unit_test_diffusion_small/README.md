# BDM small scale diffusion

This folder implements the small scale diffusion test. To run, you need to have
BioDynaMo sourced and be in the folder `code_scripts/diffusion-small`. Then,
simply execute `bdm run` in your terminal. You'll find the results in
`code_scripts/diffusion-small/output`.

Alternatively, execute the script `run.sh` which checks if BDM is sourced,
executes the simulation, and moves the results to the results directory.

## Known issues

* We do not have a convenient way to initialize the boundary different from
  the rest of the domain, thus we initialize the entire domain to `u_0 = 1`
  instead of to 0.
* The results in the folder `results/` have been taken on and Apple MacBook Pro
  with M1 chip
* As can be seen in the metadata, the export of the gird values is **by far**
  the most time consuming part.
