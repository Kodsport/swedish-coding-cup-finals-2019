#!/usr/bin/env bash

PPATH=$(realpath ..)

. ../../testdata_tools/gen.sh

use_solution sl.cpp opt

compile gen_random.py

samplegroup
limits l=100
sample 1
sample 2
sample 3
sample 4

# Simulate everything
# $L \le 10$
group group1 5
limits l=10
tc 1-rand1 gen_random n=1 l=10 k=2
tc 1-rand2 gen_random n=3 l=10 k=2
tc 1-rand3 gen_random n=3 l=10 k=2
tc 1-rand4 gen_random n=3 l=10 k=2

# DP over position and whether the only mutex is held
# $L \le 1000$, $K = 1$. It doesn't matter which error you output.
group group2 5
limits l=1000 k=1
tc 2-rand1 gen_random n=2 l=1000 k=1
tc 2-rand2 gen_random n=100 l=1000 k=1
tc 2-rand3 gen_random n=3 l=10 k=1

# DP per mutex
# $L \le 1000$. It doesn't matter which error you output.
group group3 5
limits l=1000
include_group group2
tc 3-rand1 gen_random n=1 l=1000 k=50
tc 3-rand2 gen_random n=3 l=1000 k=50
tc 3-rand3 gen_random n=3 l=10 k=50

# + reconstruction
# $L \le 1000$ \\ \hline
group group4 5
limits l=1000
include_group group1
include_group group3
tc 4-rand1 gen_random n=1 l=1000 k=100000
tc 4-rand2 gen_random n=100 l=1000 k=100000

# BFS
# $L \le 50\,000$. No \texttt{release} or \texttt{access} commands will be performed.
group group5 5
limits l=50000 onlyacq=1
tc 5-rand1 gen_random n=1 l=50000 k=100000 onlyacq=1
tc 5-rand2 gen_random n=100 l=50000 k=100000 onlyacq=1

# Bitsets
# $L \le 50\,000$
group group6 5
limits l=50000
include_group group4
include_group group5
tc 6-rand1 gen_random n=1 l=50000 k=100000
tc 6-rand2 gen_random n=100 l=50000 k=100000
