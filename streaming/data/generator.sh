#!/usr/bin/env bash

PPATH=$(realpath ..)

. ../../testdata_tools/gen.sh

use_solution sl.cpp opt

compile gen_random.py
compile gen_n2.py
compile gen_mw.py

N=200000

samplegroup
limits n=1000 k=1000
sample 1
sample 2

group group1 10
limits n=1000 k=10
for A in {1..5}; do
	tc 1${A}1-tiny gen_random 1=5 2=5 b=3 k=3
	tc 1${A}2-tiny gen_random 1=5 2=5 b=7 k=3
	tc 1${A}3-tiny gen_random 1=5 2=5 b=5 k=4
done
tc 1-k1 gen_random 1=300 2=300 b=300 k=1
tc 1-k2 gen_random 1=300 2=300 b=300 k=2
tc 1-rand1 gen_random 1=300 2=300 b=300 k=3
tc 1-rand2 gen_random 1=300 2=300 b=300 k=4
tc 1-rand3 gen_random 1=300 2=300 b=300 k=10
tc 1-ball gen_random 1=0 2=0 b=1000 k=10
tc 1-1all gen_random 1=1000 2=0 b=0 k=10
tc 1-2all gen_random 1=0 2=999 b=0 k=10

group group2 6
limits n=$N k=10
include_group group1
tc 2-rand1 gen_random 1=115000 2=80000 b=2500 k=10
tc 2-rand2 gen_random 1=80000 2=115000 b=1000 k=10
tc 2-rand3 gen_random 1=90000 2=110000 b=0 k=10
tc 2-rand4 gen_random 1=60000 2=40000 b=100000 k=9
tc 2-rand5 gen_random 1=90000 2=100000 b=3000 k=10
tc 2-rand6 gen_random 1=90000 2=100000 b=3000 k=6
tc 2-rand7 gen_random 1=90000 2=100000 b=3000 k=3
tc 2-n2-1 gen_n2 k=3 n=200000 seed=128
tc 2-n2-2 gen_n2 k=10 n=200000 seed=127

group group3 18
limits n=$N k=200
include_group group2
tc 3-rand1 gen_random 1=110000 2=80000 b=2500 k=200
tc 3-rand2 gen_random 1=80000 2=110000 b=1000 k=200
tc 3-rand3 gen_random 1=90000 2=110000 b=0 k=200
tc 3-rand4 gen_random 1=60000 2=40000 b=100000 k=199
tc 3-rand5 gen_random 1=90000 2=100000 b=3000 k=100
tc 3-rand6 gen_random 1=90000 2=100000 b=3000 k=60
tc 3-n2 gen_n2 k=100 n=200000 seed=128

group group4 31
limits n=$N k=$N
include_group group3
tc 4-rand1 gen_random 1=80000 2=110000 b=5000 k=180000
tc 4-rand2 gen_random 1=80000 2=110000 b=5000 k=50000
tc 4-rand3 gen_random 1=80000 2=110000 b=5000 k=10000
tc 4-rand4 gen_random 1=80000 2=110000 b=5000 k=3000
tc 4-n2 gen_n2 k=30000 n=200000 seed=128
tc 4-mw gen_mw k=400 n=200000
