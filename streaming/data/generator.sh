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
tc bign0 gen_random NUM1=50 NUM2=50 NUMB=10
