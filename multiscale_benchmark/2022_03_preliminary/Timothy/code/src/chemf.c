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

#include <float.h>
#include "_hypre_utilities.h"
#include "HYPRE_sstruct_ls.h"
#include "HYPRE_parcsr_ls.h"
#include "HYPRE_krylov.h"

#include "global.h"
#include "fields.h"

/*! \file chemf.c
 *  \brief contains functions used for solving chemical global fields
 */

HYPRE_SStructGrid chemGrid[NCHEM];
HYPRE_SStructGraph chemGraph[NCHEM];
HYPRE_SStructStencil chemStencil[NCHEM];

HYPRE_SStructMatrix chemA[NCHEM];
HYPRE_SStructVector chemb[NCHEM];
HYPRE_SStructVector chemx[NCHEM];

HYPRE_ParCSRMatrix chemParA[NCHEM];
HYPRE_ParVector chemParb[NCHEM];
HYPRE_ParVector chemParx[NCHEM];

HYPRE_Solver chemSolver[NCHEM];
HYPRE_Solver chemPrecond[NCHEM];

int chemObjectType;

long long chemLower[3], chemUpper[3];
long long bcLower[3];
long long bcUpper[3];

double dt[NCHEM];
double chemLambda = 0.25;

char chfname[256];

int chemIter[NCHEM];

double chemZ[NCHEM];

HYPRE_SStructVariable chemVartypes[1] = { HYPRE_SSTRUCT_VARIABLE_NODE };

int numberOfIters;

double *chemPC;			/* production-consumption function */

/*!
 * This function sets boundary conditions for domain faces.
 */
void chemSetBoundary(int coord, int boundary)
{
  if (coord == 0 && boundary == -1) {
    bcLower[0] = chemLower[0];
    bcUpper[0] = chemLower[0];
    bcLower[1] = chemLower[1];
    bcUpper[1] = chemUpper[1];
    bcLower[2] = chemLower[2];
    bcUpper[2] = chemUpper[2];
  }
  if (coord == 0 && boundary == 1) {
    bcLower[0] = chemUpper[0];
    bcUpper[0] = chemUpper[0];
    bcLower[1] = chemLower[1];
    bcUpper[1] = chemUpper[1];
    bcLower[2] = chemLower[2];
    bcUpper[2] = chemUpper[2];
  }
  if (coord == 1 && boundary == -1) {
    bcLower[0] = chemLower[0];
    bcUpper[0] = chemUpper[0];
    bcLower[1] = chemLower[1];
    bcUpper[1] = chemLower[1];
    bcLower[2] = chemLower[2];
    bcUpper[2] = chemUpper[2];
  }
  if (coord == 1 && boundary == 1) {
    bcLower[0] = chemLower[0];
    bcUpper[0] = chemUpper[0];
    bcLower[1] = chemUpper[1];
    bcUpper[1] = chemUpper[1];
    bcLower[2] = chemLower[2];
    bcUpper[2] = chemUpper[2];
  }
  if (coord == 2 && boundary == -1) {
    bcLower[0] = chemLower[0];
    bcUpper[0] = chemUpper[0];
    bcLower[1] = chemLower[1];
    bcUpper[1] = chemUpper[1];
    bcLower[2] = chemLower[2];
    bcUpper[2] = chemLower[2];
  }
  if (coord == 2 && boundary == 1) {
    bcLower[0] = chemLower[0];
    bcUpper[0] = chemUpper[0];
    bcLower[1] = chemLower[1];
    bcUpper[1] = chemUpper[1];
    bcLower[2] = chemUpper[2];
    bcUpper[2] = chemUpper[2];
  }
}

/*!
 * This function initializes grid, stencil and matrix for a given chemical field.
 */
void chemEnvInitSystem(int nch)
{
  int i, j, k, c;
  int entry;
  long long offsets[7][3] =
      { {0, 0, 0}, {-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0,
								  -1}, {0,
									0,
									1}
  };
  double gridResolutionInUnits;	/* grid resolution in centimeters */

  dt[nch] = fieldDt[nch + NGLOB];
  numberOfIters = 1;
  chemIter[nch] = 0;

  sprintf(chfname, "%s/chemSolver.log", logdir);
  /* stdout will go to the file */
  switchStdOut(chfname);

  /* 1. INIT GRID */

  /* create an empty 3D grid object */
  HYPRE_SStructGridCreate(MPI_CART_COMM, 3, 1, &chemGrid[nch]);

  /* set this process box */
  chemLower[0] = gridStartIdx[MPIrank].x;
  chemLower[1] = gridStartIdx[MPIrank].y;
  chemLower[2] = gridStartIdx[MPIrank].z;

  chemUpper[0] = gridEndIdx[MPIrank].x;
  chemUpper[1] = gridEndIdx[MPIrank].y;
  chemUpper[2] = gridEndIdx[MPIrank].z;

  /* add a new box to the grid */
  HYPRE_SStructGridSetExtents(chemGrid[nch], 0, chemLower, chemUpper);

  HYPRE_SStructGridSetVariables(chemGrid[nch], 0, 1, chemVartypes);
  HYPRE_SStructGridAssemble(chemGrid[nch]);

  /*  2. INIT STENCIL */
  HYPRE_SStructStencilCreate(3, 7, &chemStencil[nch]);
  for (entry = 0; entry < 7; entry++)
    HYPRE_SStructStencilSetEntry(chemStencil[nch], entry, offsets[entry],
				 0);

  /* 3. SET UP THE GRAPH */
  chemObjectType = HYPRE_PARCSR;
  HYPRE_SStructGraphCreate(MPI_CART_COMM, chemGrid[nch], &chemGraph[nch]);
  HYPRE_SStructGraphSetObjectType(chemGraph[nch], chemObjectType);
  HYPRE_SStructGraphSetStencil(chemGraph[nch], 0, 0, chemStencil[nch]);
  HYPRE_SStructGraphAssemble(chemGraph[nch]);

  /* 4. SET UP MATRIX */
  long long nentries = 7;
  long long nvalues;
  double *values;
  long long stencil_indices[7];

  nvalues = nentries * gridSize.x * gridSize.y * gridSize.z;
  /* create an empty matrix object */
  HYPRE_SStructMatrixCreate(MPI_CART_COMM, chemGraph[nch], &chemA[nch]);
  HYPRE_SStructMatrixSetObjectType(chemA[nch], chemObjectType);
  /* indicate that the matrix coefficients are ready to be set */
  HYPRE_SStructMatrixInitialize(chemA[nch]);

  values = calloc(nvalues, sizeof(double));

  for (j = 0; j < nentries; j++)
    stencil_indices[j] = j;

  gridResolutionInUnits = (gridResolution / csize) * csizeInUnits * 0.0001;

  chemZ[nch] =
      fieldDiffCoef[nch +
		    NGLOB] * dt[nch] / (gridResolutionInUnits *
					gridResolutionInUnits);

  /* set the standard stencil at each grid point,
   * we will fix the boundaries later */
  for (i = 0; i < nvalues; i += nentries) {
    values[i] = 1 + 6.0 * chemZ[nch] + fieldLambda[nch + NGLOB] * dt[nch];
    for (j = 1; j < nentries; j++)
      values[i + j] = -chemZ[nch];
  }

  HYPRE_SStructMatrixSetBoxValues(chemA[nch], 0, chemLower, chemUpper, 0,
				  nentries, stencil_indices, values);

  for (k = 0; k < gridSize.z; k++)
    for (j = 0; j < gridSize.y; j++)
      for (i = 0; i < gridSize.x; i++) {
	chemField[nch][gridSize.y * gridSize.z * i + gridSize.z * j + k] =
	    fieldICMean[nch + NGLOB];
      }
  fieldMax[nch + NGLOB] = fieldICMean[nch + NGLOB];
  fieldMin[nch + NGLOB] = fieldICMean[nch + NGLOB];

  for (c = 0; c < maxCellsPerProc; c++) {
    cellFields[nch + NGLOB][c] = fieldICMean[nch + NGLOB];
  }

  free(values);
  /* stdout brought back */
  revertStdOut();
}

/*!
 * This function computes cell production/consumption function based on 
 * the interpolated cell density field.
 */
void chemEnvCellPC(int nch)
{
  int ch, i, j, k;
  long long nvalues = gridSize.x * gridSize.y * gridSize.z;

  if (step == 0)
    return;

  int idx = 0;
  for (k = 0; k < gridSize.z; k++)
    for (j = 0; j < gridSize.y; j++)
      for (i = 0; i < gridSize.x; i++, idx++) {
	chemPC[idx] = (-fieldConsumption[nch + NGLOB] + fieldProduction[nch + NGLOB]) * densityField[gridSize.z * gridSize.y * i + gridSize.z * j + k] * dt[nch];	//*(cellVolume/boxVolume);//*(1.0/cellVolume);//*dt[nch];//*dt[nch];
      }
}

/*!
 * This function initializes boundary conditions for a given chemical field.
 */
void chemEnvInitBC(int nch)
{
  int i, j, k;
  int m;
  int nentries = 1;
  long long stencil_indices[1];
  long long nvalues = gridSize.x * gridSize.y * gridSize.z;
  double *values, *bvalues;
  /* stdout redirected to file */
  switchStdOut(chfname);

  chemPC = (double *) calloc(nvalues, sizeof(double));
  values = calloc(nvalues, sizeof(double));
  bvalues = calloc(nvalues, sizeof(double));

  chemEnvCellPC(nch);

  /* 5. SETUP STRUCT VECTORS FOR B AND X */

  /* create an empty vector object */
  HYPRE_SStructVectorCreate(MPI_CART_COMM, chemGrid[nch], &chemb[nch]);
  HYPRE_SStructVectorCreate(MPI_CART_COMM, chemGrid[nch], &chemx[nch]);

  /* as with the matrix, set the appropriate object type for the vectors */
  HYPRE_SStructVectorSetObjectType(chemb[nch], chemObjectType);
  HYPRE_SStructVectorSetObjectType(chemx[nch], chemObjectType);

  /* indicate that the vector coefficients are ready to be set */
  HYPRE_SStructVectorInitialize(chemb[nch]);
  HYPRE_SStructVectorInitialize(chemx[nch]);

  /* set the values */
  m = 0;
  for (k = chemLower[2]; k <= chemUpper[2]; k++)
    for (j = chemLower[1]; j <= chemUpper[1]; j++)
      for (i = chemLower[0]; i <= chemUpper[0]; i++) {
	values[m] = fieldICMean[nch + NGLOB];
	m++;
      }

  HYPRE_SStructVectorSetBoxValues(chemb[nch], 0, chemLower, chemUpper, 0,
				  values);

  m = 0;
  for (k = chemLower[2]; k <= chemUpper[2]; k++)
    for (j = chemLower[1]; j <= chemUpper[1]; j++)
      for (i = chemLower[0]; i <= chemUpper[0]; i++) {
	values[m] = fieldICMean[nch + NGLOB];
	m++;
      }

  HYPRE_SStructVectorSetBoxValues(chemx[nch], 0, chemLower, chemUpper, 0,
				  values);

  /* incorporate boundary conditions; Dirichlet on 6 faces */

  for (i = 0; i < nvalues; i++)
    values[i] = chemZ[nch];
  for (i = 0; i < nvalues; i++)
    bvalues[i] = chemZ[nch] * fieldBC[nch + NGLOB];

  if (MPIcoords[MPIrank][0] == 0) {
    nvalues = nentries * gridSize.y * gridSize.z;
    chemSetBoundary(0, -1);
    stencil_indices[0] = 1;
    HYPRE_SStructMatrixAddToBoxValues(chemA[nch], 0, bcLower, bcUpper, 0,
				      nentries, stencil_indices, values);
    HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, bcLower, bcUpper, 0,
				      bvalues);
  }
  if (MPIcoords[MPIrank][0] == MPIdim[0] - 1) {
    nvalues = nentries * gridSize.y * gridSize.z;
    chemSetBoundary(0, 1);
    stencil_indices[0] = 2;
    HYPRE_SStructMatrixAddToBoxValues(chemA[nch], 0, bcLower, bcUpper, 0,
				      nentries, stencil_indices, values);
    HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, bcLower, bcUpper, 0,
				      bvalues);
  }
  if (MPIcoords[MPIrank][1] == 0) {
    nvalues = nentries * gridSize.x * gridSize.z;
    chemSetBoundary(1, -1);
    stencil_indices[0] = 3;
    HYPRE_SStructMatrixAddToBoxValues(chemA[nch], 0, bcLower, bcUpper, 0,
				      nentries, stencil_indices, values);
    HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, bcLower, bcUpper, 0,
				      bvalues);
  }
  if (MPIcoords[MPIrank][1] == MPIdim[1] - 1) {
    nvalues = nentries * gridSize.x * gridSize.z;
    chemSetBoundary(1, 1);
    stencil_indices[0] = 4;
    HYPRE_SStructMatrixAddToBoxValues(chemA[nch], 0, bcLower, bcUpper, 0,
				      nentries, stencil_indices, values);
    HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, bcLower, bcUpper, 0,
				      bvalues);
  }
  if (MPIcoords[MPIrank][2] == 0) {
    nvalues = nentries * gridSize.x * gridSize.y;
    chemSetBoundary(2, -1);
    stencil_indices[0] = 5;
    HYPRE_SStructMatrixAddToBoxValues(chemA[nch], 0, bcLower, bcUpper, 0,
				      nentries, stencil_indices, values);
    HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, bcLower, bcUpper, 0,
				      bvalues);
  }
  if (MPIcoords[MPIrank][2] == MPIdim[2] - 1) {
    nvalues = nentries * gridSize.x * gridSize.y;
    chemSetBoundary(2, 1);
    stencil_indices[0] = 6;
    HYPRE_SStructMatrixAddToBoxValues(chemA[nch], 0, bcLower, bcUpper, 0,
				      nentries, stencil_indices, values);
    HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, bcLower, bcUpper, 0,
				      bvalues);
  }

  /* add production consumption function to the right side */
  HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, chemLower, chemUpper, 0,
				    chemPC);

  free(chemPC);
  free(values);
  free(bvalues);
  /* stdout brought back */
  revertStdOut();
}

/*!
 * This function initializes Hypre for solving a given chemical field.
 */
void chemEnvInitSolver(int nch)
{
  /* stdout redirected to file */
  switchStdOut(chfname);

  HYPRE_SStructMatrixAssemble(chemA[nch]);
  /* This is a collective call finalizing the vector assembly.
     The vector is now ``ready to be used'' */
  HYPRE_SStructVectorAssemble(chemb[nch]);
  HYPRE_SStructVectorAssemble(chemx[nch]);

  HYPRE_SStructMatrixGetObject(chemA[nch], (void **) &chemParA[nch]);
  HYPRE_SStructVectorGetObject(chemb[nch], (void **) &chemParb[nch]);
  HYPRE_SStructVectorGetObject(chemx[nch], (void **) &chemParx[nch]);

  HYPRE_ParCSRPCGCreate(MPI_CART_COMM, &chemSolver[nch]);
  HYPRE_ParCSRPCGSetTol(chemSolver[nch], 1.0e-12);
  HYPRE_ParCSRPCGSetPrintLevel(chemSolver[nch], 2);
  HYPRE_ParCSRPCGSetMaxIter(chemSolver[nch], 50);

  HYPRE_BoomerAMGCreate(&chemPrecond[nch]);
  HYPRE_BoomerAMGSetMaxIter(chemPrecond[nch], 1);
  HYPRE_BoomerAMGSetTol(chemPrecond[nch], 0.0);
  HYPRE_BoomerAMGSetPrintLevel(chemPrecond[nch], 2);
  HYPRE_BoomerAMGSetCoarsenType(chemPrecond[nch], 6);
  HYPRE_BoomerAMGSetRelaxType(chemPrecond[nch], 6);
  HYPRE_BoomerAMGSetNumSweeps(chemPrecond[nch], 1);

  HYPRE_ParCSRPCGSetPrecond(chemSolver[nch], HYPRE_BoomerAMGSolve,
			    HYPRE_BoomerAMGSetup, chemPrecond[nch]);
  HYPRE_ParCSRPCGSetup(chemSolver[nch], chemParA[nch], chemParb[nch],
		       chemParx[nch]);

  /* stdout brought back */
  revertStdOut();
}

/*!
 * This is a driving function for solving next time step 
 * of a given chemical field.
 */
void chemEnvSolve(int nch)
{
  int i, j, k;
  int idx;
  double *values;
  int stepIter = 0;
  long long nvalues = gridSize.x * gridSize.y * gridSize.z;
#ifdef DEBUG
  if (MPIrank == 0 && !(step % statOutStep) && gfIter == 0) {
    printf(" Solving field: %s...", fieldName[nch + NGLOB]);
    fflush(stdout);
  }
#endif
  /* redirecting stdout to log file */
  switchStdOut(chfname);

  values = (double *) calloc(nvalues, sizeof(double));
  chemPC = (double *) calloc(nvalues, sizeof(double));
  chemEnvCellPC(nch);

  fieldMin[nch + NGLOB] = DBL_MAX;
  fieldMax[nch + NGLOB] = DBL_MIN;

  while (stepIter < numberOfIters) {
    if (chemIter[nch] > 0) {
      /* update right hand side */
      HYPRE_SStructVectorGetBoxValues(chemx[nch], 0, chemLower, chemUpper,
				      0, values);
      HYPRE_SStructVectorSetBoxValues(chemb[nch], 0, chemLower, chemUpper,
				      0, values);
      for (i = 0; i < nvalues; i++)
	values[i] = chemZ[nch] * fieldBC[nch + NGLOB];
      if (MPIcoords[MPIrank][0] == 0) {
	chemSetBoundary(0, -1);
	HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, bcLower, bcUpper,
					  0, values);
      }
      if (MPIcoords[MPIrank][0] == MPIdim[0] - 1) {
	chemSetBoundary(0, 1);
	HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, bcLower, bcUpper,
					  0, values);
      }
      if (MPIcoords[MPIrank][1] == 0) {
	chemSetBoundary(1, -1);
	HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, bcLower, bcUpper,
					  0, values);
      }
      if (MPIcoords[MPIrank][1] == MPIdim[1] - 1) {
	chemSetBoundary(1, 1);
	HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, bcLower, bcUpper,
					  0, values);
      }
      if (MPIcoords[MPIrank][2] == 0) {
	chemSetBoundary(2, -1);
	HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, bcLower, bcUpper,
					  0, values);
      }
      if (MPIcoords[MPIrank][2] == MPIdim[2] - 1) {
	chemSetBoundary(2, 1);
	HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, bcLower, bcUpper,
					  0, values);
      }
      HYPRE_SStructVectorAddToBoxValues(chemb[nch], 0, chemLower,
					chemUpper, 0, chemPC);
      HYPRE_SStructVectorAssemble(chemb[nch]);
      HYPRE_SStructVectorAssemble(chemx[nch]);
    }

    HYPRE_ParCSRPCGSolve(chemSolver[nch], chemParA[nch], chemParb[nch],
			 chemParx[nch]);

    /* copy solution to field buffer */
    HYPRE_SStructVectorGather(chemx[nch]);
    HYPRE_SStructVectorGetBoxValues(chemx[nch], 0, chemLower, chemUpper, 0,
				    values);
    idx = 0;
    for (k = 0; k < gridSize.z; k++)
      for (j = 0; j < gridSize.y; j++)
	for (i = 0; i < gridSize.x; i++, idx++) {
	  chemField[nch][gridSize.y * gridSize.z * i + gridSize.z * j +
			 k] = values[idx];
	  if (values[idx] > fieldMax[nch + NGLOB])
	    fieldMax[nch + NGLOB] = values[idx];
	  if (values[idx] < fieldMin[nch + NGLOB])
	    fieldMin[nch + NGLOB] = values[idx];
	}
    chemIter[nch]++;
    stepIter++;
  }

  free(values);
  free(chemPC);
  /* stdout brought back */
  revertStdOut();
#ifdef DEBUG
  if (MPIrank == 0 && !(step % statOutStep) && gfIter == gfIterPerStep - 1) {
    printf("done\n");
    fflush(stdout);
  }
#endif
}
