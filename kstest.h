#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_sf_erf.h>
#include <gsl/gsl_rng.h>
#include "eegl.h"

#define SMPLS (1000000)

/* modulus used in subrand */

#define MOD (1000000000)

/* 128^3 */

#define CUBESIZE (2097152)

/* modulus for a cube of dots */
/* there is a 50% chance of a black dot in the cube */

#define CUBEMOD (1048576)

#define EOFKS (-999999999.0)

#define EOFDIE (-999999999.0)

typedef struct treestruct {
   struct treestruct *left;
   struct treestruct *rght;
   double num;
   } treefmt;

typedef struct xxstruct {
   char *rngname;
   char dieharder_rngname[128];
   char rngtbl[1000][64];
   char cube[CUBESIZE];   /* 128^3 */
   int generator;
   int eofsw;
   int state[55];       /* subrand state */
   int si;              /* subrand state index */
   int sj;              /* subrand state index */
   int first_seed;      /* subrand first seed for wrap around */
   unsigned int fibonum1;
   unsigned int fibonum2;
   unsigned int fibonum3;
   unsigned int lfsr0;
   unsigned int lfsr;
   unsigned int major;
   unsigned int minor;
   unsigned int lowbit;
   unsigned int out;
   unsigned int seed;
   unsigned int maxint;
   double dblsmpls;
   double count;
   double duplicates;
   double modulus;
   double subrand_mod;
   double sumx;
   double deltax;
   double maxdiff;
   double maxint_tbl[2048];
   treefmt *root;
   eefmt *ee;
   gsl_rng_type *gsltype;
   gsl_rng *rng;
   } xxfmt;

treefmt *treeinit(void);

void isrt(treefmt *node, double num, xxfmt *xx);

void rmtree(treefmt *node);

void traverse(treefmt *node, xxfmt *xx);

double getks(xxfmt *xx);

double getdie(xxfmt *xx);

void freeall(xxfmt *xx);

void subrand_seed(xxfmt *xx, int p1);

int subrand(xxfmt *xx);
