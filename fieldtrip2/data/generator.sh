#!/usr/bin/env bash

PPATH=$(realpath ..)

. ../../testdata_tools/gen.sh

use_solution fieldtrip2_js.cpp

MAXK=1000000
MAXA=1000000000
MAXM=100000
MAXASUM=100000000000000

samplegroup
limits maxA=$MAXA maxM=$MAXM maxAsum=$MAXASUM maxK=$MAXK
sample 1
sample 2
