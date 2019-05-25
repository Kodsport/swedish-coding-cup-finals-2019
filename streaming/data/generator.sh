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
limits n=1e5 k=10
include_group group1
tc 2-rand1 gen_random 1=115000 2=80000 b=2500 k=10 mult=0.5
tc 2-rand2 gen_random 1=80000 2=115000 b=1000 k=10 mult=0.5
tc 2-rand3 gen_random 1=90000 2=110000 b=0 k=10 mult=0.5
tc 2-rand4 gen_random 1=60000 2=40000 b=100000 k=9 mult=0.5
tc 2-rand5 gen_random 1=90000 2=100000 b=3000 k=10 mult=0.5
tc 2-rand6 gen_random 1=90000 2=100000 b=3000 k=6 mult=0.5
tc 2-rand7 gen_random 1=90000 2=100000 b=3000 k=3 mult=0.5
tc 2-n2-1 gen_n2 k=3 n=100000 seed=128
tc 2-n2-2 gen_n2 k=10 n=100000 seed=127

group group3 15
limits n=1e5 k=200
include_group group2
tc 3-rand1 gen_random 1=110000 2=80000 b=2500 k=200 mult=0.5
tc 3-rand2 gen_random 1=80000 2=110000 b=1000 k=200 mult=0.5
tc 3-rand3 gen_random 1=90000 2=110000 b=0 k=200 mult=0.5
tc 3-rand4 gen_random 1=60000 2=40000 b=100000 k=199 mult=0.5
tc 3-rand5 gen_random 1=90000 2=100000 b=3000 k=100 mult=0.5
tc 3-rand6 gen_random 1=90000 2=100000 b=3000 k=60 mult=0.5
tc 3-n2 gen_n2 k=100 n=100000
tc 3-mw gen_mw k=200 n=100000
tc 3-aslowmw-1 gen_random 1=2 2=9900 b=190000 k=200 seed=3 mult=0.5
tc 3-slowmw-2 gen_random 1=60 2=90 b=199850 k=200 seed=6 mult=0.5
tc 3-slowmw-3 gen_random 1=700 2=0 b=199000 k=200 seed=1 mult=0.5

group group4 34
limits n=4e5 k=4e5
include_group group3
tc 4-rand1 gen_random 1=80000 2=110000 b=5000 k=180000 mult=2
tc 4-rand2 gen_random 1=80000 2=110000 b=5000 k=50000 mult=2
tc 4-rand3 gen_random 1=80000 2=110000 b=5000 k=10000 mult=2
tc 4-rand4 gen_random 1=80000 2=110000 b=5000 k=3000 mult=2
tc 4-n2-1 gen_n2 k=60000 n=400000
tc 4-n2-2 gen_n2 k=20000 n=400000
tc 4-n2-3 gen_n2 k=6000 n=400000
tc 4-n2-4 gen_n2 k=2000 n=400000
tc 4-mw gen_mw k=800 n=400000
tc 4-aslowmw-1 gen_random 1=700 2=0 b=199000 k=1000 seed=1 mult=2
tc 4-slowmw-2 gen_random 1=30 2=700 b=199000 k=1000 seed=6 mult=2
tc 4-slowmw-3 gen_random 1=1 2=700 b=199000 k=1000 seed=5 mult=2
tc 4-slowmw-4 gen_random 1=1 2=9900 b=190000 k=1000 seed=3 mult=2
tc 4-3-rand1 gen_random 1=110000 2=80000 b=2500 k=200 mult=2
tc 4-3-rand2 gen_random 1=80000 2=110000 b=1000 k=200 mult=2
tc 4-3-rand3 gen_random 1=90000 2=110000 b=0 k=200 mult=2
tc 4-3-rand4 gen_random 1=60000 2=40000 b=100000 k=199 mult=2
tc 4-3-rand5 gen_random 1=90000 2=100000 b=3000 k=100 mult=2
tc 4-3-rand6 gen_random 1=90000 2=100000 b=3000 k=60 mult=2
tc 4-3-n2 gen_n2 k=100 n=400000
tc 4-3-mw gen_mw k=200 n=400000
