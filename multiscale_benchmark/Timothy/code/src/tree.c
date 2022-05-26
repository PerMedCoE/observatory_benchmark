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
#include "inline.h"

/*! \file tree.c
 *  \brief contains tree build functions 
 */

/* lookup table used in tree construction */
double tci[8][3] = { {-1, -1, -1}, {-1, 1, -1}, {1, -1, -1}, {1, 1, -1},
{-1, -1, 1}, {-1, 1, 1}, {1, -1, 1}, {1, 1, 1},
};

/*!
 * This function checks whether the cell is inside the node box.
 */
static inline int cellInNode(int c, struct bht_node *node)
{

  double xmin, xmax, ymin, ymax, zmin, zmax;
  double l;
  double x, y, z;
  int an;
  l = node->len * 0.5;
  x = cells[c].x;
  y = cells[c].y;
  z = cells[c].z;

  xmin = node->center[0] - l;
  ymin = node->center[1] - l;
  if (sdim == 3)
    zmin = node->center[2] - l;
  if (sdim == 2)
    zmin = 0.0;
  xmax = node->center[0] + l;
  ymax = node->center[1] + l;
  if (sdim == 3)
    zmax = node->center[2] + l;
  if (sdim == 2)
    zmax = 0.0;

  if (x <= xmax && x > xmin && y <= ymax && y > ymin
      && (sdim == 2 || (z <= zmax && z > zmin)))
    return 1;

  return 0;
}


/*!
 * This function checks which child node contains a given cell.
 */
static inline int whichChildNode(int p, struct bht_node *node)
{

  int i, j, k;
  int num = 0;
  double x_min, x_max, y_min, y_max, z_min, z_max;
  double x, y, z;
  double cx, cy, cz;
  double shift;
  int idx;

  shift = node->len * 0.25;
  x = cells[p].x;
  y = cells[p].y;
  z = cells[p].z;
  for (i = 0; i < tnc; i++) {
    cx = node->center[0] + tci[i][0] * shift;
    cy = node->center[1] + tci[i][1] * shift;
    if (sdim == 3)
      cz = node->center[2] + tci[i][2] * shift;
    if (sdim == 2)
      cz = 0.0;
    x_min = cx - shift;
    x_max = cx + shift;
    y_min = cy - shift;
    y_max = cy + shift;
    if (sdim == 3)
      z_min = cz - shift;
    else
      z_min = 0.0;
    if (sdim == 3)
      z_max = cz + shift;
    else
      z_max = 0.0;
    if (sdim == 3) {
      if (x > x_min && x <= x_max && y > y_min && y <= y_max && z > z_min
	  && z <= z_max)
	break;
    } else if (x > x_min && x <= x_max && y > y_min && y <= y_max)
      break;
    num++;
  }

  if (node->child[num] == NULL) {
#pragma omp critical
    {
      idx = ni;
      ni++;
    }
    node->child[num] = &tree[idx];
    node->child[num]->len = node->len * 0.5;
    node->child[num]->center[0] = cx;
    node->child[num]->center[1] = cy;
    node->child[num]->center[2] = cz;
    node->child[num]->father = node;
    node->child[num]->isempty = 1;
    node->child[num]->leaf = 1;
    for (j = 0; j < tnc; j++)
      node->child[num]->child[j] = NULL;
  }

  return num;
}

/*!
 * This function builds an initial tree which is needed for OpenMP parallelization
 */
void treeBuildInitial(int depth, struct bht_node **iroots,
		      struct bht_node *node)
{
  int i, j, k;
  if (depth != 0) {
    double shift;
    shift = node->len * 0.25;
    for (j = 0; j < tnc; j++) {
      node->child[j] = &tree[nnodes_init];
      node->child[j]->len = node->len * 0.5;
      node->child[j]->center[0] = node->center[0] + tci[j][0] * shift;
      node->child[j]->center[1] = node->center[1] + tci[j][1] * shift;
      if (sdim == 3)
	node->child[j]->center[2] = node->center[2] + tci[j][2] * shift;
      if (sdim == 2)
	node->child[j]->center[2] = 0.0;
      node->child[j]->father = node;
      node->child[j]->isempty = 1;
      node->child[j]->leaf = 1;
      node->leaf = 0;
      for (k = 0; k < tnc; k++)
	node->child[j]->child[k] = NULL;
      nnodes_init++;
      treeBuildInitial(depth - 1, iroots, node->child[j]);
    }
  } else {
    node->leaf = 1;
    node->partnum = -1;		/* indicates an empty node */
    iroots[ni] = node;
    ni++;
  }
}

/*!
 * This function builds an octree for local cells. 
 */
void treeBuild()
{

  int i, j;
  int pow2, idepth, pparts, k, l;
  int maxTreeSize;
  struct bht_node *node;
  struct bht_node **iroots;
  int nnodes_per_thread = 0;

  if (lnc == 0)
    return;
#ifdef DEBUG
  if (MPIrank == 0 && !(step % statOutStep)) {
    printf(" Tree build...");
    fflush(stdout);
  }
#endif
  if (sdim == 3)
    tnc = 8;
  if (sdim == 2)
    tnc = 4;

  nnodes = 0;
  nnodes_init = 0;

  pow2 = 0;
  k = 1;
  while (1) {
    if (k >= OMPthreads || k >= lnc)
      break;
    k = k * 2;
    pow2 += 1;
  }

  idepth = 0;
  l = 1;
  while (1) {
    if (l >= k)
      break;
    l = l * tnc;
    idepth += 1;
  }

  if (!
      (iroots =
       (struct bht_node **) malloc(l * sizeof(struct bht_node *))))
    stopRun(106, "iroots", __FILE__, __LINE__);

  pparts = l / k;

  /* allocate memory for the leafs table */
  if (!
      (leafs =
       (struct bht_node **) malloc(lnc * sizeof(struct bht_node *))))
    stopRun(106, "leafs", __FILE__, __LINE__);

  maxTreeSize = lnc * 16;

  if (!
      (tree =
       (struct bht_node *) malloc(maxTreeSize * sizeof(struct bht_node))))
    stopRun(106, "tree", __FILE__, __LINE__);

  bht_root = &tree[0];

  nnodes_init = 1;


  boxmin[0] = nx;
  boxmin[1] = nx;
  boxmin[2] = nx;
  boxmax[0] = -nx;
  boxmax[1] = -nx;
  boxmax[2] = -nx;

  for (i = 0; i < lnc; i++) {
    boxmin[0] = (cells[i].x < boxmin[0] ? cells[i].x : boxmin[0]);
    boxmax[0] = (cells[i].x > boxmax[0] ? cells[i].x : boxmax[0]);
    boxmin[1] = (cells[i].y < boxmin[1] ? cells[i].y : boxmin[1]);
    boxmax[1] = (cells[i].y > boxmax[1] ? cells[i].y : boxmax[1]);
    boxmin[2] = (cells[i].z < boxmin[2] ? cells[i].z : boxmin[2]);
    boxmax[2] = (cells[i].z > boxmax[2] ? cells[i].z : boxmax[2]);
  }

  boxsize = boxmax[0] - boxmin[0];
  boxsize =
      (boxmax[1] - boxmin[1] > boxsize ? boxmax[1] - boxmin[1] : boxsize);
  boxsize =
      (boxmax[2] - boxmin[2] > boxsize ? boxmax[2] - boxmin[2] : boxsize);
  boxsize += 0.1;

  /* set up the root node */
  bht_root->len = boxsize;
  bht_root->center[0] = boxmin[0] + (boxmax[0] - boxmin[0]) / 2.0;
  bht_root->center[1] = boxmin[1] + (boxmax[1] - boxmin[1]) / 2.0;
  if (sdim == 3)
    bht_root->center[2] = boxmin[2] + (boxmax[2] - boxmin[2]) / 2.0;
  if (sdim == 2)
    bht_root->center[2] = 0.0;

  bht_root->leaf = 1;
  bht_root->isempty = 1;
  bht_root->father = NULL;

  for (i = 0; i < tnc; i++)
    bht_root->child[i] = NULL;

  ni = 0;

  treeBuildInitial(idepth, iroots, bht_root);

  ni = nnodes_init;

  /* stop if there are no particles in this process */
  if (lnc == 0)
    return;

#pragma omp parallel num_threads(k) private(node,i,j) firstprivate(pparts) shared(ni)
  {
    int OMPid;

    OMPid = omp_get_thread_num();

    node = bht_root;

    /* loop over cells - each cell is inserted into its own octree location */
    for (i = 0; i < lnc; i++) {
      int mycell = 0;
      int c;
      int s;
      struct bht_node *no;

      no = node;

      for (j = 0; j < pparts; j++) {
	mycell = cellInNode(i, iroots[OMPid * pparts + j]);
	if (mycell == 1) {
	  no = iroots[OMPid * pparts + j];
	  break;
	}
      }

      if (mycell == 0)
	continue;

      /* this loop iterates until given cell p is inserted into its location */
      while (1) {
	/* if this node is not a leaf we continue searching */
	if (no->leaf == 0) {
	  c = whichChildNode(i, no);
	  no = no->child[c];
	  /* if this node is a leaf and it is not empty we need to move cells */
	} else if (no->leaf == 1 && no->isempty == 0) {
	  for (s = 0; s < tnc; s++)
	    no->child[s] = NULL;
	  no->leaf = 0;
	  c = whichChildNode(no->partnum, no);
	  no->child[c]->partnum = no->partnum;
	  no->child[c]->isempty = 0;
	  leafs[no->partnum] = no->child[c];
	  c = whichChildNode(i, no);
	  no = no->child[c];
	  /* if this node is a leaf and it is empty we insert cell into the node */
	} else {
	  no->partnum = i;
	  no->isempty = 0;
	  leafs[i] = no;
	  break;
	}
      }

    }

  }				/* end of OpenMP parallel region */

  free(iroots);
#ifdef DEBUG
  if (MPIrank == 0 && !(step % statOutStep)) {
    printf("done\n");
    fflush(stdout);
  }
#endif
}

/*!
 * This function dealocates arrays used in tree building
 */
void treeFree()
{
  free(tree);
  free(leafs);
}
