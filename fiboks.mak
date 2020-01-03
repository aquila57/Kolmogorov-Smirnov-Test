#  fiboks.mak - Compile fiboks.c Version 0.1.0
#  Copyright (C) 2019 aquila57 at github.com

#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of
#  the License, or (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to:

   #  Free Software Foundation, Inc.
   #  59 Temple Place - Suite 330
   #  Boston, MA 02111-1307, USA.

OBJ=eeglks.o \
	getks.o \
	treeinit.o \
	isrt.o \
	rmtree.o \
	traverse.o \
	freeall.o \
	eeglinit.o \
	eegl.o \
	eeglpwr.o \
	eeglfrac.o

CC=gcc

CFLAGS=-c -Wall -O2

LDFLAGS=-lgsl -lgslcblas -lm

fiboks:				$(OBJ)
		$(CC) -Wall -O2 $(OBJ) -o fiboks $(LDFLAGS)

fiboks.o:				fiboks.c
		$(CC) $(CFLAGS) fiboks.c

getks.o:			getks.c
		$(CC) $(CFLAGS) getks.c

treeinit.o:			treeinit.c
		$(CC) $(CFLAGS) treeinit.c

isrt.o:				isrt.c
		$(CC) $(CFLAGS) isrt.c

rmtree.o:			rmtree.c
		$(CC) $(CFLAGS) rmtree.c

traverse.o:			traverse.c
		$(CC) $(CFLAGS) traverse.c

freeall.o:			freeall.c
		$(CC) $(CFLAGS) freeall.c

eeglinit.o:			eeglinit.c
		$(CC) $(CFLAGS) eeglinit.c

eegl.o:				eegl.c
		$(CC) $(CFLAGS) eegl.c

eeglpwr.o:			eeglpwr.c
		$(CC) $(CFLAGS) eeglpwr.c

eeglfrac.o:			eeglfrac.c
		$(CC) $(CFLAGS) eeglfrac.c

clean:
		rm -f $(OBJ) fiboks
