/* **************************************************************************
 * This file is part of Timothy
 *
 * Copyright (c) 2014/15 Maciej Cytowski
 * Copyright (c) 2014/15 ICM, University of Warsaw, Poland
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * *************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>
#include<omp.h>

#include "global.h"

/*! \file main.c
 *  \brief contains the main simulation loop
 */

/*!   
 * This function intializes MPI, calls Timothy initialization and allocation functions. 
 * It also contains the main simulation loop where all important simulation steps are called. 
*/

int main(int argc, char **argv)
{

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &MPIsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &MPIrank);

  OMPthreads = omp_get_max_threads();

  simulationInit(argc, argv);

  for (step = 0; step < nsteps; step++) {

    if (!(step % statOutStep))
      printStepNum();

    decompositionExecute();
    treeBuild();
    createExportList();
    initCellsToGridExchange();
    computePotential();
    computePotentialGradient();

    waitCellsToGridExchange();
    fieldsSolve();
    interpolateFieldsToCells();

    if (!(step % statOutStep))
      statisticsPrint();

    if (simStart)
      simTime += secondsPerStep / 3600.0;	/* biological process time in hours */

    if (!(step % vtkOutStep)) {
      if (vtkout)
	ioWriteStepVTK(step);
      if (povout)
	ioWriteStepPovRay(step, 0);
      if (vnfout)
	ioWriteFields(step);
    }

    updateCellPositions();
    updateCellStates();
    commCleanup();
    treeFree();

    if (!(step % rstOutStep))
      saveRstFile();
  }

  MPI_Barrier(MPI_COMM_WORLD);

  decompositionFinalize();
  randomStreamFree();
  cellsCleanup();

  if (MPIrank == 0)
    printf("\nEnd of simulation run.\n");

  MPI_Finalize();

  return 0;
}
