# Kolmogov-Smirnov Test

The Kolmogov-Smirnov test is one of two frequency tests
of uniformity described in the following document.

https://www.eg.bucknell.edu/~xmeng/Course/CS6337/Note/master/node43.html

The Kolmogov-Smirnov test reveals gaps in sample data in a
test, or bunching of data, which is the opposite of gaps.

One million random numbers between zero and one are sorted
in ascending sequence in a binary tree in memory.  These
sorted numbers are then compared to an ascending sequence of
numbers in a straight line from zero to one.  The maximum
difference between the random numbers and the straight line
in the vertical axis becomes the statistic.  The maximum
difference is multiplied by the square root of N, sqrt(1000000),
and compared to 1.95.  The test fails if the adjusted difference
is greater than 1.95.

The tests in this repository are applied against a variety
of random number generators, some weak and some strong.
The purpose of this repository is to show how the Kolmogorov-
Smirnov test is performed, and what types of generators pass
or fail the test.

Random number generators used in this test.

eegl64

The eegl64 random number generator is explained in the repository
"eegl64".  That is a random number generator based on a 64 bit
LFSR with a Bays Durham shuffle.  The period length of the eegl64
generator approximates 1.2 * 16^61036 generations.  That is a long
period length, that never terminates, or wraps around.  The eegl64
generator passes the Kolmogorov-Smirnov test.

----------------

Knuth's subrand generator

Knuth's subrand generator is a subtractive random number generator
which he describes in his book.

Donald E. Knuth
The Art Of Computer Programming
Volume 2, Section 3.2.2

The algorithm is as follows.

state[n] = state[n-1] - state[n-2]
if (state[n] < 0) state[n] += MOD
where MOD is 10^9

The C code for subrand is available in Rosetta Code.

http://rosettacode.org/wiki/Subtractive_generator#C

subrand fails the Kolmogorov-Smirnov test.

----------------


Fibonacci

The fibonacci random number generator illustrates how a weak
random number generator passes the Kolmogorov-Smirnov test.

The fibonacci generator is computed in the gen_dbl() function
in the fiboks.c program.

fibonum1 = fibonum2
fibonum2 = fibonum3
fibonum3 = fibonum1 + fibonum2
fraction = fibonum3 / maxint

fraction is a pseudo random number with a uniform distribution
ranging from zero to one.

----------------

LFSR

The LFSR random number generator illustrates how a weak
random number generator passes the Kolmogorov-Smirnov test.

The LFSR generator is computed in the gen_dbl() function in the
lfsrks.c program.  See the macro MYLFSR at the beginning of
the program for the algorithm used in the LFSR generator.  The
LFSR generator used is a 64 bit linear feedback shift register
with a period length of 2^64.

MYLFSR;
fraction = lfsr / maxint

fraction is a pseudo random number with a uniform distribution
ranging from zero to one.

----------------

RANDU

The RANDU random number generator illustrates how a weak
random number generator passes the Kolmogorov-Smirnov test.

The RANDU generator is computed in the gen_dbl() function
in the randuks.c program.  RANDU is a 32 bit generator with
a period length of 2^30.

seed *= 65539;
fraction = seed / maxint

fraction is a pseudo random number with a uniform distribution
ranging from zero to one.

----------------

Sine Wave Generator

The sine random number generator illustrates how a weak
random number generator fails the Kolmogorov-Smirnov test.

The sine generator is computed in the gen_dbl() function
in the sineks.c program.  The sine generator has a long
enough period length to complete the test.

/* generate a uniform number between zero and PI */
radian = eeglunif(ee) * M_PI;
sinx = sin(radian);

sinx is a pseudo random number with a sine distribution
ranging from zero to one.

----------------

GNU Scientific Library Generators

The GSL generators illustrate how a variety of strong random
number generators perform well in the Kolmogorov-Smirnov test.

The GSL generators are computed in the gen_dbl() function
in the gslks.c program.  The GSL generators have a long
enough period length to complete the test.

fraction = gsl_rng_uniform(rng);

fraction is a strong random number with a uniform distribution
ranging from zero to one.

The following GSL generators fail the Kolmogorov-Smirnov test.

knuthran

knuthran2002

ran3

ranlux

ranlux389

ranlxs0

ranlxs1

ranlxs2

ranmar

uni

zuf

The random*-* family of generators perform poorly in the KS test.

Other GSL generators, which fail the KS Test more often than
expected, are:

cmrg

mrg

mt19937

mt19937_1998

r250

ran2

uni32

----------------

Dieharder generators

The dieharder package contains 74 well known random number
generators.  Dieharder can generate 32 bit unsigned integers
from these generators with the following command.

dieharder -g nnn -t yyy -o

where nnn is the three digit number of the generator, and
yyy is the number of integers to generate.

For example,

dieharder -g 053 -t 1000 -o

This example generates one thousand 32 bit integers using
the taus2 generator.  053 is the number of the taus2 generator.

To see all the generator numbers, run the following command.

dieharder -g -l

The KS test command for dieharder generators in this
repository is called tstdie.sh.  The parameter for this command
is the dieharder generator number.  For example,

tstdie.sh 053

This runs the test using the taus2 generator from dieharder.

The following dieharder generators fail the Kolmogorov=Smirnov
test.

Gen Name

001 cmrg

005 fishman2x

007 knuthran

014 mt19937_1999

020 ran3

023 random128-bsd

024 random128-glibc2

026 random256-bsd

028 random256-libc5

040 random-libc5

043 ranlux

044 ranlux389

047 ranlxs0

048 ranlxs1

049 ranlxs2

050 ranmar

057 uni

061 zuf

205 AES_OFB

206 Threefish_OFB

207 XOR abort

404 R_knuth_taocp

405 R_knuth_taocp2

----------------

If you have a random number generator that you want to include
in this repository, you are welcome to submit your generator for
inclusion.

Read the INSTALL and TESTING documents for more information
about how to use this repository.
