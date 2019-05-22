#!/usr/bin/env bash

PPATH=$(realpath ..)

. ../../testdata_tools/gen.sh

use_solution naive.cpp opt

compile gen_random.py

# Antalet dagar
MAXN=10000000

samplegroup
limits sMax=$MAXS
sample 1

group group1 5
limits sMax=$MAXS
tc bign0 gen_random 1=50 2=50 b=10 k=30
