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

#include "global.h"

/*! \file stats.c
 *  \brief contains functions computing and printing simulation statisctical information
 */

/*!
 * This function computes and prints out density statistics.
 */
void statisticsDensity()
{
  int c;
  double sum = 0.0, mean;
  double globalMaxDens;
  double globalMinDens;
  double deviation;

  statistics.maxdens = 0;
  statistics.mindens = 1024;

  for (c = 0; c < lnc; c++) {
    sum += cells[c].density;
    statistics.maxdens =
	(cells[c].density >
	 statistics.maxdens ? cells[c].density : statistics.maxdens);
    statistics.mindens =
	(cells[c].density <
	 statistics.mindens ? cells[c].density : statistics.mindens);
  }

  MPI_Allreduce(&sum, &mean, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
  MPI_Allreduce(&statistics.maxdens, &globalMaxDens, 1, MPI_DOUBLE,
		MPI_MAX, MPI_COMM_WORLD);
  MPI_Allreduce(&statistics.mindens, &globalMinDens, 1, MPI_DOUBLE,
		MPI_MIN, MPI_COMM_WORLD);
  statistics.maxdens = globalMaxDens;
  statistics.mindens = globalMinDens;

  mean /= nc;
  statistics.densavg = mean;
  sum = 0.0;

  for (c = 0; c < lnc; c++)
    sum += (cells[c].density - mean) * (cells[c].density - mean);

  MPI_Allreduce(&sum, &(statistics.densdev), 1, MPI_DOUBLE, MPI_SUM,
		MPI_COMM_WORLD);

  statistics.densdev /= nc;
  statistics.densdev = sqrt(statistics.densdev);

  if (MPIrank == 0)
    printf("%12s%10.4lf%10.4lf%10.4lf%10.4lf\n", "Density    ",
	   globalMinDens, globalMaxDens, mean, statistics.densdev);
}

/*!
 * This function computes and prints out distance statistics.
 */
void statisticsDistance()
{
  double globalMinDist;
  double globalMaxDist;

  MPI_Allreduce(&statistics.mindist, &globalMinDist, 1, MPI_DOUBLE,
		MPI_MIN, MPI_COMM_WORLD);

  statistics.mindist = globalMinDist;

  if (MPIrank == 0)
    printf("%12s%10.4lf%10s%10s%10s\n", "Distance   ", globalMinDist, "-",
	   "-", "-");
}

/*!
 * This function computes and prints out velocity statistics.
 */
void statisticsVelocity()
{
  MPI_Reduce(&statistics.minvel, &globalMinVel, 1, MPI_DOUBLE, MPI_MIN, 0,
	     MPI_COMM_WORLD);
  MPI_Reduce(&statistics.maxvel, &globalMaxVel, 1, MPI_DOUBLE, MPI_MAX, 0,
	     MPI_COMM_WORLD);
  if (MPIrank == 0)
    printf("%12s%10.4lf%10.4lf%10s%10s\n", "Velocity   ", globalMinVel,
	   globalMaxVel, "-", "-");
}

/*!
 * This function computes and prints out cell size statistics.
 */
void statisticsSize()
{
  double globalMaxSize, globalMinSize;

  MPI_Reduce(&statistics.maxsize, &globalMaxSize, 1, MPI_DOUBLE, MPI_MAX,
	     0, MPI_COMM_WORLD);
  MPI_Reduce(&statistics.minsize, &globalMinSize, 1, MPI_DOUBLE, MPI_MIN,
	     0, MPI_COMM_WORLD);

  if (MPIrank == 0)
    printf("%12s%10.4lf%10.4lf%10s%10s\n", "Size       ", globalMinSize,
	   globalMaxSize, "-", "-");
}

/*!
 * This function computes and prints out phases statistics.
 */
void statisticsPhases()
{
  if (MPIrank == 0) {
    printf("%12s%12s%12s%12s%12s%12s\n", "Cell phase ", "G0", "G1", "S",
	   "G2", "M");
    printf("%12s%12" PRId64 "%12" PRId64 "%12" PRId64 "%12" PRId64 "%12"
	   PRId64 "\n", "N. of cells", g0nc, g1nc, snc, g2nc, mnc);
    printf("\n%16s%12" PRId64 "\n", "Healthy cells  ", nc - cnc - nnc);
    printf("%16s%12" PRId64 "\n", "Cancer cells   ", cnc);
    printf("%16s%12" PRId64 "\n", "Necrotic cells ", nnc);
  }
}

/*!
 * This is a driving function for computing and printing out statistics.
 */
void statisticsPrint()
{
  if (MPIrank == 0)
    printf("%12s%10s%10s%10s%10s\n", "", "Min", "Max", "Avg", "Dev");
  statisticsDensity();
  statisticsDistance();
  /*statisticsVelocity(); */
  statisticsSize();
  if (MPIrank == 0)
    printf("\n");
  statisticsPhases();
}
