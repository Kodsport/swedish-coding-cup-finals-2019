#!/usr/bin/env bash

PPATH=$(realpath ..)

. ../../testdata_tools/gen.sh

use_solution mirrormirror_js.cpp opt

compile gen_random.py
compile gen_convex_hull.py
compile gen_line.py
compile gen_answer_is_2.cpp opt
compile gen_answer_is_barely_3.cpp opt

# Antal punkter
MAXN=1500

# Högsta absolutbeloppet av en koordinat (|x_i|, |y_i| <= MAXX)
MAXX=30000

samplegroup
limits nMax=100 xMax=$MAXX
sample 1

group group1 10
limits nMax=20 xMax=$MAXX
tc 1-n1 gen_random n=1   maxx=$MAXX
tc 1-n2 gen_random n=2   maxx=5
tc 1-n3 gen_random n=3   maxx=10  
tc 1-smalln2 gen_random n=10  maxx=10
tc 1-smalln3 gen_random n=20  maxx=10
tc 1-smalln4 gen_random n=20  maxx=$((MAXX/2))
tc 1-smalln5 gen_random n=20  maxx=$MAXX
tc 1-smalln6 gen_line   n=10  maxx=$MAXX        lines=1
tc 1-smalln7 gen_line   n=20  maxx=$MAXX        lines=2
tc 1-smalln8 gen_line   n=20  maxx=$MAXX        lines=3
tc 1-smalln9 gen_answer_is_barely_3 20 40

group group2 7
limits nMax=800 xMax=$MAXX nocolinear=1
# TODO
tc 2-nocolinear1 gen_random n=800  maxx=$MAXX

group group3 8
limits nMax=800 xMax=$MAXX
include_group group2
include_group group1
tc 3-mediumn0 gen_random n=800  maxx=$MAXX
tc 3-mediumn1 gen_random n=800  maxx=$MAXX
tc 3-mediumn2 gen_random n=800  maxx=$MAXX
tc 3-mediumn3 gen_random n=800  maxx=$MAXX
tc 3-mediumn4 gen_random n=800  maxx=$MAXX
tc 3-mediumn5 gen_random n=800  maxx=$MAXX
tc 3-mediumn6 gen_line n=800  maxx=$MAXX   lines=1
tc 3-mediumn7 gen_line n=800  maxx=$MAXX   lines=3
tc 3-mediumn8 gen_line n=800  maxx=$MAXX   lines=10
tc 3-mediumn9 gen_answer_is_barely_3 800 $MAXX

group group4 10
limits nMax=$MAXN xMax=$MAXX
# Copied from group 6 below

group group5 15
limits nMax=$MAXN xMax=$MAXX convexhull=1
tc 5-bign_convex0 gen_convex_hull n=$MAXN  maxx=$MAXX fact=1   wobble=0
tc 5-bign_convex1 gen_convex_hull n=$MAXN  maxx=$MAXX fact=400 wobble=2
tc 5-bign_convex2 gen_convex_hull n=$MAXN  maxx=$MAXX fact=20  wobble=5
tc 5-bign_convex3 gen_convex_hull n=$MAXN  maxx=$MAXX fact=400 wobble=0
tc 5-bign_convex4 gen_convex_hull n=$MAXN  maxx=$MAXX fact=400 wobble=0
tc 5-bign_convex5 gen_convex_hull n=$MAXN  maxx=$MAXX fact=400 wobble=0 rand=0
tc 5-bign_convex6 gen_convex_hull n=$MAXN  maxx=$MAXX fact=2   wobble=2 odd=1 seed=128
tc 1-n1
tc 1-n2
tc 1-n3

group group6 25
limits nMax=$MAXN xMax=$MAXX
include_group group5
include_group group3
tc 6-bign1 gen_random n=$MAXN  maxx=$MAXX
tc 6-bign2 gen_random n=$MAXN  maxx=$MAXX
tc 6-bign3 gen_random n=$MAXN  maxx=$MAXX
tc 6-bign4 gen_random n=$MAXN  maxx=$MAXX
tc 6-bign5 gen_random n=$MAXN  maxx=$MAXX
tc 6-bign6 gen_random n=$MAXN  maxx=$MAXX
tc 6-bign7 gen_line n=$MAXN  maxx=$MAXX    lines=1
tc 6-bign8 gen_line n=$MAXN  maxx=$MAXX    lines=3
tc 6-bign9 gen_line n=$MAXN  maxx=$MAXX    lines=10
tc 6-bign10 gen_random n=$MAXN  maxx=32 # The smallest square that fits 4000 points
tc 6-a-barely3-1 gen_answer_is_barely_3 $MAXN $MAXX
tc 6-a-barely3-2 gen_answer_is_barely_3 $MAXN $MAXX
tc 6-a-is2-1 gen_answer_is_2 $MAXN $MAXX
tc 6-c-barely3-3 gen_answer_is_barely_3 $MAXN $MAXX
tc 6-c-barely3-4 gen_answer_is_barely_3 $MAXN $MAXX
tc 6-c-is2-2 gen_answer_is_2 $MAXN $MAXX

wait
for A in secret/group6/*.in; do
	# We don't have output validator flags per test group in Kattis, so hack it by adding some whitespace
	B=$(basename $A .in)
	cp secret/group6/$B.in secret/group4/offbyone-$B.in
	echo ' ' > secret/group4/offbyone-$B.ans
	cat secret/group6/$B.ans >> secret/group4/offbyone-$B.ans
done
