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

#include "_hypre_utilities.h"
#include "HYPRE_sstruct_ls.h"
#include "HYPRE_parcsr_ls.h"
#include "HYPRE_krylov.h"

#include "global.h"
#include "fields.h"

/*! \file tempf.c
 *  \brief contains functions used for solving temperature field
 */

HYPRE_SStructGrid tempGrid;
HYPRE_SStructGraph tempGraph;
HYPRE_SStructStencil tempStencil;

HYPRE_SStructMatrix A;
HYPRE_SStructVector b;
HYPRE_SStructVector x;

HYPRE_ParCSRMatrix parA;
HYPRE_ParVector parb;
HYPRE_ParVector parx;

HYPRE_Solver tempSolver;
HYPRE_Solver tempPrecond;

int tempObjectType;

long long tempLower[3], tempUpper[3];
long long bcLower[3];
long long bcUpper[3];

double dt;
double tempLambda = 0.25;

char tfname[256];

int tempNVars;
int tempNParts;

int tempIter;

HYPRE_SStructVariable tempVartypes[1] = { HYPRE_SSTRUCT_VARIABLE_NODE };

/*!
 * This function sets boundary conditions for domain faces.
 */
void tempSetBoundary(int coord, int boundary)
{
  if (coord == 0 && boundary == -1) {
    bcLower[0] = tempLower[0];
    bcUpper[0] = tempLower[0];
    bcLower[1] = tempLower[1];
    bcUpper[1] = tempUpper[1];
    bcLower[2] = tempLower[2];
    bcUpper[2] = tempUpper[2];
  }
  if (coord == 0 && boundary == 1) {
    bcLower[0] = tempUpper[0];
    bcUpper[0] = tempUpper[0];
    bcLower[1] = tempLower[1];
    bcUpper[1] = tempUpper[1];
    bcLower[2] = tempLower[2];
    bcUpper[2] = tempUpper[2];
  }
  if (coord == 1 && boundary == -1) {
    bcLower[0] = tempLower[0];
    bcUpper[0] = tempUpper[0];
    bcLower[1] = tempLower[1];
    bcUpper[1] = tempLower[1];
    bcLower[2] = tempLower[2];
    bcUpper[2] = tempUpper[2];
  }
  if (coord == 1 && boundary == 1) {
    bcLower[0] = tempLower[0];
    bcUpper[0] = tempUpper[0];
    bcLower[1] = tempUpper[1];
    bcUpper[1] = tempUpper[1];
    bcLower[2] = tempLower[2];
    bcUpper[2] = tempUpper[2];
  }
  if (coord == 2 && boundary == -1) {
    bcLower[0] = tempLower[0];
    bcUpper[0] = tempUpper[0];
    bcLower[1] = tempLower[1];
    bcUpper[1] = tempUpper[1];
    bcLower[2] = tempLower[2];
    bcUpper[2] = tempLower[2];
  }
  if (coord == 2 && boundary == 1) {
    bcLower[0] = tempLower[0];
    bcUpper[0] = tempUpper[0];
    bcLower[1] = tempLower[1];
    bcUpper[1] = tempUpper[1];
    bcLower[2] = tempUpper[2];
    bcUpper[2] = tempUpper[2];
  }
}

/*!
 * This function initializes grid, stencil and matrix for temperature field.
 */
void tempEnvInitSystem()
{
  int i, j, k;
  double z;
  int entry;
  long long offsets[7][3] =
      { {0, 0, 0}, {-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0,
								  -1}, {0,
									0,
									1}
  };

  dt = 0.1;
  tempIter = 0;
  tempNVars = 1;
  tempNParts = 1;

  sprintf(tfname, "%s/tempSolver.log", logdir);
  /* stdout redirected to file */
  switchStdOut(tfname);

  /* 1. INIT GRID */

  /* create an empty 3D grid object */
  HYPRE_SStructGridCreate(MPI_CART_COMM, 3, tempNParts, &tempGrid);

  /* set this process box */
  tempLower[0] = gridStartIdx[MPIrank].x;
  tempLower[1] = gridStartIdx[MPIrank].y;
  tempLower[2] = gridStartIdx[MPIrank].z;

  tempUpper[0] = gridEndIdx[MPIrank].x;
  tempUpper[1] = gridEndIdx[MPIrank].y;
  tempUpper[2] = gridEndIdx[MPIrank].z;

  /* add a new box to the grid */
  HYPRE_SStructGridSetExtents(tempGrid, 0, tempLower, tempUpper);

  HYPRE_SStructGridSetVariables(tempGrid, 0, tempNVars, tempVartypes);
  HYPRE_SStructGridAssemble(tempGrid);

  /*  2. INIT STENCIL */
  HYPRE_SStructStencilCreate(3, 7, &tempStencil);
  for (entry = 0; entry < 7; entry++)
    HYPRE_SStructStencilSetEntry(tempStencil, entry, offsets[entry], 0);

  /* 3. SET UP THE GRAPH */
  tempObjectType = HYPRE_PARCSR;
  HYPRE_SStructGraphCreate(MPI_CART_COMM, tempGrid, &tempGraph);
  HYPRE_SStructGraphSetObjectType(tempGraph, tempObjectType);
  HYPRE_SStructGraphSetStencil(tempGraph, 0, 0, tempStencil);
  HYPRE_SStructGraphAssemble(tempGraph);

  /* 4. SET UP MATRIX */
  long long nentries = 7;
  long long nvalues;
  double *values;
  long long stencil_indices[7];

  nvalues = nentries * gridSize.x * gridSize.y * gridSize.z;
  /* create an empty matrix object */
  HYPRE_SStructMatrixCreate(MPI_CART_COMM, tempGraph, &A);
  HYPRE_SStructMatrixSetObjectType(A, tempObjectType);
  /* indicate that the matrix coefficients are ready to be set */
  HYPRE_SStructMatrixInitialize(A);

  values = calloc(nvalues, sizeof(double));

  for (j = 0; j < nentries; j++)
    stencil_indices[j] = j;

  z = dt / (gridResolution * gridResolution);

  /* set the standard stencil at each grid point,
   * we will fix the boundaries later */
  for (i = 0; i < nvalues; i += nentries) {
    values[i] = 1 + 6.0 * z;
    for (j = 1; j < nentries; j++)
      values[i + j] = -z;
  }

  HYPRE_SStructMatrixSetBoxValues(A, 0, tempLower, tempUpper, 0, nentries,
				  stencil_indices, values);

  free(values);
  /* stdout brought back */
  revertStdOut();
}

/*!
 * This function computes cell oxygen consumption function based on
 * the interpolated cell density field.
 */
void tempEnvInitBC()
{
  int i, j, k;
  int m;
  int nvalues;
  int nentries;
  double *values, *bvalues;
  double z;
  z = dt / (gridResolution * gridResolution);
  /* stdout redirected to file */
  switchStdOut(tfname);

  /* 5. SETUP STRUCT VECTORS FOR B AND X */
  nvalues = gridSize.x * gridSize.y * gridSize.z;

  values = calloc(nvalues, sizeof(double));

  /* create an empty vector object */
  HYPRE_SStructVectorCreate(MPI_CART_COMM, tempGrid, &b);
  HYPRE_SStructVectorCreate(MPI_CART_COMM, tempGrid, &x);

  /* as with the matrix, set the appropriate object type for the vectors */
  HYPRE_SStructVectorSetObjectType(b, tempObjectType);
  HYPRE_SStructVectorSetObjectType(x, tempObjectType);

  /* indicate that the vector coefficients are ready to be set */
  HYPRE_SStructVectorInitialize(b);
  HYPRE_SStructVectorInitialize(x);

  /* set the values */
  m = 0;
  for (k = tempLower[2]; k <= tempUpper[2]; k++)
    for (j = tempLower[1]; j <= tempUpper[1]; j++)
      for (i = tempLower[0]; i <= tempUpper[0]; i++) {
	values[m] = fieldICMean[TEMP];
	m++;
      }

  HYPRE_SStructVectorSetBoxValues(b, 0, tempLower, tempUpper, 0, values);

  m = 0;
  for (k = tempLower[2]; k <= tempUpper[2]; k++)
    for (j = tempLower[1]; j <= tempUpper[1]; j++)
      for (i = tempLower[0]; i <= tempUpper[0]; i++) {
	values[m] = fieldICMean[TEMP];
	m++;
      }

  HYPRE_SStructVectorSetBoxValues(x, 0, tempLower, tempUpper, 0, values);

  free(values);

  /* incorporate boundary conditions; Dirichlet on 1 face; Robin on 7 other faces (low X) */

  /* Robin conditions */
  nentries = 3;
  long long stencilRindices[3];
  int Nmax;
  Nmax = 0;
  Nmax = (Nmax < gridSize.x ? gridSize.x : Nmax);
  Nmax = (Nmax < gridSize.y ? gridSize.y : Nmax);
  Nmax = (Nmax < gridSize.z ? gridSize.z : Nmax);
  values = calloc(nentries * Nmax * Nmax, sizeof(double));
  bvalues = calloc(Nmax * Nmax, sizeof(double));

  for (i = 0; i < Nmax * Nmax; i++)
    bvalues[i] = 2.0 * z * gridResolution * tempLambda * fieldICMean[TEMP];

  if (MPIcoords[MPIrank][0] == MPIdim[0] - 1) {
    nvalues = nentries * gridSize.y * gridSize.z;
    for (i = 0; i < nvalues; i += nentries) {
      values[i] = 2.0 * z * gridResolution * tempLambda;
      values[i + 1] = z;
      values[i + 2] = -z;
    }

    tempSetBoundary(0, 1);

    stencilRindices[0] = 0;
    stencilRindices[1] = 2;
    stencilRindices[2] = 1;

    HYPRE_SStructMatrixAddToBoxValues(A, 0, bcLower, bcUpper, 0, nentries,
				      stencilRindices, values);

    HYPRE_SStructVectorAddToBoxValues(b, 0, bcLower, bcUpper, 0, bvalues);

  }

  if (MPIcoords[MPIrank][1] == 0) {
    nvalues = nentries * gridSize.x * gridSize.z;
    for (i = 0; i < nvalues; i += nentries) {
      values[i] = 2.0 * z * gridResolution * tempLambda;
      values[i + 1] = z;
      values[i + 2] = -z;
    }

    tempSetBoundary(1, -1);

    stencilRindices[0] = 0;
    stencilRindices[1] = 3;
    stencilRindices[2] = 4;

    HYPRE_SStructMatrixAddToBoxValues(A, 0, bcLower, bcUpper, 0, nentries,
				      stencilRindices, values);

    HYPRE_SStructVectorAddToBoxValues(b, 0, bcLower, bcUpper, 0, bvalues);

  }

  if (MPIcoords[MPIrank][1] == MPIdim[1] - 1) {
    nvalues = nentries * gridSize.x * gridSize.z;
    for (i = 0; i < nvalues; i += nentries) {
      values[i] = 2.0 * z * gridResolution * tempLambda;
      values[i + 1] = z;
      values[i + 2] = -z;
    }

    tempSetBoundary(1, 1);

    stencilRindices[0] = 0;
    stencilRindices[1] = 4;
    stencilRindices[2] = 3;

    HYPRE_SStructMatrixAddToBoxValues(A, 0, bcLower, bcUpper, 0, nentries,
				      stencilRindices, values);

    HYPRE_SStructVectorAddToBoxValues(b, 0, bcLower, bcUpper, 0, bvalues);

  }

  if (MPIcoords[MPIrank][2] == 0) {
    nvalues = nentries * gridSize.x * gridSize.y;
    for (i = 0; i < nvalues; i += nentries) {
      values[i] = 2.0 * z * gridResolution * tempLambda;
      values[i + 1] = z;
      values[i + 2] = -z;
    }

    tempSetBoundary(2, -1);

    stencilRindices[0] = 0;
    stencilRindices[1] = 5;
    stencilRindices[2] = 6;

    HYPRE_SStructMatrixAddToBoxValues(A, 0, bcLower, bcUpper, 0, nentries,
				      stencilRindices, values);

    HYPRE_SStructVectorAddToBoxValues(b, 0, bcLower, bcUpper, 0, bvalues);

  }

  if (MPIcoords[MPIrank][2] == MPIdim[2] - 1) {
    nvalues = nentries * gridSize.x * gridSize.y;
    for (i = 0; i < nvalues; i += nentries) {
      values[i] = 2.0 * z * gridResolution * tempLambda;
      values[i + 1] = z;
      values[i + 2] = -z;
    }

    tempSetBoundary(2, 1);

    stencilRindices[0] = 0;
    stencilRindices[1] = 6;
    stencilRindices[2] = 5;

    HYPRE_SStructMatrixAddToBoxValues(A, 0, bcLower, bcUpper, 0, nentries,
				      stencilRindices, values);

    HYPRE_SStructVectorAddToBoxValues(b, 0, bcLower, bcUpper, 0, bvalues);

  }

  free(values);
  free(bvalues);

  /* Dirichlet conditions */
  if (MPIcoords[MPIrank][0] == 0) {

    int nentries = 1;
    long long stencilDindices[1];
    nvalues = nentries * gridSize.y * gridSize.z;
    values = calloc(nvalues, sizeof(double));
    bvalues = calloc(nvalues, sizeof(double));
    for (i = 0; i < nvalues; i++)
      values[i] = z;

    tempSetBoundary(0, -1);

    stencilDindices[0] = 1;

    HYPRE_SStructMatrixAddToBoxValues(A, 0, bcLower, bcUpper, 0, nentries,
				      stencilDindices, values);

    for (i = 0; i < nvalues; i++)
      bvalues[i] = z * fieldBC[TEMP];

    HYPRE_SStructVectorAddToBoxValues(b, 0, bcLower, bcUpper, 0, bvalues);

    free(values);
    free(bvalues);
  }
  /* stdout brought back */
  revertStdOut();
}

/*!
 * This function initializes Hypre for solving temperature field.
 */
void tempEnvInitSolver()
{
  /* stdout redirected to file */
  switchStdOut(tfname);

  HYPRE_SStructMatrixAssemble(A);
  /* This is a collective call finalizing the vector assembly.
     The vector is now ``ready to be used'' */
  HYPRE_SStructVectorAssemble(b);
  HYPRE_SStructVectorAssemble(x);

  HYPRE_SStructMatrixGetObject(A, (void **) &parA);
  HYPRE_SStructVectorGetObject(b, (void **) &parb);
  HYPRE_SStructVectorGetObject(x, (void **) &parx);

  HYPRE_ParCSRPCGCreate(MPI_CART_COMM, &tempSolver);
  HYPRE_ParCSRPCGSetTol(tempSolver, 1.0e-12);
  HYPRE_ParCSRPCGSetPrintLevel(tempSolver, 2);
  HYPRE_ParCSRPCGSetMaxIter(tempSolver, 50);

  HYPRE_BoomerAMGCreate(&tempPrecond);
  HYPRE_BoomerAMGSetMaxIter(tempPrecond, 1);
  HYPRE_BoomerAMGSetTol(tempPrecond, 0.0);
  HYPRE_BoomerAMGSetPrintLevel(tempPrecond, 2);
  HYPRE_BoomerAMGSetCoarsenType(tempPrecond, 6);
  HYPRE_BoomerAMGSetRelaxType(tempPrecond, 6);
  HYPRE_BoomerAMGSetNumSweeps(tempPrecond, 1);

  HYPRE_ParCSRPCGSetPrecond(tempSolver, HYPRE_BoomerAMGSolve,
			    HYPRE_BoomerAMGSetup, tempPrecond);
  HYPRE_ParCSRPCGSetup(tempSolver, parA, parb, parx);
  /* stdout brought back */
  revertStdOut();
}

/*!
 * This function is a driving function for the solving next time step
 * of temperature field.
 */
void tempEnvSolve()
{

  int i, j, k;
  int idx;
  double z;
  double *values;
  long long nvalues = gridSize.x * gridSize.y * gridSize.z;
  z = dt / (gridResolution * gridResolution);
  /* stdout redirected to file */
  switchStdOut(tfname);

  if (tempIter > 0) {

    /* update right hand side */

    values = calloc(nvalues, sizeof(double));

    HYPRE_SStructVectorGetBoxValues(x, 0, tempLower, tempUpper, 0, values);
    HYPRE_SStructVectorSetBoxValues(b, 0, tempLower, tempUpper, 0, values);

    for (i = 0; i < nvalues; i++)
      values[i] =
	  2.0 * z * gridResolution * tempLambda * fieldICMean[TEMP];

    if (MPIcoords[MPIrank][0] == MPIdim[0] - 1) {
      tempSetBoundary(0, 1);
      HYPRE_SStructVectorAddToBoxValues(b, 0, bcLower, bcUpper, 0, values);
    }
    if (MPIcoords[MPIrank][1] == 0) {
      tempSetBoundary(1, -1);
      HYPRE_SStructVectorAddToBoxValues(b, 0, bcLower, bcUpper, 0, values);
    }
    if (MPIcoords[MPIrank][1] == MPIdim[1] - 1) {
      tempSetBoundary(1, 1);
      HYPRE_SStructVectorAddToBoxValues(b, 0, bcLower, bcUpper, 0, values);
    }
    if (MPIcoords[MPIrank][2] == 0) {
      tempSetBoundary(2, -1);
      HYPRE_SStructVectorAddToBoxValues(b, 0, bcLower, bcUpper, 0, values);
    }
    if (MPIcoords[MPIrank][2] == MPIdim[2] - 1) {
      tempSetBoundary(2, 1);
      HYPRE_SStructVectorAddToBoxValues(b, 0, bcLower, bcUpper, 0, values);
    }

    if (MPIcoords[MPIrank][0] == 0) {
      int nentries = 1;
      long long nvalues;
      nvalues = gridSize.x * gridSize.y * gridSize.z;
      for (i = 0; i < nvalues; i++)
	values[i] = z * fieldBC[TEMP];

      tempSetBoundary(0, -1);

      HYPRE_SStructVectorAddToBoxValues(b, 0, bcLower, bcUpper, 0, values);
    }
    free(values);

    HYPRE_SStructVectorAssemble(b);
    HYPRE_SStructVectorAssemble(x);

  }

  HYPRE_ParCSRPCGSolve(tempSolver, parA, parb, parx);

  /* copy solution to field buffer */
  HYPRE_SStructVectorGather(x);
  values = calloc(nvalues, sizeof(double));
  HYPRE_SStructVectorGetBoxValues(x, 0, tempLower, tempUpper, 0, values);
  idx = 0;
  for (k = 0; k < gridSize.z; k++)
    for (j = 0; j < gridSize.y; j++)
      for (i = 0; i < gridSize.x; i++, idx++)
	tempField[gridSize.y * gridSize.z * i + gridSize.z * j + k] =
	    values[idx];
  free(values);

  tempIter++;
  /* stdout brought back */
  revertStdOut();
}
