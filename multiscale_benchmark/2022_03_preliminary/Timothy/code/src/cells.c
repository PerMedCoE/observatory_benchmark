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
#include <mpi.h>
#include <math.h>
#include <inttypes.h>
#include <sprng.h>

#include "global.h"
#include "inline.h"
#include "fields.h"

/*! \file cells.c
 *  \brief contains functions which control current states and evolution of cells 
 */

unsigned char *celld;

/*!
 * This function checks whether the cell p is outside the computational box.
 */
static inline int outsideTheBox(int p)
{
  double x, y, z, r;

  x = cells[p].x;
  y = cells[p].y;
  z = cells[p].z;
  r = cells[p].size;

  if (x - r < 0 || x + r > (double) nx)
    return 1;
  if (y - r < 0 || y + r > (double) ny)
    return 1;
  if (sdim == 3 && (z - r < 0 || z + r > (double) nz))
    return 1;

  return 0;
}

/*!
 * This function allocates tables responsible for carrying 
 * informations about cells, their current state and evolution.
 */
void cellsAllocate()
{

  int i, j, c, f;
  int64_t cellsActualSize;

  if (sdim == 2)
    csize = (nx / 2) / pow(8.0 * maxCells, 1.0 / 2.0);
  if (sdim == 3)
    csize = (nx / 2) / pow(8.0 * maxCells, 1.0 / 3.0);

  maxCellsPerProc = 1.5 * maxCells / MPIsize;

  cellsActualSize = maxCellsPerProc * sizeof(struct cellData);

  localID = 0;

  if (!(cells = (struct cellData *) malloc(cellsActualSize)))
    stopRun(106, "cells", __FILE__, __LINE__);

  if (!
      (velocity =
       (struct doubleVector3d *) malloc(maxCellsPerProc *
					sizeof(struct doubleVector3d))))
    stopRun(106, "velocity", __FILE__, __LINE__);

  cellFields = (double **) malloc(NFIELDS * sizeof(double *));
  for (f = 0; f < NFIELDS; f++)
    if (!
	(cellFields[f] =
	 (double *) malloc(maxCellsPerProc * sizeof(double))))
      stopRun(106, "cellFields", __FILE__, __LINE__);

  if (!(tlnc = (int64_t *) calloc(MPIsize, sizeof(int64_t))))
    stopRun(106, "tlnc", __FILE__, __LINE__);

}

/*!
 * This function initializes counters of cells in various cell phases.
 */
void cellsCycleInit()
{
  /* global numbers of cells */
  g0nc = nc;
  g1nc = 0;
  snc = 0;
  g2nc = 0;
  mnc = 0;
  cnc = 0;
  /* local numbers of cells */
  lg0nc = lnc;
  lg1nc = 0;
  lsnc = 0;
  lg2nc = 0;
  lmnc = 0;
  lcnc = 0;
  lnnc = 0;
  /* number of cancer cells */
  cancer = 0;
}

/*!
 * This function initializes cell data.
 * Locations of cells in space are generated randomly.
 */
int cellsRandomInit()
{

  int i, j;

  /* uniform distribution */
  if (!strcmp(rng, "UNB")) {
    double D;

    if (sdim == 2)
      csize = (nx / 2) / pow(8.0 * maxCells, 1.0 / 2.0);
    if (sdim == 3)
      csize = (nx / 2) / pow(8.0 * maxCells, 1.0 / 3.0);
    if (sdim == 2)
      D = csize * pow(8.0 * nc, 1.0 / 2.0);
    if (sdim == 3)
      D = csize * pow(8.0 * nc, 1.0 / 3.0);

    h = 3.0 * csize;
    simTime = 0;

    for (i = 0; i < lnc; i++) {
      cells[i].x = D * (sprng(stream) * 2 - 1);
      cells[i].y = D * (sprng(stream) * 2 - 1);
      if (sdim == 3)
	cells[i].z = D * (sprng(stream) * 2 - 1);
      else
	cells[i].z = 0.0;

      cells[i].x += nx / 2;
      cells[i].y += nx / 2;
      if (sdim == 3)
	cells[i].z += nx / 2;
      else
	cells[i].z = 0.0;

      cells[i].size = pow(2.0, -(1.0 / 3.0)) * csize;
      cells[i].gid =
	  (unsigned long long int) MPIrank *(unsigned long long int)
	  maxCellsPerProc + (unsigned long long int) i;
      cells[i].v = 0.0;
      cells[i].density = 0.0;
      cells[i].h = h;
      cells[i].young = 2100.0 + sprng(stream) * 100.0;
      cells[i].halo = 0;
      cells[i].phase = 0;
      cells[i].g1 = g1 * (1 + (sprng(stream) * 2 - 1) * v);
      cells[i].g2 = g2 * (1 + (sprng(stream) * 2 - 1) * v);
      cells[i].s = s * (1 + (sprng(stream) * 2 - 1) * v);
      cells[i].m = m * (1 + (sprng(stream) * 2 - 1) * v);
      cells[i].phasetime = 0.0;
      cells[i].age = 0;
      cells[i].death = 0;
      cells[i].tumor = 0;
      localID++;
    }
  }
  /* normal distribution (Box-Muller transform) */
  if (!strcmp(rng, "BM")) {
    double x1, x2, x3;
    double z1, z2, z3;
    double r1, r2;
    double l;
    double D;
    if (sdim == 2)
      csize = (nx / 2) / pow(8.0 * maxCells, 1.0 / 2.0);
    if (sdim == 3)
      csize = (nx / 2) / pow(8.0 * maxCells, 1.0 / 3.0);
    if (sdim == 2)
      D = csize * pow(8.0 * nc, 1.0 / 2.0);
    if (sdim == 3)
      D = csize * pow(8.0 * nc, 1.0 / 3.0);

    h = 3.0 * csize;
    simTime = 0;

    for (i = 0; i < lnc; i++) {

      r2 = 1.1;

      while (r2 >= 1.0) {
	r1 = 1.1;
	while (r1 == 0 || r1 >= 1.0) {
	  x1 = sprng(stream) * 2 - 1;
	  x2 = sprng(stream) * 2 - 1;
	  x3 = sprng(stream) * 2 - 1;
	  r1 = x1 * x1 + x2 * x2 + x3 * x3;
	}
	l = sqrt(-2 * log(r1) / r1);
	z1 = x1 * l;
	z2 = x2 * l;
	z3 = x3 * l;

	r2 = z1 * z1 + z2 * z2 + z3 * z3;
      }

      cells[i].x = z1 * D + nx / 2;
      cells[i].y = z2 * D + nx / 2;
      if (sdim == 3)
	cells[i].z = z3 * D + nx / 2;
      else
	cells[i].z = 0.0;

      cells[i].size = pow(2.0, -(1.0 / 3.0)) * csize;
      cells[i].gid =
	  (unsigned long long int) MPIrank *(unsigned long long int)
	  maxCellsPerProc + (unsigned long long int) i;
      cells[i].v = 0.0;
      cells[i].density = 0.0;
      cells[i].h = h;
      cells[i].young = 2100.0 + sprng(stream) * 100.0;
      cells[i].halo = 0;
      cells[i].phase = 0;
      cells[i].g1 = g1 * (1 + (sprng(stream) * 2 - 1) * v);
      cells[i].g2 = g2 * (1 + (sprng(stream) * 2 - 1) * v);
      cells[i].s = s * (1 + (sprng(stream) * 2 - 1) * v);
      cells[i].m = m * (1 + (sprng(stream) * 2 - 1) * v);
      cells[i].phasetime = 0.0;
      cells[i].tumor = 0;
      cells[i].age = 0;
      cells[i].death = 0;
      localID++;
    }
  }

  /* powers of h are calculated only once here */
  h2 = h * h;
  h3 = h2 * h;
  h4 = h3 * h;
}

/*!
 * This function implements mitosis of cells.
 */
void mitosis(int c)
{

  double sc;
  double shift[3];

  if (lnc + 1 > maxCellsPerProc)
    stopRun(109, NULL, __FILE__, __LINE__);

  sc = sqrt(velocity[c].x * velocity[c].x + velocity[c].y * velocity[c].y +
	    velocity[c].z * velocity[c].z);

  /* daughter cells are shifted away from the center of parent cell */
  if (sc > 0 && mitrand == 0) {	/* direction of shift related to velocity vector */
    sc = cells[c].size / (2 * sc);
    shift[0] = sc * velocity[c].x;
    shift[1] = sc * velocity[c].y;
    if (sdim == 3)
      shift[2] = sc * velocity[c].z;
    else
      shift[2] = 0.0;
  } else {			/* direction of shift chosen randomly */
    int accept = 0;
    while (accept == 0) {
      shift[0] = sprng(stream) * 2.0 - 1.0;
      shift[1] = sprng(stream) * 2.0 - 1.0;
      if (sdim == 3)
	shift[2] = sprng(stream) * 2.0 - 1.0;
      else
	shift[2] = 0.0;
      sc = sqrt(pow(shift[0], 2) + pow(shift[1], 2) + pow(shift[2], 2));
      if (sc == 0)
	continue;
      sc = cells[c].size / (2 * sc);
      shift[0] = sc * shift[0];
      shift[1] = sc * shift[1];
      shift[2] = sc * shift[2];
      accept = 1;
    }
  }
  /* 1st daughter cell position, size, type and age */
  cells[lnc].x = cells[c].x + shift[0];
  cells[lnc].y = cells[c].y + shift[1];
  cells[lnc].z = cells[c].z + shift[2];
  cells[lnc].size = pow(2.0, -(1.0 / 3.0)) * cells[c].size;;
  cells[lnc].tumor = cells[c].tumor;
  cells[lnc].age = cells[c].age + 1;

  /* 2nd daughter cell position, size, type and age */
  cells[c].x -= shift[0];
  cells[c].y -= shift[1];
  cells[c].z -= shift[2];
  cells[c].size = cells[lnc].size;;
  cells[c].age += 1;

  /* 2nd daughter cell cycle phases lenghts */
  if (cells[c].tumor == 1) {
    cells[c].g1 = cg1 * (1 + (sprng(stream) * 2 - 1) * v);
    cells[c].g2 = cg2 * (1 + (sprng(stream) * 2 - 1) * v);
    cells[c].s = cs * (1 + (sprng(stream) * 2 - 1) * v);
    cells[c].m = cm * (1 + (sprng(stream) * 2 - 1) * v);
  } else {
    cells[c].g1 = g1 * (1 + (sprng(stream) * 2 - 1) * v);
    cells[c].g2 = g2 * (1 + (sprng(stream) * 2 - 1) * v);
    cells[c].s = s * (1 + (sprng(stream) * 2 - 1) * v);
    cells[c].m = m * (1 + (sprng(stream) * 2 - 1) * v);
  }
  /* 1st daughter cell global ID */
  cells[lnc].gid =
      (unsigned long long int) MPIrank *(unsigned long long int)
      maxCellsPerProc + (unsigned long long int) lnc;

  /* 1st daughter cell parameters */
  cells[lnc].v = 0.0;
  cells[lnc].density = cells[c].density;
  cells[lnc].h = h;
  cells[lnc].young = 2100.0 + sprng(stream) * 100.0;
  cells[lnc].halo = 0;
  cells[lnc].phase = 1;
  cells[lnc].death = 0;
  cells[lnc].phasetime = 0.0;
  /* 1st daughter cell cycle phases lenghts */
  if (cells[lnc].tumor == 1) {
    cells[lnc].g1 = cg1 * (1 + (sprng(stream) * 2 - 1) * v);
    cells[lnc].g2 = cg2 * (1 + (sprng(stream) * 2 - 1) * v);
    cells[lnc].s = cs * (1 + (sprng(stream) * 2 - 1) * v);
    cells[lnc].m = cm * (1 + (sprng(stream) * 2 - 1) * v);
  } else {
    cells[lnc].g1 = g1 * (1 + (sprng(stream) * 2 - 1) * v);
    cells[lnc].g2 = g2 * (1 + (sprng(stream) * 2 - 1) * v);
    cells[lnc].s = s * (1 + (sprng(stream) * 2 - 1) * v);
    cells[lnc].m = m * (1 + (sprng(stream) * 2 - 1) * v);
  }

  /* update local cell counters */
  if (cells[lnc].tumor == 1)
    lcnc += 1;
  lnc = lnc + 1;
  lg1nc += 1;
  /* increment local ID */
  localID++;

}

/*!
 * This function finds locates cell closest to the center of mass of the system
 * and marks this cell as a cancer cell.
 */
void markMiddleCancerCell()
{
  int c;
  int middle = 0;
  double dist;
  struct {
    double val;
    int rank;
  } lmdist, gmdist;
  double center[3];
  double gcenter[3];

  /* each process computes its local center of mass */
  center[0] = 0.0;
  center[1] = 0.0;
  center[2] = 0.0;
  for (c = 0; c < lnc; c++) {
    center[0] += cells[c].x / nc;
    center[1] += cells[c].y / nc;
    center[2] += cells[c].z / nc;
  }

  /* MPI Reduce operation computes global center of mass */
  MPI_Allreduce(center, gcenter, 3, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

  /* intialization */
  lmdist.rank = MPIrank;
  lmdist.val = INT_MAX;

  /* each process finds local cell closest to the global center of mass */
  for (c = 0; c < lnc; c++) {
    dist =
	sqrt((cells[c].x - gcenter[0]) * (cells[c].x - gcenter[0]) +
	     (cells[c].y - gcenter[1]) * (cells[c].y - gcenter[1]) +
	     (cells[c].z - gcenter[2]) * (cells[c].z - gcenter[2]));
    if (dist < lmdist.val) {
      lmdist.val = dist;
      middle = c;
    }
  }

  /* MPI_Allreduce locates the cell closest to the global center of mass */
  MPI_Allreduce(&lmdist, &gmdist, 1, MPI_DOUBLE_INT, MPI_MINLOC,
		MPI_COMM_WORLD);
  /* mark the found cell as cancer one */
  if (MPIrank == gmdist.rank) {
    cells[middle].tumor = 1;
    cells[middle].phase = 1;
    lg0nc--;
    lg1nc++;
    lcnc++;
  }

  /* indicate that there is a cancer cell in the system */
  cancer = 1;
}

/*!
 * This function dealocates all tables allocated during initialization of cell data
 */
void cellsCleanup()
{
  int f;
  free(tlnc);
  free(cells);
  for (f = 0; f < NFIELDS; f++)
    free(cellFields[f]);
  free(cellFields);
  free(velocity);
}

/*!
 * This function removes a dead cell from the simulation.
 */
void cellsDeath(int lnc_old)
{
  int c, pos;

  pos = 0;
  for (c = 0; c < lnc; c++) {
    /* shift cells after dead cell removal */
    if (c >= lnc_old) {
      cells[pos] = cells[c];
      pos++;
      continue;
    }
    if (c != pos && celld[c] == 0)
      cells[pos] = cells[c];
    if (celld[c] == 0)
      pos++;
    /* update cell counters */
    if (celld[c] == 1) {
      switch (cells[c].phase) {
      case 0:
	lg0nc--;
	break;
      case 1:
	lg1nc--;
	break;
      case 2:
	lsnc--;
	break;
      case 3:
	lg2nc--;
	break;
      case 4:
	lmnc--;
	break;
      }
      if (cells[c].tumor == 1)
	lcnc--;
    }
  }
  lnc -= rsum;
}

/*!
 * This function updates cell counters.
 */
void updateCellCounters()
{
  MPI_Allgather(&lnc, 1, MPI_INT64_T, tlnc, 1, MPI_INT64_T,
		MPI_COMM_WORLD);
  MPI_Allreduce(localCellCount, totalCellCount, numberOfCounts,
		MPI_INT64_T, MPI_SUM, MPI_COMM_WORLD);
}

/*!
 * This function updates cells' positions.
 */
void updateCellPositions()
{
  int c;
#ifdef DEBUG
  if (MPIrank == 0 && !(step % statOutStep)) {
    printf(" Cells movement...");
    fflush(stdout);
  }
#endif
  if ((statistics.mindist >= 0.95 * 2.0 * pow(2.0, -(1.0 / 3.0)) * csize
       && simStart == 0) || (nc == 1 && simStart == 0)) {
    simStart = 1;
    if (MPIrank == 0)
      printf("\nSimulation started.\n");
  }

  /* move cells */
  for (c = 0; c < lnc; c++) {
    cells[c].x += velocity[c].x;
    cells[c].y += velocity[c].y;
    cells[c].z += velocity[c].z;
    // Mark cells that are out of the box and need to be removed
    //if(outside_the_box(c)) { celld[c]=1; rsum++; }
  }
#ifdef DEBUG
  if (MPIrank == 0 && !(step % statOutStep))
    printf("done\n");
#endif
}

/*!
 * This function updates cells' cycle phases.
 */
int updateCellCycles()
{

  int c;
  double eps, epsCancer;
  int lncAtThisStep;

  eps = densityCriticalLevel1;
  epsCancer = densityCriticalLevel2;

  lncAtThisStep = lnc;

  for (c = 0; c < lncAtThisStep; c++) {

    if (outsideTheBox(c)) {
      celld[c] = 1;
      rsum++;
      continue;
    }

    if (celld[c])
      continue;

    if (simStart) {

      if (cells[c].phase != 0
	  && ((cells[c].tumor == 0 && cells[c].density <= eps)
	      || (cells[c].tumor == 1 && cells[c].density <= epsCancer)))
	cells[c].phasetime += gfDt / 3600.0;

      switch (cells[c].phase) {

      case 0:			/* G0 phase */
	if (gfields && oxygen
	    && cellFields[OXYG][c] < fieldCriticalLevel2[OXYG]) {
	  cells[c].phase = 5;
	  cells[c].phasetime = 0;
	  lg0nc--;
	  lnnc++;
	  break;
	}
	/* transition to G1 phase */
	if ((cells[c].tumor == 0 && cells[c].density <= eps) ||	/* enough space for healthy cell */
	    (cells[c].tumor == 1 && cells[c].density <= epsCancer) ||	/* enough space for tumor cell */
	    nc == 1 ||		/* only single cell in the simulation */
	    (gfields && oxygen && cellFields[OXYG][c] >= fieldCriticalLevel1[OXYG])) {	/* sufficient level of oxygen */
	  cells[c].phase = 1;
	  lg0nc--;
	  lg1nc++;
	  break;
	}
	break;
      case 1:			/* G1 phase */
	/* transition to G0 or Necrotic phase */
	if ((cells[c].tumor == 0 && cells[c].density > eps) ||	/* too crowdy for healthy cell */
	    (cells[c].tumor == 1 && cells[c].density > epsCancer) ||	/* too crowdy for tumor cell */
	    (gfields && oxygen && cellFields[OXYG][c] < fieldCriticalLevel1[OXYG])) {	/* too low oxygen level */
	  if (gfields && oxygen && cellFields[OXYG][c] < fieldCriticalLevel2[OXYG]) {	/* transition to Necrotic phase */
	    cells[c].phase = 5;
	    cells[c].phasetime = 0;
	    lg1nc--;
	    lnnc++;
	  } else {		/* transition to G0 phase */
	    cells[c].phase = 0;
	    lg1nc--;
	    lg0nc++;
	  }
	  break;
	}
	/* cells grow in phase G1 */
	if (cells[c].size < csize) {
	  cells[c].size +=
	      (csize -
	       pow(2.0,
		   -(1.0 / 3.0)) * csize) * (gfDt) / (3600.0 *
						      cells[c].g1);
	}
	if (cells[c].size > csize)
	  cells[c].size = csize;
	if (cells[c].phasetime >= cells[c].g1) {
	  int death;
	  cells[c].phase = 2;
	  cells[c].phasetime = 0;
	  lg1nc--;
	  lsnc++;
	  if (cells[c].tumor == 0) {
	    death = (sprng(stream) < rd ? 1 : 0);
	    if (death) {
	      celld[c] = 1;
	      rsum++;
	    }
	  }
	}
	break;
      case 2:			/* S phase */
	if (gfields && oxygen
	    && cellFields[OXYG][c] < fieldCriticalLevel2[OXYG]) {
	  cells[c].phase = 5;
	  cells[c].phasetime = 0;
	  lsnc--;
	  lnnc++;
	  break;
	}
	if (cells[c].phasetime >= cells[c].s) {
	  cells[c].phase = 3;
	  cells[c].phasetime = 0;
	  lsnc--;
	  lg2nc++;
	  break;
	}
	break;
      case 3:			/* G2 phase */
	if (gfields && oxygen
	    && cellFields[OXYG][c] < fieldCriticalLevel2[OXYG]) {
	  cells[c].phase = 5;
	  cells[c].phasetime = 0;
	  lg2nc--;
	  lnnc++;
	  break;
	}
	if (cells[c].phasetime >= cells[c].g2) {
	  int death;
	  cells[c].phase = 4;
	  cells[c].phasetime = 0;
	  lg2nc--;
	  lmnc++;
	  if (cells[c].tumor == 0) {
	    death = (sprng(stream) < rd ? 1 : 0);
	    if (death) {
	      celld[c] = 1;
	      rsum++;
	    }
	  }
	  break;
	}
	break;
      case 4:			/* M phase */
	if (gfields && oxygen
	    && cellFields[OXYG][c] < fieldCriticalLevel2[OXYG]) {
	  cells[c].phase = 5;
	  cells[c].phasetime = 0;
	  lmnc--;
	  lnnc++;

	} else if (cells[c].phasetime >= cells[c].m) {
	  mitosis(c);
	  cells[c].phase = 1;
	  cells[c].phasetime = 0;
	  lmnc--;
	  lg1nc++;
	}
	break;
      }				// switch
    }				// if
  }				// for loop

  /* update global number of cells */
  MPI_Allreduce(&lnc, &nc, 1, MPI_INT64_T, MPI_SUM, MPI_COMM_WORLD);

}

/*!
 * This function fills the scalarOutput field of each cell.
 * It can be modified to output any float scalars that 
 * user would like to analyze or visualize after simulation.
 * This field is printed to the output VTK files.
 */
void additionalScalarField()
{
  int c;
  for (c = 0; c < lnc; c++) {
    if (cells[c].tumor == 1)
      cells[c].scalarField = 8.0;
    else
      cells[c].scalarField = cells[c].density;
  }
}

/*!
 * This function drives the whole cell cycle update.
 */
void updateCellStates()
{
  int lnc_old;
  /* number of local cells might change during the update */
  lnc_old = lnc;
  celld = (unsigned char *) calloc(lnc_old, sizeof(unsigned char));
  rsum = 0;

  updateCellCycles();
  if (nhs > 0 && nc > nhs && tgs == 1 && cancer == 0)
    markMiddleCancerCell();
  if (nhs > 0 && nc > nhs)
    cellsDeath(lnc_old);
  updateCellCounters();
  additionalScalarField();
  free(celld);
}
