/* srandks.c - KS Test, subrand generator  Version 0.1.0 */
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

/* This program runs the Kolmogorov-Smirnov test on the */
/* subrand random number generator, created by Professor */
/* Donald E. Knuth at Stanford University.  */
/* subrand is a subtractive generator.                       */
/* state[n] = state[n-1] - state[n-2]                        */
/* if (state[n] < 0) state[n] += MOD                         */
/* where MOD is 10^9                                         */
/* The subrand generator here has been taken from            */
/* http://rosettacode.org/wiki/Subtractive_generator#C       */
/* The subrand generator passes the Kolmogorov-Smirnov test  */
/* only with certain seeds.                                  */
/* Duplicate random numbers in srand occur as much as 4      */
/* times more frequently than they do in strong generators.  */

/* initialize the state array for the subrand generator */

void subrand_seed(xxfmt *xx, int p1)
	{
	int i;
	int j;
	int p2;
	int *p,*q;
	p = (int *) xx->state;
	q = (int *) xx->state + 55;
	while (p < q) *p++ = 0;
	xx->si = xx->sj = 0;
	p2 = 1;
 
	xx->state[0] = p1 % MOD;
	for (i = 1, j = 21; i < 55; i++, j += 21) {
		if (j >= 55) j -= 55;
		xx->state[j] = p2;
		if ((p2 = p1 - p2) < 0) p2 += MOD;
		p1 = xx->state[j];
	}
	xx->si = 0;
	xx->sj = 24;
	for (i = 0; i < 165; i++) subrand(xx);
	} /* subrand_seed */

/* generate a random number from 0 to 10^9 */
 
int subrand(xxfmt *xx)
	{
	int x;
	if (xx->si == xx->sj) subrand_seed(xx, 0);
 
	if (!xx->si--) xx->si = 54;
	if (!xx->sj--) xx->sj = 54;
	if ((x = xx->state[xx->si] - xx->state[xx->sj]) < 0) x += MOD;
	if (x == xx->first_seed)
	   {
	   fprintf(stderr,"subrand: wrap around "
	      "on count %.0f\n", xx->count);
	   exit(1);
	   } /* if wrap around */
 
	return xx->state[xx->si] = x;
	} /* subrand */
 
/* Initialize the subrand random number generator */
/* see http://rosettacode.org/wiki/Subtractive_generator */
/* for more information about subrand */

void start_rng(xxfmt *xx)
   {
   unsigned int sd;                /* seed */
   xx->ee = (eefmt *) eeglinit();
   sd = (eegl(xx->ee) | 1) & 0x7fffffff;
   xx->first_seed = sd;    /* for wrap around test */
   subrand_seed(xx, sd);
   } /* start_rng */

/* Generate one uniform sample from zero to one */

double gen_dbl(xxfmt *xx)
   {
   unsigned int x;
   double num;
   x = subrand(xx);
   num = (double) x / xx->subrand_mod;
   return(num);
   } /* gen_dbl */

int main(void)
   {
   xxfmt *xx;

   /*************************************************************/
   /* Allocate memory for the global structure.                 */
   /* This is a re-entrant program.                             */
   /*************************************************************/

   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */

   /*************************************************************/
   /* initialize global data                                    */
   /*************************************************************/
   xx->dieharder_rngname[0] = '\0';
   xx->rngname = (char *) NULL;
   xx->generator = -1;
   xx->eofsw     = 0;
   xx->sumx = 0.0;
   xx->deltax = 1.0 / (double) SMPLS;
   xx->maxdiff = -999999999.0;
   xx->subrand_mod = (double) MOD;
   xx->root = (treefmt *) treeinit();
   xx->dblsmpls = (double) SMPLS;
   start_rng(xx);  /* initialize the RNG */
   xx->count = 0.0;
   xx->duplicates = 0.0;
   while (xx->count < xx->dblsmpls)
      {
      double num;
      num = gen_dbl(xx);
      isrt(xx->root, num, xx);
      xx->count += 1.0;
      } /* for each sample */
   if (xx->root->rght != NULL) traverse(xx->root->rght, xx);
   printf("Kolmogorov-Smirnov Test\n");
   printf("Knuth subrand Generator\n");
   printf("Maximum difference %f\n", xx->maxdiff);
   printf("Times sqrt(N)      %f\n",
      xx->maxdiff * sqrt(xx->dblsmpls));
   printf("Number of samples  %d\n", SMPLS);
   printf("Duplicate keys     %.0f\n", xx->duplicates);
   printf("\n");
   printf("Since number of samples is over 50,\n");
   printf("Probability    D-Max\n");
   printf("  0.001        1.94947\n");
   printf("  0.01         1.62762\n");
   printf("  0.02         1.51743\n");
   printf("  0.05         1.35810\n");
   if (xx->root->rght != NULL) rmtree(xx->root->rght);
   freeall(xx);        /* free all allocated memory */
   return(0);          /* end of job */
   } /* main */
