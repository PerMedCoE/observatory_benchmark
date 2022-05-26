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

/*! \file vessel.c
 *  \brief contains functions defining virtual vessels
 */

/*!
 * This functions builds a tube vessel from spheres.
 */
int initVessel()
{
  int i, j, k;
  int lenght;
  int nEndothelial;
  int nRings;
  double intersect;
  double circumradius;
  double startPoint[3];
  double direction[3];
  double point[3];
  double radius[3];
  double t;
  double angle;

  if (MPIrank == 0) {

    startPoint[0] = nx / 2.0;
    startPoint[1] = ny / 2.0;
    startPoint[2] = 0.05 * nz;

    direction[0] = 0.0;
    direction[1] = 0.0;
    direction[2] = 0.1;

    t = sqrt(direction[0] * direction[0] + direction[1] * direction[1] +
	     direction[2] * direction[2]);

    direction[0] /= t * 2 * csize * (1.0 - intersect);
    direction[1] /= t * 2 * csize * (1.0 - intersect);
    direction[2] /= t * 2 * csize * (1.0 - intersect);

    lenght = nz;
    nEndothelial = 8;
    intersect = 0.2;

    circumradius =
	(2 * csize * (1.0 - intersect)) / (2 *
					   sin(M_PI /
					       (double) nEndothelial));
    printf("circumradius=%f\n", circumradius);

    nRings = lenght / (2 * csize * (1.0 - intersect));

    printf("nRings=%d\n", nRings);
    printf("lnc=%" PRId64 "\n", lnc);

    angle = (360 / nEndothelial) * (M_PI / 180);

    radius[0] = 0.0;
    radius[1] = 1.0;
    radius[2] = 0.0;

    lnc = 0;

    for (i = 0; i < nRings; i++) {
      point[0] = startPoint[0];
      point[1] = startPoint[1];
      point[2] = startPoint[2];
      for (j = 0; j < nEndothelial; j++) {
	double x, y;
	double alpha;
	x = radius[0];
	y = radius[1];
	alpha = j * angle;
	radius[0] = x * cos(alpha) - y * sin(alpha);
	radius[1] = x * sin(alpha) + y * cos(alpha);
	radius[2] = 0.0;	//i*csize*(1.0-intersect);
	t = sqrt(pow(radius[0], 2) + pow(radius[1], 2) +
		 pow(radius[2], 2));
	radius[0] /= t;
	radius[1] /= t;
	radius[2] /= t;
	radius[2] = i * csize * (1.0 - intersect);
	cells[lnc].x = point[0] + circumradius * radius[0];
	cells[lnc].y = point[1] + circumradius * radius[1];
	cells[lnc].z = point[2] + radius[2];
	cells[lnc].size = csize;
	lnc++;
      }
    }

  }
}
