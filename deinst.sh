#!/bin/bash
make -f eegllib.mak clean
make -f etauslib.mak clean
make -f libks.mak clean
make -f eeglks.mak clean
make -f etausks.mak clean
make -f srandks.mak clean
make -f fiboks.mak clean
make -f lfsrks.mak clean
make -f sineks.mak clean
make -f randuks.mak clean
make -f gslks.mak clean
make -f dieks.mak clean
rm -f allgsl.out
