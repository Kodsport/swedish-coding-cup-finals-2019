#!/usr/bin/env bash

PPATH=$(realpath ..)

. ../../testdata_tools/gen.sh

use_solution squatting_mw.cpp opt

compile gen_random.py
compile gen_concentrated_diffs.py

# Totala antalet tecken i input
MAXS=1000000

samplegroup
limits sMax=$MAXS
sample 1

group group1 5
limits sMax=$MAXS
tc bign0 gen_random S=$MAXS minLength=1 maxLength=10
tc bign1 gen_random S=$MAXS minLength=1 maxLength=4
tc bign2 gen_random S=$MAXS minLength=4 maxLength=4
tc bign3 gen_concentrated_diffs S=$MAXS length=5
tc bign4 gen_concentrated_diffs S=$MAXS length=8
tc bign5 gen_concentrated_diffs S=$MAXS length=250
