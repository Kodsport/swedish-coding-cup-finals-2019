#!/usr/bin/env bash

PPATH=$(realpath ..)

. ../../testdata_tools/gen.sh

use_solution sl_opt.cpp opt

compile gen_random.py
compile gen_concentrated_diffs.py
compile gen_abba.py

samplegroup
limits s=10000
sample 1
sample 2

group group1 5
limits s=500
tc 1-small-rand0 gen_random s=500 minLength=500 maxLength=5000
tc 1-small-rand1 gen_random s=500 minLength=1 maxLength=10
tc 1-small-rand2 gen_random s=500 minLength=1 maxLength=4
tc 1-small-rand3 gen_random s=500 minLength=4 maxLength=4
tc 1-small-conc1 gen_concentrated_diffs s=500 length=5
tc 1-small-conc2 gen_concentrated_diffs s=500 length=8
tc 1-small-conc3 gen_concentrated_diffs s=500 length=250

group group2 16
limits s=1e5 len=100
tc 2-short-rand1 gen_random s=1e5 minLength=1 maxLength=100
tc 2-short-rand2 gen_random s=1e5 minLength=1 maxLength=10
tc 2-short-rand3 gen_random s=1e5 minLength=1 maxLength=4
tc 2-short-rand4 gen_random s=1e5 minLength=4 maxLength=4
tc 2-short-conc1 gen_concentrated_diffs s=1e5 length=5
tc 2-short-conc2 gen_concentrated_diffs s=1e5 length=8
tc 2-short-conc3 gen_concentrated_diffs s=1e5 length=100
tc 2-short-abba gen_abba logn=6

group group3 14
limits s=3e5
include_group group1
include_group group2
tc 3-large-rand1 gen_random s=3e5 minLength=1 maxLength=10
tc 3-large-rand2 gen_random s=3e5 minLength=1 maxLength=4
tc 3-large-rand3 gen_random s=3e5 minLength=4 maxLength=4
tc 3-large-conc1 gen_concentrated_diffs s=3e5 length=5
tc 3-large-conc2 gen_concentrated_diffs s=3e5 length=8
tc 3-large-conc3 gen_concentrated_diffs s=3e5 length=250
tc 3-large-abba gen_abba logn=15

group group4 15
limits s=3e6
include_group group3
tc 4-huge-rand1 gen_random s=3e6 minLength=1 maxLength=10
tc 4-huge-rand2 gen_random s=3e6 minLength=1 maxLength=4
tc 4-huge-rand3 gen_random s=3e6 minLength=4 maxLength=4
tc 4-huge-conc1 gen_concentrated_diffs s=3e6 length=5
tc 4-huge-conc2 gen_concentrated_diffs s=3e6 length=8
tc 4-huge-conc3 gen_concentrated_diffs s=3e6 length=250
tc 4-huge-abba gen_abba logn=19
