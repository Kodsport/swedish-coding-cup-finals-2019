#!/usr/bin/env bash

USE_SYMLINKS=1

ulimit -s unlimited

PPATH=$(realpath ..)

. ../../testdata_tools/gen.sh

use_solution sl.cpp opt

compile gen_random.py
compile gen.cpp opt
compile dummy.py

samplegroup
limits l=100
sample 1
sample 2
sample 3
sample 4

# Simulate everything
# $L \le 10$
group group1 7
limits l=10
tc 1-rand1 gen_random n=1 l=10 k=2
tc 1-rand2 gen_random n=3 l=10 k=2
tc 1-rand3 gen_random n=3 l=10 k=2
tc 1-rand4 gen_random n=3 l=10 k=2
tc 1-smart1 gen n=1 l=10 eachlo=3 eachhi=4 tryk=50000 tree=shallow calls=0 error=0
tc 1-smart2 gen n=2 l=10 eachlo=2 eachhi=4 tryk=50000 tree=shallow calls=0 error=1
tc 1-smart3 gen n=2 l=10 eachlo=2 eachhi=4 tryk=50000 tree=random calls=0 error=0
tc 1-smart4 gen n=2 l=10 eachlo=1 eachhi=2 tryk=50000 tree=random calls=1 error=1
tc 1-smart5 gen n=3 l=10 eachlo=1 eachhi=2 tryk=50000 tree=random calls=1 error=1
tc 1-smart6 gen n=3 l=10 eachlo=1 eachhi=2 tryk=50000 tree=random calls=2 error=0

# DP over position and whether the only mutex is held
# $L \le 1000$, $K = 1$. It doesn't matter which error you output.
group group2 10
limits l=1000 k=1
tc 2-rand1 gen_random n=2 l=1000 k=1
tc 2-rand2 gen_random n=100 l=1000 k=1
tc 2-rand3 gen_random n=3 l=10 k=1
tc 2-deep1 gen n=100 l=1000 k=1 eachlo=6 eachhi=8 tryk=500000 tree=deeper calls=200 error=0 seed=123
tc 2-deep2 gen n=100 l=1000 k=1 eachlo=6 eachhi=8 tryk=500000 tree=deeper calls=200 error=1 seed=123
tc 2-deep3 gen n=100 l=1000 k=1 eachlo=6 eachhi=8 tryk=500000 tree=deeper calls=200 error=2 seed=123
tc 2-smart1 gen n=100 l=1000 k=1 eachlo=7 eachhi=10 tryk=500000 tree=shallow calls=100 error=0 seed=123
tc 2-smart2 gen n=100 l=1000 k=1 eachlo=7 eachhi=10 tryk=500000 tree=shallow calls=10 error=1
tc 2-smart3 gen n=100 l=1000 k=1 eachlo=7 eachhi=10 tryk=500000 tree=random calls=50 error=0
tc 2-smart4 gen n=100 l=1000 k=1 eachlo=5 eachhi=8 tryk=500000 tree=random calls=50 error=1
tc 2-smart5 gen n=300 l=1000 k=1 eachlo=4 eachhi=6 tryk=500000 tree=random calls=50 error=1
tc 2-smart6 gen n=300 l=1000 k=1 eachlo=4 eachhi=6 tryk=500000 tree=random calls=50 error=0

# DP per mutex
# $L \le 1000$. It doesn't matter which error you output.
group group3 10
limits l=1000
include_group group2
tc 3-rand1 gen_random n=1 l=1000 k=50
tc 3-rand2 gen_random n=3 l=1000 k=50
tc 3-rand3 gen_random n=3 l=10 k=50
tc 3-deep1 gen n=100 l=1000 eachlo=2 eachhi=3 tryk=500000 tree=deeper calls=200 error=0 seed=123
tc 3-deep2 gen n=100 l=1000 eachlo=2 eachhi=3 tryk=500000 tree=deeper calls=200 error=1 seed=123
tc 3-deep3 gen n=100 l=1000 eachlo=2 eachhi=3 tryk=500000 tree=deeper calls=200 error=2 seed=123
tc 3-smart1 gen n=100 l=1000 eachlo=4 eachhi=7 tryk=500000 tree=shallow calls=10 error=0
tc 3-smart2 gen n=100 l=1000 eachlo=2 eachhi=7 tryk=500000 tree=shallow calls=10 error=1
tc 3-smart3 gen n=100 l=1000 eachlo=2 eachhi=7 tryk=500000 tree=random calls=50 error=0
tc 3-smart4 gen n=100 l=1000 eachlo=1 eachhi=3 tryk=500000 tree=random calls=50 error=1
tc 3-smart5 gen n=300 l=1000 eachlo=1 eachhi=3 tryk=500000 tree=random calls=50 error=1
tc 3-smart6 gen n=300 l=1000 eachlo=1 eachhi=3 tryk=500000 tree=random calls=50 error=0

# + reconstruction
# $L \le 1000$ \\ \hline
group group4 15
limits l=1000
include_group group1
include_group group3

# Reduce memory usage for the upcoming part...
wait
USE_PARALLEL=0

# Copy group 3 to group 4, and signal to the output validator that any error is ok
# by writing an initial space (Kattis does not yet support output validator flags
# per test group).
for A in secret/group3/*.in; do
	B=$(basename $A .in)
	tc 4-$B dummy
	cp secret/group3/$B.in secret/group4/4-$B.in
	cp secret/group3/$B.ans secret/group4/4-$B.ans
	echo ' ' >secret/group3/$B.ans
	cat secret/group4/4-$B.ans >>secret/group3/$B.ans
done

# BFS
# $L \le 50\,000$. No \texttt{release} or \texttt{access} commands will be performed.
group group5 10
limits l=50000 onlyacq=1
tc 5-rand1 gen_random n=1 l=50000 k=100000 onlyacq=1
tc 5-rand2 gen_random n=100 l=50000 k=100000 onlyacq=1
tc 5-deep1 gen n=10000 l=50000 eachlo=2 eachhi=5 tryk=500000 tree=deeper remEdges=10 calls=1000 error=0 onlyacq=1 seed=123
tc 5-deep2 gen n=10000 l=50000 eachlo=2 eachhi=5 tryk=500000 tree=deeper remEdges=10 calls=1000 error=2 onlyacq=1 seed=123
tc 5-smart1 gen n=10000 l=50000 eachlo=2 eachhi=5 tryk=500000 tree=shallow remEdges=200 calls=200 error=0 onlyacq=1 seed=123
tc 5-smart2 gen n=10000 l=50000 eachlo=2 eachhi=5 tryk=500000 tree=shallow remEdges=200 calls=200 error=1 onlyacq=1 seed=123
tc 5-smart3 gen n=10000 l=50000 eachlo=1 eachhi=5 tryk=500000 tree=random calls=30 remEdges=15 error=0 onlyacq=1
tc 5-smart4 gen n=15000 l=50000 eachlo=1 eachhi=5 tryk=500000 tree=random calls=30 remEdges=15 error=1 onlyacq=1
tc 5-smart5 gen n=15000 l=50000 eachlo=1 eachhi=2 tryk=500000 tree=random calls=1000 error=1 onlyacq=1
tc 5-smart6 gen n=15000 l=50000 eachlo=1 eachhi=2 tryk=500000 tree=random calls=1000 error=0 onlyacq=1

# Bitsets
# $L \le 50\,000$
group group6 23
limits l=50000
include_group group4
include_group group5
tc 6-rand1 gen_random n=1 l=50000 k=100000
tc 6-rand2 gen_random n=100 l=50000 k=100000
tc 6-deep1 gen n=15000 l=50000 eachlo=2 eachhi=5 tryk=500000 tree=deeper calls=1000 error=0
tc 6-deep2 gen n=15000 l=50000 eachlo=2 eachhi=5 tryk=500000 tree=deeper calls=1000 error=1
tc 6-deep3 gen n=15000 l=50000 eachlo=2 eachhi=5 tryk=500000 tree=deeper calls=1000 error=2
tc 6-smart1 gen n=10000 l=50000 eachlo=4 eachhi=7 tryk=500000 tree=shallow calls=1000 error=0
tc 6-smart2 gen n=10000 l=50000 eachlo=2 eachhi=7 tryk=500000 tree=shallow calls=1000 error=1
tc 6-smart3 gen n=10000 l=50000 eachlo=2 eachhi=7 tryk=500000 tree=random calls=1000 error=0
tc 6-smart4 gen n=15000 l=50000 eachlo=1 eachhi=2 tryk=500000 tree=random calls=1000 error=1
tc 6-smart5 gen n=15000 l=50000 eachlo=1 eachhi=2 tryk=500000 tree=random calls=3000 error=1 seed=13
tc 6-smart6 gen n=15000 l=50000 eachlo=1 eachhi=2 tryk=500000 tree=random calls=3000 error=0 seed=24
