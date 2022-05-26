#!/bin/sh
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

VISDIR=$1
NPROCS=$2
cd $VISDIR

if command -v povray >/dev/null 2>&1; then
  find . -name '*.pov' | xargs -n 1 -P $NPROCS povray +A +Q11 -D -GA -V
else 
  echo "Error: povray not found."
  exit 1
fi

if command -v composite >/dev/null 2>&1; then
  find . -name '*.png' | xargs -n 1 -P $NPROCS -I file composite ../timothy_logo.png file file
else
  echo "Error: composite not found."
  exit 1
fi

if command -v ffmpeg >/dev/null 2>&1; then
  ffmpeg -threads $NPROCS -framerate 10 -pattern_type glob -i '*.png' -c:v libx264 -pix_fmt yuv420p movie.mp4
else
  echo "Error: ffmpeg not found."
  exit 1
fi
