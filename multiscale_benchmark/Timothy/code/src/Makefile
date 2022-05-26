#* **************************************************************************
# * This file is part of Timothy
# *
# * Copyright (c) 2014/15 Maciej Cytowski
# * Copyright (c) 2014/15 ICM, University of Warsaw, Poland
# *
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation; either version 2 of the License, or
# * (at your option) any later version.
# *
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
# *
# * You should have received a copy of the GNU General Public License
# * along with this program; if not, write to the Free Software
# * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
# *
# * *************************************************************************/


CC = mpiicc
OPT = -O2 -fopenmp  -ffast-math -ftree-vectorize -finline-functions -Winline -g
DEFS =
INCLUDES = -I/apps/INTEL/2017.4/impi/2017.3.196/include64 -I/apps/SPRNG/2.0/INTEL/include -I. -I/apps/ZOLTAN/3.83/INTEL/IMPI/include -I/apps/HYPRE/2.24.0/INTEL/IMPI/include -I/apps/PARMETIS/4.0.3/INTEL/IMPI/include -I/apps/PARMETIS/4.0.3/INTEL/IMPI/include/parmetis.h 
LIBS = -lm -L/apps/ZOLTAN/3.83/INTEL/IMPI/lib -lzoltan -L/apps/SPRNG/2.0/lib -lsprng -lgmp -L//apps/HYPRE/2.24.0/INTEL/IMPI/lib -lHYPRE -L/apps/INTEL/2017.4/mkl/lib/intel64 -lmkl_rt -L/apps/PARMETIS/4.0.3/INTEL/IMPI/lib -lparmetis

EXEC = ../timothy

OPTIONS = $(OPT) $(DEFS)

OBJS = main.o io.o utils.o cells.o domdec.o tree.o gradient.o potential.o comm.o stats.o random.o init.o grid.o interp.o fields.o tempf.o chemf.o vessel.o

INCL = global.h io.h inline.h fields.h

CFLAGS = $(OPTIONS) $(INCLUDES) 

$(EXEC): $(OBJS)
	$(CC) $(OPTIONS) $(OBJS) $(LIBS) -o $(EXEC)

$(OBJS): $(INCL)

clean:
	rm -f $(OBJS); rm -f $(EXEC)

doc:
	doxygen Doxyfile


