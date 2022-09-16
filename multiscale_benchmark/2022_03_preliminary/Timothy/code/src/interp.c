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
#include <limits.h>

#include "global.h"
#include "fields.h"

/*! \file interp.c
 *  \brief contains grid to cellular data interpolation functions
 */

double **cicPatch;
int *cicIntersect;
int *cicReceiver;
int *cicSender;
double **cicRecvPatch;

MPI_Request *cicReqSend, *cicReqRecv;

int *recvP;

struct int64Vector3d *lowerPatchCorner, *upperPatchCorner;
struct int64Vector3d *lowerPatchCornerR, *upperPatchCornerR;
struct int64Vector3d *patchSize;
struct int64Vector3d *patchSizeR;
#define patch(p,i,j,k) (cicPatch[p][patchSize[p].y*patchSize[p].z*i+patchSize[p].z*j+k])

/*!
 * For each local cell we check its position in the grid. 
 * If cell is located in the grid partition of other process
 * than the information about this cell should be send to 
 * remote process by MPI communication. This is done by preparing
 * special patches and sending the information on all bunch of cells 
 * rather than sendind it one by one.
 * This function identifies patches and allocate memory buffers for patches.
 */
void findPatches()
{

  int i, c, p;
  struct int64Vector3d cellIdx;

  cicPatch = (double **) calloc(MPIsize, sizeof(double *));
  cicIntersect = (int *) calloc(MPIsize, sizeof(int));
  lowerPatchCorner =
      (struct int64Vector3d *) calloc(MPIsize,
				      sizeof(struct int64Vector3d));
  upperPatchCorner =
      (struct int64Vector3d *) calloc(MPIsize,
				      sizeof(struct int64Vector3d));
  lowerPatchCornerR =
      (struct int64Vector3d *) calloc(MPIsize,
				      sizeof(struct int64Vector3d));
  upperPatchCornerR =
      (struct int64Vector3d *) calloc(MPIsize,
				      sizeof(struct int64Vector3d));
  patchSize =
      (struct int64Vector3d *) calloc(MPIsize,
				      sizeof(struct int64Vector3d));
  patchSizeR =
      (struct int64Vector3d *) calloc(MPIsize,
				      sizeof(struct int64Vector3d));

  for (p = 0; p < MPIsize; p++) {
    cicIntersect[p] = 0;
    patchSize[p].x = 0;
    patchSize[p].y = 0;
    patchSize[p].z = 0;
    lowerPatchCorner[p].x = INT_MAX;
    lowerPatchCorner[p].y = INT_MAX;
    if (sdim == 3)
      lowerPatchCorner[p].z = INT_MAX;
    else
      lowerPatchCorner[p].z = 0;
    upperPatchCorner[p].x = INT_MIN, upperPatchCorner[p].y = INT_MIN;
    if (sdim == 3)
      upperPatchCorner[p].z = INT_MIN;
    else
      upperPatchCorner[p].z = 0;
  }

  //#pragma omp parallel for default(none) private(p,c,cellIdx) shared(cells,gridResolution,lnc,MPIsize,gridStartIdx,gridEndIdx,lowerPatchCorner,upperPatchCorner,cicIntersect,sdim,lowerGridCorner)
  for (p = 0; p < MPIsize; p++) {

    for (c = 0; c < lnc; c++) {

      int ax, ay, az;

      cellIdx.x = ((cells[c].x - lowerGridCorner.x) / gridResolution);
      cellIdx.y = ((cells[c].y - lowerGridCorner.y) / gridResolution);
      cellIdx.z = ((cells[c].z - lowerGridCorner.z) / gridResolution);

      for (ax = 0; ax < 2; ax++)
	for (ay = 0; ay < 2; ay++)
	  for (az = 0; az < 2; az++) {

	    if (cellIdx.x + ax >= gridStartIdx[p].x
		&& cellIdx.y + ay >= gridStartIdx[p].y
		&& cellIdx.z + az >= gridStartIdx[p].z
		&& cellIdx.x + ax <= gridEndIdx[p].x
		&& cellIdx.y + ay <= gridEndIdx[p].y
		&& cellIdx.z + az <= gridEndIdx[p].z) {
	      lowerPatchCorner[p].x =
		  (lowerPatchCorner[p].x >
		   cellIdx.x + ax ? cellIdx.x +
		   ax : lowerPatchCorner[p].x);
	      lowerPatchCorner[p].y =
		  (lowerPatchCorner[p].y >
		   cellIdx.y + ay ? cellIdx.y +
		   ay : lowerPatchCorner[p].y);
	      if (sdim == 3)
		lowerPatchCorner[p].z =
		    (lowerPatchCorner[p].z >
		     cellIdx.z + az ? cellIdx.z +
		     az : lowerPatchCorner[p].z);
	      upperPatchCorner[p].x =
		  (upperPatchCorner[p].x <
		   cellIdx.x + ax ? cellIdx.x +
		   ax : upperPatchCorner[p].x);
	      upperPatchCorner[p].y =
		  (upperPatchCorner[p].y <
		   cellIdx.y + ay ? cellIdx.y +
		   ay : upperPatchCorner[p].y);
	      if (sdim == 3)
		upperPatchCorner[p].z =
		    (upperPatchCorner[p].z <
		     cellIdx.z + az ? cellIdx.z +
		     az : upperPatchCorner[p].z);

	      cicIntersect[p] = 1;
	    }
	  }
    }
  }

  for (p = 0; p < MPIsize; p++)
    if (cicIntersect[p]) {
      patchSize[p].x = upperPatchCorner[p].x - lowerPatchCorner[p].x + 1;
      patchSize[p].y = upperPatchCorner[p].y - lowerPatchCorner[p].y + 1;
      if (sdim == 3)
	patchSize[p].z = upperPatchCorner[p].z - lowerPatchCorner[p].z + 1;
      else
	patchSize[p].z = 1;
      cicPatch[p] =
	  (double *) calloc(patchSize[p].x * patchSize[p].y *
			    patchSize[p].z, sizeof(double));
    }

  return;
}

/*!
 * For each local cell its density value is interpolated accross 
 * neighbouring grid vertices with the use of Cloud-In-Cell method.
 * Computed values are stored in patches instead in field buffers.
 * No additional memory allocations are made here.
 */
void doInterpolation()
{

  int c, i, p, j, k;
  struct int64Vector3d idx;
  struct doubleVector3d d, t;
  struct int64Vector3d cellIdx;
  struct doubleVector3d cicCoord;

  for (p = 0; p < MPIsize; p++)
    for (i = 0; i < patchSize[p].x; i++)
      for (j = 0; j < patchSize[p].y; j++)
	for (k = 0; k < patchSize[p].z; k++)
	  patch(p, i, j, k) = 0.0;

  for (c = 0; c < lnc; c++) {

    cellIdx.x = ((cells[c].x - lowerGridCorner.x) / gridResolution);
    cellIdx.y = ((cells[c].y - lowerGridCorner.y) / gridResolution);
    cellIdx.z = ((cells[c].z - lowerGridCorner.z) / gridResolution);

    for (p = 0; p < MPIsize; p++) {
      int ax, ay, az;
      for (ax = 0; ax < 2; ax++)
	for (ay = 0; ay < 2; ay++)
	  for (az = 0; az < 2; az++) {
	    if (cellIdx.x + ax >= gridStartIdx[p].x
		&& cellIdx.y + ay >= gridStartIdx[p].y
		&& cellIdx.z + az >= gridStartIdx[p].z
		&& cellIdx.x + ax <= gridEndIdx[p].x
		&& cellIdx.y + ay <= gridEndIdx[p].y
		&& cellIdx.z + az <= gridEndIdx[p].z) {

	      idx.x = (cellIdx.x + ax) - lowerPatchCorner[p].x;
	      idx.y = (cellIdx.y + ay) - lowerPatchCorner[p].y;
	      idx.z = (cellIdx.z + az) - lowerPatchCorner[p].z;

	      cicCoord.x = lowerGridCorner.x + cellIdx.x * gridResolution;
	      cicCoord.y = lowerGridCorner.y + cellIdx.y * gridResolution;
	      cicCoord.z = lowerGridCorner.z + cellIdx.z * gridResolution;

	      d.x = (cells[c].x - cicCoord.x) / gridResolution;
	      d.y = (cells[c].y - cicCoord.y) / gridResolution;
	      d.z = (cells[c].z - cicCoord.z) / gridResolution;

	      t.x = 1.0 - d.x;
	      t.y = 1.0 - d.y;
	      t.z = 1.0 - d.z;

	      if (cells[c].phase != 5) {	/* if not in necrotic phase */
		if (cells[c].phase == 0) {	/* if in G0 phase - lower consumption */
		  patch(p, idx.x, idx.y, idx.z) +=
		      0.75 * (ax * d.x + (1 - ax) * t.x) * (ay * d.y +
							    (1 -
							     ay) * t.y) *
		      (az * d.z + (1 - az) * t.z);
		} else {	/* if not in G0 phase - normal consumption */
		  patch(p, idx.x, idx.y, idx.z) +=
		      1.0 * (ax * d.x + (1 - ax) * t.x) * (ay * d.y +
							   (1 -
							    ay) * t.y) *
		      (az * d.z + (1 - az) * t.z);
		}
	      }

	    }
	  }
    }
  }
  return;
}

/*!
 *  Patches are being sent to receiving processes with non-blocking 
 * communication scheme (Isend, Irecv).
 * Receiving patches are allocated here.
 * MPI_Request tables are allocated here.
 */
void initPatchExchange()
{
  int p;

  cicReceiver = (int *) calloc(MPIsize, sizeof(int));
  cicSender = (int *) calloc(MPIsize, sizeof(int));

  for (p = 0; p < MPIsize; p++)
    cicReceiver[p] = cicIntersect[p];

  MPI_Alltoall(cicReceiver, 1, MPI_INT, cicSender, 1, MPI_INT,
	       MPI_COMM_WORLD);

  MPI_Alltoall(lowerPatchCorner, sizeof(struct int64Vector3d), MPI_BYTE,
	       lowerPatchCornerR, sizeof(struct int64Vector3d), MPI_BYTE,
	       MPI_COMM_WORLD);
  MPI_Alltoall(upperPatchCorner, sizeof(struct int64Vector3d), MPI_BYTE,
	       upperPatchCornerR, sizeof(struct int64Vector3d), MPI_BYTE,
	       MPI_COMM_WORLD);

  cicRecvPatch = (double **) calloc(MPIsize, sizeof(double *));
  cicReqSend = (MPI_Request *) malloc(sizeof(MPI_Request) * MPIsize);
  cicReqRecv = (MPI_Request *) malloc(sizeof(MPI_Request) * MPIsize);

  for (p = 0; p < MPIsize; p++) {
    if (cicReceiver[p]) {
      MPI_Isend(&(cicPatch[p][0]),
		patchSize[p].x * patchSize[p].y * patchSize[p].z,
		MPI_DOUBLE, p, MPIrank, MPI_COMM_WORLD, &cicReqSend[p]);
    }
    if (cicSender[p]) {
      int recvSize;
      recvSize =
	  (upperPatchCornerR[p].x - lowerPatchCornerR[p].x +
	   1) * (upperPatchCornerR[p].y - lowerPatchCornerR[p].y +
		 1) * (upperPatchCornerR[p].z - lowerPatchCornerR[p].z +
		       1);
      if (!(cicRecvPatch[p] = (double *) calloc(recvSize, sizeof(double))))
	exit(0);
      MPI_Irecv(&(cicRecvPatch[p][0]), recvSize, MPI_DOUBLE, p, p,
		MPI_COMM_WORLD, &cicReqRecv[p]);
    }
  }
  return;
}

/*! 
 * Wait for communication to finish.
 * MPI_Request tables are deallocated here.
 */
int waitPatchExchange()
{
  int p;
  MPI_Status status;

  for (p = 0; p < MPIsize; p++) {
    if (!cicReceiver[p])
      continue;
    if (MPI_Wait(&cicReqSend[p], &status) != MPI_SUCCESS)
      stopRun(103, "sending", __FILE__, __LINE__);
  }

  for (p = 0; p < MPIsize; p++) {
    if (!cicSender[p])
      continue;
    if (MPI_Wait(&cicReqRecv[p], &status) != MPI_SUCCESS)
      stopRun(103, "receiving", __FILE__, __LINE__);
  }

  free(cicReqSend);
  free(cicReqRecv);

  return 0;
}

/*! 
 * Update local densityField part with information from remote processes 
 * received in patches. Receiveing patches are deallocated here. 
 */
int applyPatches()
{

  int p;
  int i, j, k;

  for (i = 0; i < gridSize.x * gridSize.y * gridSize.z; i++)
    densityField[i] = 0.0;

  for (p = 0; p < MPIsize; p++) {
    int i, j, k;
    if (!cicSender[p])
      continue;
    for (i = lowerPatchCornerR[p].x; i <= upperPatchCornerR[p].x; i++)
      for (j = lowerPatchCornerR[p].y; j <= upperPatchCornerR[p].y; j++)
	for (k = lowerPatchCornerR[p].z; k <= upperPatchCornerR[p].z; k++) {
	  struct int64Vector3d c, g, size;
	  size.x = upperPatchCornerR[p].x - lowerPatchCornerR[p].x + 1;
	  size.y = upperPatchCornerR[p].y - lowerPatchCornerR[p].y + 1;
	  size.z = upperPatchCornerR[p].z - lowerPatchCornerR[p].z + 1;
	  c.x = i - lowerPatchCornerR[p].x;
	  c.y = j - lowerPatchCornerR[p].y;
	  c.z = k - lowerPatchCornerR[p].z;
	  if (i >= gridStartIdx[MPIrank].x && i <= gridEndIdx[MPIrank].x
	      && j >= gridStartIdx[MPIrank].y && j <= gridEndIdx[MPIrank].y
	      && k >= gridStartIdx[MPIrank].z
	      && k <= gridEndIdx[MPIrank].z) {
	    g.x = i - gridStartIdx[MPIrank].x;
	    g.y = j - gridStartIdx[MPIrank].y;
	    g.z = k - gridStartIdx[MPIrank].z;
	    densityField[gridSize.z * gridSize.y * g.x + gridSize.z * g.y +
			 g.z] +=
		cicRecvPatch[p][size.z * size.y * c.x + size.z * c.y +
				c.z];
	  }
	}
    free(cicRecvPatch[p]);
  }

  free(cicRecvPatch);

  for (p = 0; p < MPIsize; p++)
    if (cicIntersect[p])
      free(cicPatch[p]);

  free(cicPatch);
  return;
}

/*!
 * Now each local cell should receive information about values 
 * of global fields in the grid.
 * Field patches are filled with appropriate values. 
 * Non-blocking communication is initiated.
 * This is executed after global fields are computed.
 * Field patches buffers are allocated here. 
 * Sizes of the patches are the same as those from previous CIC communication.
 * Receiving field patches are also allocated here.
 * MPI_Request tables are allocated here.
 */
void initFieldsPatchesExchange()
{

  int f;			/* fields index */
  int p;			/* process index */
  struct int64Vector3d idx, g;
  struct int64Vector3d size;

  fieldsPatchesCommBuff = (double **) calloc(MPIsize, sizeof(double *));

  for (p = 0; p < MPIsize; p++) {
    int fieldPatchSize;
    if (!cicSender[p])
      continue;			/* continue to next process if current process do not overlap domain */
    size.x = upperPatchCornerR[p].x - lowerPatchCornerR[p].x + 1;
    size.y = upperPatchCornerR[p].y - lowerPatchCornerR[p].y + 1;
    size.z = upperPatchCornerR[p].z - lowerPatchCornerR[p].z + 1;
    fieldPatchSize = size.x * size.y * size.z;
    fieldsPatchesCommBuff[p] =
	(double *) calloc(NFIELDS * fieldPatchSize, sizeof(double));
    for (f = 0; f < NFIELDS; f++) {
      int64_t i, j, k;
      for (i = lowerPatchCornerR[p].x; i <= upperPatchCornerR[p].x; i++)
	for (j = lowerPatchCornerR[p].y; j <= upperPatchCornerR[p].y; j++)
	  for (k = lowerPatchCornerR[p].z; k <= upperPatchCornerR[p].z;
	       k++) {
	    idx.x = i - lowerPatchCornerR[p].x;
	    idx.y = j - lowerPatchCornerR[p].y;
	    idx.z = k - lowerPatchCornerR[p].z;
	    g.x = i - gridStartIdx[MPIrank].x;
	    g.y = j - gridStartIdx[MPIrank].y;
	    g.z = k - gridStartIdx[MPIrank].z;
	    fieldsPatchesCommBuff[p][f * fieldPatchSize +
				     size.z * size.y * idx.x +
				     size.z * idx.y + idx.z] =
		((double *) fieldAddr[f])[gridSize.z * gridSize.y * g.x +
					  gridSize.z * g.y + g.z];
	  }
    }
  }

  if (!(fieldsPatches = (double **) calloc(MPIsize, sizeof(double *))))
    stopRun(106, "fieldsPatches", __FILE__, __LINE__);

  cicReqSend = (MPI_Request *) malloc(sizeof(MPI_Request) * MPIsize);
  cicReqRecv = (MPI_Request *) malloc(sizeof(MPI_Request) * MPIsize);

  for (p = 0; p < MPIsize; p++) {
    if (cicSender[p]) {
      int sendSize;
      sendSize =
	  (upperPatchCornerR[p].x - lowerPatchCornerR[p].x +
	   1) * (upperPatchCornerR[p].y - lowerPatchCornerR[p].y +
		 1) * (upperPatchCornerR[p].z - lowerPatchCornerR[p].z +
		       1) * NFIELDS;
      MPI_Isend(&(fieldsPatchesCommBuff[p][0]), sendSize, MPI_DOUBLE, p,
		MPIrank, MPI_COMM_WORLD, &cicReqSend[p]);
    }
    if (cicReceiver[p]) {
      int recvSize;
      recvSize =
	  patchSize[p].x * patchSize[p].y * patchSize[p].z * NFIELDS;
      if (!
	  (fieldsPatches[p] = (double *) calloc(recvSize, sizeof(double))))
	stopRun(106, "fieldsPatches", __FILE__, __LINE__);
      MPI_Irecv(&(fieldsPatches[p][0]), recvSize, MPI_DOUBLE, p, p,
		MPI_COMM_WORLD, &cicReqRecv[p]);
    }
  }
  return;
}

/*! 
 * Wait for communication to finish.
 * MPI_Request tables are deallocated here.
 * Field patches buffers are deallocated here.
 */
void waitFieldsPatchesExchange()
{
  int p, f;
  MPI_Status status;

  for (p = 0; p < MPIsize; p++) {
    if (!cicSender[p])
      continue;
    if (MPI_Wait(&cicReqSend[p], &status) != MPI_SUCCESS)
      stopRun(103, "sending", __FILE__, __LINE__);
  }

  for (p = 0; p < MPIsize; p++) {
    if (!cicReceiver[p])
      continue;
    if (MPI_Wait(&cicReqRecv[p], &status) != MPI_SUCCESS)
      stopRun(103, "receiving", __FILE__, __LINE__);
  }

  free(cicReqSend);
  free(cicReqRecv);

  for (p = 0; p < MPIsize; p++)
    free(fieldsPatchesCommBuff[p]);
  free(fieldsPatchesCommBuff);

  return;
}

/*! 
 * Update local cell fields with information from 
 * remote processes received in patches.
 * Receiveing field patches are deallocated here.
 */
void applyFieldsPatches()
{

  int p, c, f, i, j, k;
  struct int64Vector3d idx;
  struct doubleVector3d d, t;
  struct int64Vector3d cellIdx;
  struct doubleVector3d cicCoord;

  int max = 0;
  int iddd;

  /* reset fields */
  for (f = 0; f < NFIELDS; f++)
    for (c = 0; c < lnc; c++)
      cellFields[f][c] = 0.0;

  for (c = 0; c < lnc; c++) {	/* for every cell */
    cellIdx.x = ((cells[c].x - lowerGridCorner.x) / gridResolution);
    cellIdx.y = ((cells[c].y - lowerGridCorner.y) / gridResolution);
    cellIdx.z = ((cells[c].z - lowerGridCorner.z) / gridResolution);
    for (p = 0; p < MPIsize; p++) {	/* for each process */
      int ax, ay, az;
      if (!cicReceiver[p])
	continue;		/* there is no patch from this process */
      for (ax = 0; ax < 2; ax++)
	for (ay = 0; ay < 2; ay++)
	  for (az = 0; az < 2; az++) {
	    if (cellIdx.x + ax >= gridStartIdx[p].x
		&& cellIdx.y + ay >= gridStartIdx[p].y
		&& cellIdx.z + az >= gridStartIdx[p].z
		&& cellIdx.x + ax <= gridEndIdx[p].x
		&& cellIdx.y + ay <= gridEndIdx[p].y
		&& cellIdx.z + az <= gridEndIdx[p].z) {

	      idx.x = (cellIdx.x + ax) - lowerPatchCorner[p].x;
	      idx.y = (cellIdx.y + ay) - lowerPatchCorner[p].y;
	      idx.z = (cellIdx.z + az) - lowerPatchCorner[p].z;

	      cicCoord.x = lowerGridCorner.x + cellIdx.x * gridResolution;
	      cicCoord.y = lowerGridCorner.y + cellIdx.y * gridResolution;
	      cicCoord.z = lowerGridCorner.z + cellIdx.z * gridResolution;

	      d.x = (cells[c].x - cicCoord.x) / gridResolution;
	      d.y = (cells[c].y - cicCoord.y) / gridResolution;
	      d.z = (cells[c].z - cicCoord.z) / gridResolution;

	      t.x = 1.0 - d.x;
	      t.y = 1.0 - d.y;
	      t.z = 1.0 - d.z;

	      /* interpolating back to cells */
	      /* scaling from mol/cm^3 to mol/cell */
	      for (f = 0; f < NFIELDS; f++) {
		cellFields[f][c] += fieldsPatches[p][f * patchSize[p].x * patchSize[p].y * patchSize[p].z + patchSize[p].y * patchSize[p].z * idx.x + patchSize[p].z * idx.y + idx.z] * (ax * d.x + (1 - ax) * t.x) * (ay * d.y + (1 - ay) * t.y) * (az * d.z + (1 - az) * t.z);	//*cellVolume;
	      }
	    }			// if
	  }			// az
    }				// p
  }				// c

  for (p = 0; p < MPIsize; p++)
    free(fieldsPatches[p]);
  free(fieldsPatches);

  return;
}

/*!
 * This is a driving function interpolating 
 * cellular data to grid data.
 * This function does not enable overlapping communication
 * and computations.
 */
void interpolateCellsToGrid()
{
  findPatches();
  doInterpolation();
  initPatchExchange();
  waitPatchExchange();
  applyPatches();
}

/*!
 * This function initializes data exchange between
 * processes required in cells-to-grid interpolation.
 * This function enables overlapping communication and
 * computations.
 */
void initCellsToGridExchange()
{
  if (!gfields)
    return;
  findPatches();
  doInterpolation();
  initPatchExchange();
}

/*!
 * This function wait for patches communication to finish
 * in cells-to-grid interpolation.
 * This function enables overlapping communication and
 * computations.
 */
void waitCellsToGridExchange()
{
  if (!gfields)
    return;
  waitPatchExchange();
  applyPatches();
}

/*!
 * This function is used to interpolate field data back to 
 * cells. Overlapping of communication and computations is not
 * implemented here.
 * This function deallocates all important arrays used in interpolation.
 */
void interpolateFieldsToCells()
{
  if (!gfields)
    return;

  initFieldsPatchesExchange();
  waitFieldsPatchesExchange();
  applyFieldsPatches();

  free(cicReceiver);
  free(cicSender);
  free(cicIntersect);

  free(lowerPatchCorner);
  free(upperPatchCorner);
  free(lowerPatchCornerR);
  free(upperPatchCornerR);
  free(patchSize);
  free(patchSizeR);
}
