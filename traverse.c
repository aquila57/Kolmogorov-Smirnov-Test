/* traverse.c - Traverse tree in order  Version 0.1.0 */
/* Copyright (C) 2019 aquila57 at github.com */

/* This program is free software; you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License as    */
/* published by the Free Software Foundation; either version 2 of    */
/* the License, or (at your option) any later version.               */

/* This program is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/* GNU General Public License for more details.                      */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to:                        */

   /* Free Software Foundation, Inc.                                 */
   /* 59 Temple Place - Suite 330                                    */
   /* Boston, MA 02111-1307, USA.                                    */

#include "kstest.h"

/* perform the Kolmogorov-Smirnov test while traversing */
/* the binary tree */

void traverse(treefmt *node, xxfmt *xx)
   {
   double diff;
   if (node->left != NULL) traverse(node->left, xx);
   /**********************************************/
   if (xx->sumx > 0.0)
      {
      diff = fabs(node->num - xx->sumx);
      if (diff > xx->maxdiff) xx->maxdiff = diff;
      diff = fabs(node->num - (xx->sumx - xx->deltax));
      if (diff > xx->maxdiff) xx->maxdiff = diff;
      } /* if sumx>0 */
   xx->sumx += xx->deltax;
   /**********************************************/
   if (node->rght != NULL) traverse(node->rght, xx);
   } /* traverse */
