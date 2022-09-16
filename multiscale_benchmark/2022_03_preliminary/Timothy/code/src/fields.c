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

#include "global.h"
#include "fields.h"

/*! \file
 *  \brief contains driving functions for the global fields
 */

/* Global fields' IDs:
 * 0 - density field
 * 1 - temperature
 * 2 - ??
 * 3 - ??
 */

/*!
 * This function intializes the fields.
 * Various parameters are set and the Hypre initialization of the system is executed.
 */
void fieldsInit()
{
  int nf, i;
  int chf;

  if (!gfields)
    return;

  nf = 0;

  strcpy(fieldName[nf], "density");
  fieldType[nf] = SCALAR_FIELD;
  fieldAddr[nf] =
      (double *) calloc(gridSize.x * gridSize.y * gridSize.z,
			sizeof(double));
  densityField = (double *) fieldAddr[nf];
  for (i = 0; i < gridSize.x * gridSize.y * gridSize.z; i++)
    densityField[i] = 0.0;
  nf++;

  strcpy(fieldName[nf], "temp");
  fieldType[nf] = SCALAR_FIELD;
  fieldAddr[nf] =
      (double *) calloc(gridSize.x * gridSize.y * gridSize.z,
			sizeof(double));
  tempField = (double *) fieldAddr[nf];
  for (i = 0; i < gridSize.x * gridSize.y * gridSize.z; i++)
    tempField[i] = 0.0;
  fieldDiffCoef[nf] = 1 * 1e-5;
  fieldBC[nf] = 42.0;
  fieldICMean[nf] = 36.0;
  fieldICVar[nf] = 0;

  nf++;

  /* set default values for chemical parameters */
  for (chf = 0; chf < NCHEM; chf++) {
    if (chf == 0) {
      strcpy(fieldName[nf], "oxygen");
      fieldDt[nf] = gfDt;
      fieldCriticalLevel1[nf] *= gfDt;	//*(boxVolume/cellVolume);
      fieldCriticalLevel2[nf] *= gfDt;	//*(boxVolume/cellVolume);
    }
    if (chf == 1) {
      strcpy(fieldName[nf], "glucose");
      fieldDt[nf] = secondsPerStep;
    }
    if (chf == 2) {
      strcpy(fieldName[nf], "hydrogenIon");
      fieldDt[nf] = secondsPerStep;
    }
    fieldType[nf] = SCALAR_FIELD;
    fieldAddr[nf] =
	(double *) calloc(gridSize.x * gridSize.y * gridSize.z,
			  sizeof(double));
    chemField[chf] = (double *) fieldAddr[nf];
    for (i = 0; i < gridSize.x * gridSize.y * gridSize.z; i++)
      chemField[chf][i] = 0.0;
    nf++;
  }

  /* initialize temperature field */
  if (temperature) {
    tempEnvInitSystem();
    tempEnvInitBC();
    tempEnvInitSolver();
  }

  /* initialize chemical fields */
  for (i = 0; i < NCHEM; i++) {
    if (i == 0 && !oxygen)
      continue;
    if (i == 1 && !glucose)
      continue;
    if (i == 2 && !hydrogenIon)
      continue;
    chemEnvInitSystem(i);
    chemEnvInitBC(i);
    chemEnvInitSolver(i);
  }
}

/*!
 * This is a driving function for global field solver.
 * It is called in each step of the simulation.
 */
void fieldsSolve()
{
  int i;
  if (!gfields)
    return;
  for (gfIter = 0; gfIter < gfIterPerStep; gfIter++) {
    /* update cell state (if more than one iteration) */
    if (gfIter > 0)
      updateCellStates();
    /* solve temperature field */
    if (temperature)
      tempEnvSolve();
    /* solve chemical fields */
    for (i = 0; i < NCHEM; i++) {
      if (i == 0 && !oxygen)
	continue;
      if (i == 1 && !glucose)
	continue;
      if (i == 2 && !hydrogenIon)
	continue;
      chemEnvSolve(i);
    }
  }
}
