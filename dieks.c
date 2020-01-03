/* dieks.c - KS Test, dieharder generators  Version 0.1.0 */
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

void bld_rngtbl(xxfmt *xx);
void bld_maxint(xxfmt *xx);
double getdie(xxfmt *xx);

void putstx(char *pgm)
   {
   fprintf(stderr,"Usage: %s Dieharder_RNG_number\n", pgm);
   fprintf(stderr,"Example: %s 208\n", pgm);
   fprintf(stderr,"Where 208 is the kiss generator\n");
   fprintf(stderr,"Example: %s 053\n", pgm);
   fprintf(stderr,"Where 053 is the taus2 generator\n");
   fprintf(stderr,"To see a list of "
      "dieharder generators:\n");
   fprintf(stderr,"dieharder -g -l\n");
   exit(1);
   } /* putstx */

void diepfx(xxfmt *xx)
   {
   int len;
   int rslt;
   int namesw;
   char buf[256];
   namesw = 0;
   xx->dieharder_rngname[0] = '\0';
   while (1)
      {
      len = scanf("%s", buf);
      if (len < 1)
         {
         if (feof(stdin))
	    {
	    fprintf(stderr,"diepfx: scanf end of file\n");
	    exit(1);
	    } /* if end of file */
         if (ferror(stdin))
            {
            perror("diepfx: read error\n");
            exit(1);
            } /* read error */
         fprintf(stderr,"diepfx: blank line, len %d\n", len);
         exit(1);
         } /* if eof or read error */
      if (len > 1)
         {
         fprintf(stderr,"diepfx: read error\n");
         fprintf(stderr,"scanf read more than "
            "one token %d\n", len);
         exit(1);
         } /* invalid input */
      rslt = strcmp(buf,"numbit:");
      if (!rslt) break;
      if (namesw)   /* buf = generator name? */
         {
	 strcpy(xx->dieharder_rngname,buf);
	 fprintf(stderr,"Dieharder RNG Name %s\n",
	    xx->dieharder_rngname);
	 namesw = 0;    /* turn off name switch */
	 } /* if generator name switch turned on */
      rslt = strcmp(buf,"generator");
      if (!rslt)
         {
	 namesw = 1;    /* turn on name switch */
	 } /* if generator statement */
      } /* read loop until numbit: */
   len = scanf("%s", buf);
   if (len < 1)
      {
      if (feof(stdin))
	 {
	 fprintf(stderr,"diepfx: scanf end of file\n");
	 exit(1);
	 } /* if end of file */
      if (ferror(stdin))
         {
         perror("getdie: read error\n");
         exit(1);
         } /* read error */
      fprintf(stderr,"getdie: blank line\n");
      exit(1);
      } /* if eof or read error */
   if (len > 1)
      {
      fprintf(stderr,"getdie: read error\n");
      fprintf(stderr,"scanf read more than "
         "one token %d\n", len);
      exit(1);
      } /* invalid input */
   rslt = strcmp(buf,"32");
   if (rslt)
      {
      fprintf(stderr,"diepfx: numbit not = 32\n");
      fprintf(stderr,"buf = %s\n", buf);
      exit(1);
      } /* numbit: not equal to 32 */
   } /* diepfx */

/* generate a uniform random number from zero to one */
double gen_dbl(xxfmt *xx)
   {
   double num;
   num = getdie(xx);
   if (xx->eofsw)
      {
      fprintf(stderr,"gen_dbl: end of "
         "file %.0f\n", xx->count);
      num = EOFDIE;
      } /* end of file condition */
   return(num);
   } /* gen_dbl */

int main(int argc, char **argv)
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
   xx->dblsmpls = (double) SMPLS;
   xx->deltax = 1.0 / xx->dblsmpls;
   xx->maxdiff = -999999999.0;
   xx->root = (treefmt *) treeinit();
   /*************************************************************/
   /* obtain dieharder generator number parameter               */
   /*************************************************************/

   if (argc != 2) putstx(*argv);
   xx->generator = atoi(*(argv+1));
   if (xx->generator < 0 || xx->generator > 405)
      {
      fprintf(stderr,"main: invalid random "
         "number generator %s\n", *(argv+1));
      putstx(*argv);
      } /* invalid generator */

   /*************************************************************/
   /* initialize queues and numeric fields                      */
   /*************************************************************/
   xx->eofsw = 0;
   bld_maxint(xx);  /* build maxint table for dieharder RNGs */
   bld_rngtbl(xx);  /* build name table for dieharder RNGs */
   if (xx->maxint_tbl[xx->generator] == 0.0)
      {
      fprintf(stderr,"main: invalid random "
         "number generator %s\n", *(argv+1));
      putstx(*argv);
      } /* invalid generator */
   xx->modulus = xx->maxint_tbl[xx->generator];
   xx->maxint  = (unsigned int) xx->modulus;
   /****************************************************/
   diepfx(xx);    /* bypass dieharder prefix */
   xx->modulus = xx->maxint_tbl[xx->generator];
   xx->maxint = (unsigned int) xx->modulus;
   xx->count = 0.0;
   xx->duplicates = 0.0;
   while (!xx->eofsw && xx->count < xx->dblsmpls)
      {
      double num;
      num = gen_dbl(xx);
      if (num < 0.0) break;
      if (num > 1.0) break;
      if (xx->eofsw) break;
      isrt(xx->root, num, xx);
      xx->count += 1.0;
      } /* for each sample */
   if (xx->root->rght != NULL) traverse(xx->root->rght, xx);
   printf("Kolmogorov-Smirnov Test\n");
   printf("Dieharder Generator: %s\n",
      xx->dieharder_rngname);
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
