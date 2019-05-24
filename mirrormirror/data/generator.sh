#!/usr/bin/env bash

PPATH=$(realpath ..)

. ../../testdata_tools/gen.sh

use_solution cubic.cpp opt

compile gen_random.py
compile gen_convex_hull.py
compile gen_line.py
compile gen_answer_is_2.cpp opt
compile gen_answer_is_barely_3.cpp opt

# Antal punkter
MAXN=4000

# Högsta absolutbeloppet av en koordinat (|xi| <= MAXX && |yi| <= MAXX)
MAXX=30000

samplegroup
limits nMax=$MAXN xMax=$MAXX
sample 1

group group1 5
limits nMax=20 xMax=$MAXX
tc smalln0 gen_random n=2   maxx=5
tc smalln1 gen_random n=3   maxx=10  
tc smalln2 gen_random n=10  maxx=10
tc smalln3 gen_random n=20  maxx=10
tc smalln4 gen_random n=20  maxx=$((MAXX/2))
tc smalln5 gen_random n=20  maxx=$MAXX
tc smalln6 gen_line   n=10  maxx=$MAXX        lines=1
tc smalln7 gen_line   n=20  maxx=$MAXX        lines=2
tc smalln8 gen_line   n=20  maxx=$MAXX        lines=3
tc smalln9 gen_random n=1   maxx=$MAXX
tc smalln10 gen_answer_is_barely_3 20 40

group group2 13
limits nMax=800 xMax=$MAXX nocolinear=1
# TODO

group group3 13
limits nMax=800 xMax=$MAXX
include_group group2
include_group group1
tc mediumn0 gen_random n=800  maxx=$MAXX
tc mediumn1 gen_random n=800  maxx=$MAXX
tc mediumn2 gen_random n=800  maxx=$MAXX
tc mediumn3 gen_random n=800  maxx=$MAXX
tc mediumn4 gen_random n=800  maxx=$MAXX
tc mediumn5 gen_random n=800  maxx=$MAXX
tc mediumn6 gen_line n=800  maxx=$MAXX   lines=1
tc mediumn7 gen_line n=800  maxx=$MAXX   lines=3
tc mediumn8 gen_line n=800  maxx=$MAXX   lines=10
tc mediumn9 gen_answer_is_barely_3 800 $MAXX

group group4 13
limits nMax=$MAXN xMax=$MAXX
# Copied from group 6 below

group group5 13
limits nMax=$MAXN xMax=$MAXX convexhull=1
tc bign_convex0 gen_convex_hull n=$MAXN  maxx=$MAXX
tc bign_convex1 gen_convex_hull n=$MAXN  maxx=$MAXX
tc bign_convex2 gen_convex_hull n=$MAXN  maxx=$MAXX
tc bign_convex3 gen_convex_hull n=$MAXN  maxx=$MAXX
tc bign_convex4 gen_convex_hull n=$MAXN  maxx=$MAXX
tc bign_convex5 gen_convex_hull n=$MAXN  maxx=$MAXX

group group6 13
limits nMax=$MAXN xMax=$MAXX
include_group group5
include_group group3
tc bign0 gen_answer_is_barely_3 $MAXN $MAXX
tc bign1 gen_random n=$MAXN  maxx=$MAXX
tc bign2 gen_random n=$MAXN  maxx=$MAXX
tc bign3 gen_random n=$MAXN  maxx=$MAXX
tc bign4 gen_random n=$MAXN  maxx=$MAXX
tc bign5 gen_random n=$MAXN  maxx=$MAXX
tc bign6 gen_random n=$MAXN  maxx=$MAXX
tc bign7 gen_line n=$MAXN  maxx=$MAXX    lines=1
tc bign8 gen_line n=$MAXN  maxx=$MAXX    lines=3
tc bign9 gen_line n=$MAXN  maxx=$MAXX    lines=10
tc bign10 gen_random n=$MAXN  maxx=32 # The smallest square that fits 4000 points
tc bign11 gen_answer_is_2 $MAXN $MAXX

wait
for A in secret/group6/*.in; do
	# We don't have output validator flags per test group in Kattis, so hack it by adding some whitespace
	B=$(basename $A .in)
	echo ' ' > secret/group4/offbyone-$B.in
	cat secret/group6/$B.in >> secret/group4/offbyone-$B.in
	cp secret/group6/$B.ans secret/group4/offbyone-$B.ans
done
