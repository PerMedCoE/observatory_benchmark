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

/*! \file io.h
 *  \brief contains defines and declarations for I/O functions
 */

//#define NPAR 34
#define NPAR 67
#define REAL 1
#define STRING 2
#define INT 3
#define LONG 4
#define INT64_T 5
#define DOUBLE 6
#define CHAR 7

#define NOUT 10
#define NRSTPARAMS 32
#define SCALAR 1
#define VECTOR 2

#define FNLEN 256

int typeOut[NOUT];
char nameOut[NOUT][128];
int dimOut[NOUT];
void *addrOut[NOUT];
int64_t jumpOut[NOUT];
int nfOut;

int typeRst[NRSTPARAMS];
int sizeRst[NRSTPARAMS];
void *addrRst[NRSTPARAMS];
int nRst;
/* simulation parameters from the restart file */
int rstSdim;
int rstNx;
int rstNy;
int rstNz;
char rstOutdir[128];
char rstRng[3];
int64_t rstNc;
int rstSimStart;
float rstTstep;
float rstSimTime;
float rstFrac;
float rstG1;
float rstS;
float rstG2;
float rstM;
float rstV;
float rstRd;
double rstH;
double rstCsize;


int one=1;

char params[NPAR][64];
char desc[NPAR][512];
void *addr[NPAR];
int req[NPAR];
int set[NPAR];
int type[NPAR];

int fdSave;
int fdNew;

typedef struct colormapPoint_t {
  float position;
  float r;
  float g;
  float b;
} colormapPoint;

typedef struct colormap_t {
  char name[16];
  int ncp;
  colormapPoint *cp;
} colormap;

colormap *cmaps;
float beta;
