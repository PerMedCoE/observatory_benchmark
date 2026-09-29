This zip folder contains the raw data files for the plots for the diffusion decay and uptake tests.

The files are split into two types. The number at the end of the file name shows resolution of the simulation (6 = 6x6x6, 12 = 12x12x12, etc).


- data files
Column 1 = Time (seconds)
Column 2 = Average concentration across the domain (uM)
column 3 = Concentration of central voxel in domain (uM)
All files contain a 10000 rows, so each timestep represents 0.0001 seconds.


- Contour files
Array of concentration values (uM) in each voxel across the x-y plane centered at z=0. Generated at the end of the simulation (T = 10 seconds).

Concentration value at position (0,0) (top left) in the array represents concentration at x = -120 um and y = -120 um in the domain.

As the resolution increase, so does the array. For example "contour_6.csv" shows the 6x6x6 resolution simulation so the array is 6x6.
