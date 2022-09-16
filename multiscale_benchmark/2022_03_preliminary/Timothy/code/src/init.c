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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "global.h"
#include "inline.h"

/*! \file init.c
 *  \brief contains initialization functions
 */

/*!   
 * This function sets default values for the simulation.
*/
void defaultValues()
{
  rst = 0;
  rstReset = 0;
  nhs = -1;
  tgs = 0;

  statOutStep = 1;
  rstOutStep = 1;
  vtkOutStep = 1;

  povout = 0;
  vtkout = 0;
  vnfout = 0;

  csizeInUnits = 10.0;		/* eukaryotic cell size is usually between 10-30 micrometers */
  cellVolume = (4.0 / 3.0) * M_PI * pow(csizeInUnits * 0.0001, 3.0);

}

/*!
 * This functions checks the consistence of key simulation parameters.
*/
void checkParameters()
{
  /* under construction */
  if (strcmp(cOutType, "VTK") && strcmp(cOutType, "POV")
      && strcmp(cOutType, "NON"))
    stopRun(116, "COUTTYPE", __FILE__, __LINE__);
  if (strcmp(fOutType, "VNF") && strcmp(fOutType, "NON"))
    stopRun(116, "FOUTTYPE", __FILE__, __LINE__);
}

/*!   
 * This function intializes the simulation by setting all most important simulation parameters. 
*/
void simulationInit(int argc, char **argv)
{
  int i;
  int periods[3];
  int reorder;

  /* print basic informations */
  printBasicInfo();

  /* check necessary arguments */
  //if( (argc<3 || (strcmp(argv[1],"-p"))) || (argc<2 || (strcmp(argv[1],"-h"))) )
  //  stopRun(102,NULL,__FILE__,__LINE__);

  if (argc < 2)
    stopRun(102, NULL, __FILE__, __LINE__);
  else if ((argc < 3 && strcmp(argv[1], "-p") == 0)
	   || (strcmp(argv[1], "-p") && strcmp(argv[1], "-h")))
    stopRun(102, NULL, __FILE__, __LINE__);

  initParams();

  if (strcmp(argv[1], "-h") == 0)
    printHelp();

  /* check number of processes */
  if (!POWER_OF_TWO(MPIsize))
    stopRun(101, NULL, __FILE__, __LINE__);

  /* checking system and runtime configuration */
  checkEndiannes();
  getLocalRankAndSize(MPIrank, MPIsize, &MPINodeRank, &MPINodeSize);
  memPerProc = getMemoryPerProcess(MPINodeSize);

  /* print execution informations */
  printExecInfo();

  /* set default values */
  defaultValues();

  /* initialize random number generator */
  randomStreamInit();

  /* read parameters file and restart file (if present) */
  readParams(argc, argv);

  /* generate random cells if not a restart simulation */
  if (!rst) {
    simStart = 0;
    /* calculating number of cells per process */
    lnc = nc / MPIsize;
    if (MPIrank < nc % MPIsize)
      lnc++;
    /* allocating tables */
    cellsAllocate();
    /* total number of cells - initialization */
    for (i = 0; i < MPIsize; i++)
      tlnc[i] = lnc;		//ZLE!!!!!
    /* cell cycle init */
    cellsCycleInit();
    /* random cell placement */
    cellsRandomInit();
    /* decomposition - initialization */
    decompositionInit(argc, argv, MPI_COMM_WORLD);
  }

  /* maximum distance cell can travel in 1 sec */
  maxSpeedInUnits = (maxSpeed * csize) / (24.0 * 60.0 * 60.0);
  /* at least one global fields iteration per step */
  gfDt = (gfDt > secondsPerStep ? secondsPerStep : gfDt);
  /* global fields iterations per step */
  gfIterPerStep = (int) (secondsPerStep / gfDt);

  /* density critical levels (very important parameters) */
  if (sdim == 3) {
    densityCriticalLevel1 = 6 * h3 * sph_kernel(1.5 * csize);	//1.8  //1.4 //1.75
    densityCriticalLevel2 = 6 * h3 * sph_kernel(1.1 * csize);	//1.1 //1.4
  }
  if (sdim == 2) {
    densityCriticalLevel1 = 4 * h2 * sph_kernel(1.4 * csize);	//1.4 //1.75
    densityCriticalLevel2 = 4 * h2 * sph_kernel(1.15 * csize);	//1.1 //1.4
  }

  /* checking the consistency */
  checkParameters();

  if (!strcmp(cOutType, "POV"))
    povout = 1;
  if (!strcmp(cOutType, "VTK"))
    vtkout = 1;
  if (!strcmp(fOutType, "VNF"))
    vnfout = 1;

  /* organizing processes in a Cartesian grid for global fields computations */
  MPI_Dims_create(MPIsize, sdim, MPIdim);
  periods[0] = 0;
  periods[1] = 0;
  periods[2] = 0;
  reorder = 0;
  MPI_Cart_create(MPI_COMM_WORLD, sdim, MPIdim, periods, reorder,
		  &MPI_CART_COMM);
  MPIcoords = (int **) malloc(MPIsize * sizeof(int *));
  for (i = 0; i < MPIsize; i++) {
    MPIcoords[i] = (int *) malloc(3 * sizeof(int));
    MPI_Cart_coords(MPI_CART_COMM, i, sdim, MPIcoords[i]);
  }
  /* compute grid size */
  computeGridSize();

  /* allocate grid data */
  allocateGrid();
  /* initialize global fields (might take some time) */
  fieldsInit();

  /* define colormaps for PovRay outputs */
  defineColormaps();

  /* define vessels - TBD */
  //initVessel();
}
