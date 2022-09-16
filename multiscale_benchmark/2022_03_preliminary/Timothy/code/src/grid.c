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
#include <math.h>
#include <inttypes.h>

#include "global.h"
#include "fields.h"

/*! \file grid.c
 *  \brief contains functions that build the computational grid
 */

/*!
 * This function computes the sizes of the grid.
 */
void computeGridSize()
{
  gridResolution = csize * gfH;
  boxVolume = pow((gridResolution / csize) * csizeInUnits * 0.0001, 3);
  lowerGridCorner.x = 0.0;
  lowerGridCorner.y = 0.0;
  lowerGridCorner.z = 0.0;
  upperGridCorner.x = (double) nx - 1;
  upperGridCorner.y = (double) ny - 1;
  upperGridCorner.z = (double) nz - 1;


  globalGridSize.x = upperGridCorner.x - lowerGridCorner.x + 1;
  globalGridSize.y = upperGridCorner.y - lowerGridCorner.y + 1;
  globalGridSize.z = upperGridCorner.z - lowerGridCorner.z + 1;

  gridI = (int64_t) ((globalGridSize.x + 1) / gridResolution);
  gridJ = (int64_t) ((globalGridSize.y + 1) / gridResolution);
  if (sdim == 3)
    gridK = (int64_t) ((globalGridSize.z + 1) / gridResolution);
  else
    gridK = 0;

  gridI = gridI + (MPIdim[0] - gridI % MPIdim[0]);
  gridJ = gridJ + (MPIdim[1] - gridJ % MPIdim[1]);
  if (sdim == 3)
    gridK = gridK + (MPIdim[2] - gridK % MPIdim[2]);

  gridSize.x = gridI / MPIdim[0];
  gridSize.y = gridJ / MPIdim[1];
  if (sdim == 3)
    gridSize.z = gridK / MPIdim[2];
  else
    gridSize.z = 1;

  if (MPIrank == 0)
    printf("Grid size:%" PRId64 "x%" PRId64 "x%" PRId64 "\n", gridI, gridJ,
	   gridK);
}

/*!
 * This function allocates grid arrays.
 */
void allocateGrid()
{
  int i, j, k;

  gridStartIdx =
      (struct int64Vector3d *) malloc(MPIsize *
				      sizeof(struct int64Vector3d));
  gridEndIdx =
      (struct int64Vector3d *) malloc(MPIsize *
				      sizeof(struct int64Vector3d));

  for (i = 0; i < MPIsize; i++) {
    gridStartIdx[i].x = gridSize.x * MPIcoords[i][0];
    gridStartIdx[i].y = gridSize.y * MPIcoords[i][1];
    if (sdim == 3)
      gridStartIdx[i].z = gridSize.z * MPIcoords[i][2];
    else
      gridStartIdx[i].z = 0;
    gridEndIdx[i].x = gridStartIdx[i].x + gridSize.x - 1;
    gridEndIdx[i].y = gridStartIdx[i].y + gridSize.y - 1;
    if (sdim == 3)
      gridEndIdx[i].z = gridStartIdx[i].z + gridSize.z - 1;
    else
      gridEndIdx[i].z = 0;
  }

  if (!
      (gridBuffer =
       (struct doubleVector3d *) calloc(gridSize.x * gridSize.y *
					gridSize.z,
					sizeof(struct doubleVector3d))))
    stopRun(106, "gridBuffer", __FILE__, __LINE__);


  for (i = 0; i < gridSize.x; i++)
    for (j = 0; j < gridSize.y; j++)
      for (k = 0; k < gridSize.z; k++) {
	grid(i, j, k).x =
	    lowerGridCorner.x + gridResolution * (gridStartIdx[MPIrank].x +
						  i);
	grid(i, j, k).y =
	    lowerGridCorner.y + gridResolution * (gridStartIdx[MPIrank].y +
						  j);
	grid(i, j, k).z =
	    lowerGridCorner.z + gridResolution * (gridStartIdx[MPIrank].z +
						  k);
      }
}
