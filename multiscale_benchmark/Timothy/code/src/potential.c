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
#include <float.h>
#include <math.h>

#include "global.h"
#include "inline.h"

/*! \file potential.c
 *  \brief contains functions that compute the potential
 */

/*!
 * This function computes potential for two neighbour cells.
 * mode=0 - computations for local cells
 * mode=1 - computations for remote cells
 */
double computeCCPotential(int p1, int p2, int mode)
{
  double pot;
  double dist;
  double size;
  double g;
  double x, y, z;
  double xc;
  double D;
  double poisson = 0.33;
  double young;

  if (mode == 0 && p1 == p2)
    return 0.0;

  if (mode == 0) {
    x = cells[p1].x;
    y = cells[p1].y;
    z = cells[p1].z;
    size = cells[p1].size;
    young = cells[p1].young;
  }
  if (mode == 1) {
    x = recvData[p1].x;
    y = recvData[p1].y;
    z = recvData[p1].z;
    size = recvData[p1].size;
    young = recvData[p1].young;
  }

  /* compute the distance between two cells */
  if (sdim == 2)
    dist =
	sqrt((x - cells[p2].x) * (x - cells[p2].x) +
	     (y - cells[p2].y) * (y - cells[p2].y));
  if (sdim == 3)
    dist =
	sqrt((x - cells[p2].x) * (x - cells[p2].x) +
	     (y - cells[p2].y) * (y - cells[p2].y) + (z -
						      cells[p2].z) * (z -
								      cells
								      [p2].
								      z));

  if (statistics.mindist > dist)
    statistics.mindist = dist;

  if (dist <= h) {

    double r01, r02;
    double area;
    double sc;

    if (sdim == 2)
      sc = h2;
    if (sdim == 3)
      sc = h3;

    if (mode == 0) {
      cells[p1].density +=
	  sc * (cells[p2].size / csize) * sph_kernel(dist);
    }
    if (mode == 1) {
      cells[p2].density += sc * (size / csize) * sph_kernel(dist);
    }

    xc = size + cells[p2].size - dist;

    if (xc <= 0.0)
      return 0.0;

    D = 0.75 * ((1.0 - poisson * poisson) / young +
		(1.0 - poisson * poisson / cells[p2].young));

    /* adhesion */
    r01 =
	(size * size - cells[p2].size * cells[p2].size +
	 dist * dist) / (2 * dist);
    r02 = dist - r01;

    area =
	M_PI *
	((size * size * (size - r01) -
	  (size * size * size - r01 * r01 * r01) / 3) +
	 (cells[p2].size * cells[p2].size * (cells[p2].size - r02) -
	  (cells[p2].size * cells[p2].size * cells[p2].size -
	   r02 * r02 * r02) / 3));

    /* compute potential */
    pot =
	(2.0 * pow(xc, 5 / 2) / (5.0 * D)) * sqrt((size * cells[p2].size) /
						  (size +
						   cells[p2].size)) +
	area * 0.1;

    return pot;

  } else
    return 0.0;

}


/*!
 * This function traverses the subtree under given node looking for neighbour cells.
 */
void potentialTraverseSubtree(int p, struct bht_node *no)
{
  int s;

  if (no->partnum == -1)
    return;

  /* if it is a leaf node we do not proceed to the siblings */
  if (no->leaf == 1) {
    if (lnc > 0)
      cells[p].v += computeCCPotential(p, no->partnum, 0);
    return;
  }

  /* loop over siblings */
  for (s = 0; s < tnc; s++) {
    /* if it is an empty child proceed to the next one */
    if ((no->child[s] == NULL) || (no->child[s]->partnum == -1))
      continue;
    /* if there is no intersection with this child proceed to next one */
    if (!cellIntersectNode
	(cells[p].x, cells[p].y, cells[p].z, cells[p].h, no->child[s]))
      continue;
    potentialTraverseSubtree(p, no->child[s]);
  }
}

/*!
 * This function traverse the tree (up-bottom) and computes potential for remote cells.
 */
void computeRemoteCellsPotential(int rp, struct bht_node *no)
{
  int s;

  if (lnc == 0)
    return;
  if (no->partnum == -1)
    return;

  /* compute potential if it is a leaf node */
  if (no->leaf == 1) {
    if (lnc > 0)
      cells[no->partnum].v += computeCCPotential(rp, no->partnum, 1);
    return;
  }

  /* loop over all siblings */
  for (s = 0; s < tnc; s++) {
    /* continue if there is no child */
    if (no->child[s] == NULL || no->child[s]->partnum == -1)
      continue;
    /* proceed if the child node and particle intersect */
    if (!cellIntersectNode
	(recvData[rp].x, recvData[rp].y, recvData[rp].z, recvData[rp].h,
	 no->child[s]))
      continue;
    computeRemoteCellsPotential(rp, no->child[s]);
  }
}

/*!
 * This function computes potential for all local cells.
 */
void computePotentialField()
{
  int p, rp;
  int s;
  struct bht_node *no;

  if (nc > 1)
    statistics.mindist = nx;	/* minimal distance is set to the box size */
  else
    statistics.mindist = 0.0;
  statistics.minvel = DBL_MAX;	/* minimal velocity is set to DBL_MAX */
  statistics.maxvel = 0;	/* maximal velocity is set to zero */
  statistics.minsize = DBL_MAX;	/* minimal size is set to DBL_MAX */
  statistics.maxsize = 0;	/* maximal size is set to zero */

  if (lnc == 0)
    return;

  /* initiate asynchronous data transfers between processors */
  cellsExchangeInit();

  /* loop over all local cells */
  //#pragma omp parallel for private(p,s,no) schedule(dynamic)
#pragma omp parallel for private(p,s,no)
  for (p = 0; p < lnc; p++) {

    cells[p].density = 0.0;
    cells[p].v = 0.0;

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
	  potentialTraverseSubtree(p, no->father->child[s]);
	}
      }

      no = no->father;
      if (no->father == NULL)
	break;			/* this is the root node */
      if (cellInsideNode(p, no))
	break;

    }

  }

  /* wait for data transfers to finish */
  cellsExchangeWait();

  /* loop over remote cells */
  for (rp = 0; rp < numImp; rp++) {
    /* start with the root node */
    no = bht_root;
    /* traverse the tree and compute potential (starting from the root) */
    computeRemoteCellsPotential(rp, no);

  }
}

/*!
 * This is a driving routine for the potential computations.
 */
void computePotential()
{
#ifdef DEBUG
  if (MPIrank == 0 && !(step % statOutStep)) {
    printf(" Potential computations...");
    fflush(stdout);
  }
#endif

  computePotentialField();

#ifdef DEBUG
  if (MPIrank == 0 && !(step % statOutStep)) {
    printf("done\n");
    fflush(stdout);
  }
#endif
}
