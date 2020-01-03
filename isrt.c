/* isrt.c - Insert one node in tree  Version 0.1.0 */
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

/* duplicates allowed */

void isrt(treefmt *node, double num, xxfmt *xx)
   {
   treefmt *newnode;
   if (num < node->num)
      {
      if (node->left != NULL) isrt(node->left,num,xx);
      else
         {
	 newnode = (treefmt *) treeinit();
	 newnode->num = num;
	 node->left = (treefmt *) newnode;
	 } /* else leaf node */
      } /* if less than */
   else if (num > node->num)
      {
      if (node->rght != NULL) isrt(node->rght,num,xx);
      else
         {
	 newnode = (treefmt *) treeinit();
	 newnode->num = num;
	 node->rght = (treefmt *) newnode;
	 } /* else leaf node */
      } /* if greater than */
   else
      {
      newnode = (treefmt *) treeinit();
      newnode->num = num;
      node->rght = (treefmt *) newnode;
      xx->duplicates += 1.0;
      } /* duplicate number */
   } /* isrt */
