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
#include <float.h>

#include "global.h"
#include "inline.h"

/*! \file gradient.c
 *  \brief contains functions that compute potential gradient
 */

/*!
 *  This function computes potential gradient for two neighbour cells.
 * mode=0 - computations for local cells
 * mode=1 - computations for remote cells
 */
void computeCCgradient(int p1, int p2, int mode)
{

  double pot;
  double dist;
  double g;
  double grad[3];
  double m = 1.0;		/* we assume that cells' mass is always 1.0 */
  double sc;
  double x1, x2, y1, y2, z1, z2;
  double v, density, size;
  double r;

  if (p1 == p2 && mode == 0)
    return;

  if (mode == 0) {
    x1 = cells[p1].x;
    x2 = cells[p2].x;
    y1 = cells[p1].y;
    y2 = cells[p2].y;
    z1 = cells[p1].z;
    z2 = cells[p2].z;
    v = cells[p2].v;
    density = cells[p2].density;
    size = cells[p2].size;
  }
  if (mode == 1) {
    x1 = recvData[p1].x;
    x2 = cells[p2].x;
    y1 = recvData[p1].y;
    y2 = cells[p2].y;
    z1 = recvData[p1].z;
    z2 = cells[p2].z;
    v = recvDensPotData[p1].v;
    density = recvDensPotData[p1].density;
    size = recvData[p1].size;
  }

  if (sdim == 2)
    r = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  if (sdim == 3)
    r = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) +
	     (z1 - z2) * (z1 - z2));

  grad[0] = 0.0;
  grad[1] = 0.0;
  grad[2] = 0.0;

  /* compute the gradient of SPH kernel function */
  sph_kernel_gradient(p1, p2, grad, mode, r);

  if (density == 0.0)
    sc = 0.0;
  else {
    m = size / csize;
    sc = (m / density) * v;
  }

  /* update forces */
  if (mode == 0) {
    velocity[p1].x += sc * grad[0];
    velocity[p1].y += sc * grad[1];
    velocity[p1].z += sc * grad[2];
  } else {
    velocity[p2].x -= sc * grad[0];
    velocity[p2].y -= sc * grad[1];
    velocity[p2].z -= sc * grad[2];
  }

}

/*!
 * This function traverses the subtree under given node looking for neighbour cells.
 */
void gradientTraverseSubtree(int p, struct bht_node *no)
{

  int s;

  if (no->partnum == -1)
    return;

  /* if it is a leaf node we do not proceed to the siblings */
  if (no->leaf == 1) {
    if (lnc > 0)
      computeCCgradient(p, no->partnum, 0);
    return;
  }

  /* loop over siblings */
  for (s = 0; s < tnc; s++) {
    /* if it is an empty child proceed to the next one */
    if (no->child[s] == NULL || no->child[s]->partnum == -1)
      continue;
    /* if there is no intersection with this child proceed to next one */
    if (!cellIntersectNode
	(cells[p].x, cells[p].y, cells[p].z, cells[p].h, no->child[s]))
      continue;
    /* if it is an leaf child compute the potential */
    if (no->child[s]->leaf == 1) {
      computeCCgradient(p, no->child[s]->partnum, 0);
    } else {
      gradientTraverseSubtree(p, no->child[s]);
    }
  }
}

/*!
 * This function traverse the tree (up-bottom) and computes potential gradient for remote cells.
 */
void computeRemoteCellsPotentialGradient(int rp, struct bht_node *no)
{

  int s;

  if (lnc == 0)
    return;
  if (no->partnum == -1)
    return;

  /* compute potential if it is a leaf node */
  if (no->leaf == 1) {
    computeCCgradient(rp, no->partnum, 1);
    return;
  }

  /* loop over all siblings */
  for (s = 0; s < tnc; s++) {
    /* continue if there is no child */
    if (no->child[s] == NULL || no->child[s]->partnum == -1)
      continue;
    /* proceed if the child node and particle intersect */
    if (cellIntersectNode
	(recvData[rp].x, recvData[rp].y, recvData[rp].z, recvData[rp].h,
	 no->child[s]))
      computeRemoteCellsPotentialGradient(rp, no->child[s]);
  }
}

/*!
 * This function computes the potential gradient with the use of SPH method for all local cells.
 */
int computePotentialGradient()
{
  int p, s;
  struct bht_node *no;
  double dvel;
  double sf;
#ifdef DEBUG
  if (MPIrank == 0 && !(step % statOutStep)) {
    printf(" Potential gradient...");
    fflush(stdout);
  }
#endif
  densPotExchangeInit();

  /* loop over all local cells */
#pragma omp parallel for private(p,s,no)	//schedule(dynamic)
  for (p = 0; p < lnc; p++) {
    velocity[p].x = 0.0;
    velocity[p].y = 0.0;
    velocity[p].z = 0.0;
    /* set the pointer to the node that owns the cell */
    no = leafs[p];
    /* traverse the tree (bottom-up) */
    while (1) {
      if (no->father == NULL)
	break;
      /* loop over siblings */
      for (s = 0; s < tnc; s++) {
	/* "Son of my father but not my brother. It's me." Hairdresser */
	if ((no->father->child[s] == NULL) || (no->father->child[s] == no)
	    || (no->father->child[s]->partnum == -1))
	  continue;
	if (cellIntersectNode
	    (cells[p].x, cells[p].y, cells[p].z, cells[p].h,
	     no->father->child[s])) {
	  /* traverse subtree of the sibling (up-bottom) */
	  gradientTraverseSubtree(p, no->father->child[s]);
	}

      }
      no = no->father;
      if (no->father == NULL)
	break;			/* this is the root node */
      if (cellInsideNode(p, no))
	break;
    }
  }

  densPotExchangeWait();

  /* loop over imported cells */
  for (p = 0; p < numImp; p++) {
    /* start with the root node */
    no = bht_root;
    /* traverse the tree starting from the root and compute potential */
    computeRemoteCellsPotentialGradient(p, no);

  }

  for (p = 0; p < lnc; p++) {
    dvel =
	sqrt(velocity[p].x * velocity[p].x +
	     velocity[p].y * velocity[p].y +
	     velocity[p].z * velocity[p].z);
    if (dvel < statistics.minvel)
      statistics.minvel = dvel;
    if (dvel > statistics.maxvel)
      statistics.maxvel = dvel;
    if (cells[p].size < statistics.minsize)
      statistics.minsize = cells[p].size;
    if (cells[p].size > statistics.maxsize)
      statistics.maxsize = cells[p].size;
  }
  /* this should be removed soon (do we really need to reduceall here?) */
  MPI_Allreduce(&statistics.minvel, &globalMinVel, 1, MPI_DOUBLE, MPI_MIN,
		MPI_COMM_WORLD);
  MPI_Allreduce(&statistics.maxvel, &globalMaxVel, 1, MPI_DOUBLE, MPI_MAX,
		MPI_COMM_WORLD);

  if (globalMaxVel == 0.0)
    sf = 0.0;
  else
    sf = maxSpeedInUnits * secondsPerStep / globalMaxVel;

  statistics.minvel = DBL_MAX;	/* minimal velocity is set to DBL_MAX */
  statistics.maxvel = 0;	/* maximal velocity is set to zero */

  for (p = 0; p < lnc; p++) {
    velocity[p].x *= sf;
    velocity[p].y *= sf;
    velocity[p].z *= sf;
    dvel =
	sqrt(velocity[p].x * velocity[p].x +
	     velocity[p].y * velocity[p].y +
	     velocity[p].z * velocity[p].z);
    if (dvel < statistics.minvel)
      statistics.minvel = dvel;
    if (dvel > statistics.maxvel)
      statistics.maxvel = dvel;
  }
#ifdef DEBUG
  if (MPIrank == 0 && !(step % statOutStep)) {
    printf("done\n");
    fflush(stdout);
  }
#endif
}
