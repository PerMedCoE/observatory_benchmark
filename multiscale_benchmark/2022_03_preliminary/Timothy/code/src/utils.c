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
#include <string.h>
#include <inttypes.h>
#include <mpi.h>
#include <unistd.h>

#if defined(__bg__) && defined(__bgq__)
#include <spi/include/kernel/process.h>
#include <spi/include/kernel/location.h>
#endif

#include "global.h"
//#include "comm.h"

/*! \file utils.c
 *  \brief contains various utility functions
 */

/*!   
 * This function checks the endiannes of the system
 */
int checkEndiannes()
{
  volatile uint32_t i = 0x01234567;
  /* return 0 for big endian, 1 for little endian. */
  endian = (*((uint8_t *) (&i))) == 0x67;
  return 0;
}

/*!
 * This function swaps endiannes within a table of n elements 
 * of a given size m (given in bytes).
 */
void swap_Nbyte(char *data, int n, int m)
{
  int i, j;
  char old_data[16];

  for (j = 0; j < n; j++) {
    memcpy(&old_data[0], &data[j * m], m);
    for (i = 0; i < m; i++)
      data[j * m + i] = old_data[m - i - 1];
  }
}

/*!
 * This function is used to handle various critical errors.
 */
void stopRun(int ierr, char *name, char *file, int line)
{
  switch (ierr) {
  case 100:
    fprintf(stderr, "Bad %s dimensions at %s, line %d\n", name, file,
	    line);
    break;
  case 101:
    if (MPIrank == 0)
      fprintf(stderr,
	      "Number of processes must be a power of two at %s, line %d\n",
	      file, line);
    break;
  case 102:
    if (MPIrank == 0) {
      fprintf(stderr,
	      "Bad or missing Program parameters, at %s, line %d\n", file,
	      line);
      fprintf(stderr, "Usage:\n");
      fprintf(stderr, "mpiexec -n NPROC ./timothy -p <ParameterFile>\n");
    }
    break;
  case 103:
    fprintf(stderr, "Failed %s MPI message at %s, line %d.\n", name, file,
	    line);
    break;
  case 106:
    fprintf(stderr,
	    "Failed to allocate memory for %s array at %s, line %d\n",
	    name, file, line);
    break;
  case 107:
    fprintf(stderr, "Too many exported particles. Adjust parameters.\n");
    break;
  case 108:
    fprintf(stderr,
	    "Size of float does not divide the statistics table size.\n");
    break;
  case 109:
    fprintf(stderr, "Max. number of cells per process exceeded.\n");
    break;
  case 110:
    fprintf(stderr, "Too many exported cells on process %d. Abort.\n",
	    MPIrank);
    break;
  case 111:
    fprintf(stderr,
	    "Error while reading simulation parameters. MAXMOVE out of range.\n");
    break;
  case 112:
    fprintf(stderr, "Error in Zoltan library at %s, line %d.\n", file,
	    line);
    break;
  case 113:
    fprintf(stderr,
	    "Error while opening povray output file at %s, line %d.\n",
	    file, line);
    break;
  case 114:
    fprintf(stderr, "Field parameter %s missing at %s, line %d.\n", name,
	    file, line);
    break;
  case 115:
    fprintf(stderr,
	    "Number of cells in the restart file is larger than MAXCELLS parameter at %s, line %d.\n",
	    file, line);
    break;
  case 116:
    fprintf(stderr, "Bad value for parameter %s at %s, line %d.\n", name,
	    file, line);
    break;
  case 666:
    fprintf(stderr, "Some devilish error at %s, line %d (lcf)\n", file,
	    line);
    break;
  case 898:
    fprintf(stderr, "Error. tree_create_child_node()\n");
    break;
  case 999:
    break;
  default:
    if (MPIrank == 0)
      fprintf(stderr, "Error at %s, line %d\n", file, line);
    break;
  }
  fflush(stderr);
  MPI_Finalize();
  exit(1);
}

/*!
 * This function detects the amount of addressable memory available for each process.
 * Assumptions: each process allocates similar amount of data.
 * This functions is system dependent. Supported platforms: linux, AIX, Blue Gene/Q.
 */
size_t getMemoryPerProcess(int32_t lsize)
{
#if defined(__bg__) && defined(__bgq__)
  Personality_t pers;
  int32_t msize;
  Kernel_GetPersonality(&pers, sizeof(pers));
  msize = pers.DDR_Config.DDRSizeMB;
#else
#if defined(_AIX)
  int msize = sysconf(_SC_AIX_REALMEM) / 1024;
#endif				/* aix */
#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
  long psize = sysconf(_SC_PAGE_SIZE);
  long npages = sysconf(_SC_PHYS_PAGES);
  long msize = psize * npages / (1024 * 1024);
#endif				/*linux */
#endif				/* bgq */
  return msize / lsize;
}

/*!
 * This function detects number of processes on each node and assignes
 * local node ranks for each process.
 * Assumptions: number of processes per node is equal accross nodes.
 * This functions is system dependent. Supported platforms: linux, AIX, Blue Gene/Q.
 */
void getLocalRankAndSize(int rank, int size, int32_t * lrank,
			 int32_t * lsize)
{
  int i;
  int32_t r, s;
#if defined(__bg__) && defined(__bgq__)
  s = Kernel_ProcessCount();
  r = Kernel_MyTcoord();
#else
  int pnamelen;
  char pname[MPI_MAX_PROCESSOR_NAME];
  char pnametable[size][MPI_MAX_PROCESSOR_NAME];
  MPI_Get_processor_name(pname, &pnamelen);
  MPI_Allgather(pname, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, pnametable,
		MPI_MAX_PROCESSOR_NAME, MPI_CHAR, MPI_COMM_WORLD);
  r = 0;
  s = 0;
  for (i = 0; i < size; i++)
    if (!strcmp(pnametable[rank], pnametable[i])) {
      if (i < rank)
	r++;
      s++;
    }
#endif
  *lrank = r;
  *lsize = s;
}
