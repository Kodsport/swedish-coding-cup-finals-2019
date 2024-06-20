#!/usr/bin/env bash

PPATH=$(realpath ..)

. ../../testdata_tools/gen.sh

use_solution sl.cpp

compile gen_rand.py
compile gen_param.py

E18=1000000000000000000

samplegroup
limits maxW=$E18 maxK=$E18
sample 1
sample 2
sample 3

tw() {
  tc $1-rand-01 gen_rand maxW=$2 maxK=$3
  tc $1-rand-02 gen_rand maxW=$2 maxK=$3
  tc $1-rand-03 gen_rand maxW=$2 maxK=$3
  tc $1-rand-04 gen_rand maxW=$2 maxK=$3
  tc $1-rand-05 gen_rand maxW=$2 maxK=$3
  tc $1-rand-06 gen_rand maxW=$2 maxK=$3
  tc $1-fails-begin-01 gen_param maxW=$2 maxK=$3 ival=begin
  tc $1-fails-begin-02 gen_param maxW=$2 maxK=$3 ival=begin
  tc $1-fails-begin-03 gen_param maxW=$2 maxK=$3 ival=begin
  tc $1-fails-beginzero-01 gen_param maxW=$2 maxK=$3 ival=beginzero
  tc $1-fails-beginzero-02 gen_param maxW=$2 maxK=$3 ival=beginzero
  tc $1-fails-beginzero-03 gen_param maxW=$2 maxK=$3 ival=beginzero
  tc $1-fails-mid-01 gen_param maxW=$2 maxK=$3 ival=mid
  tc $1-fails-mid-02 gen_param maxW=$2 maxK=$3 ival=mid
  tc $1-fails-mid-03 gen_param maxW=$2 maxK=$3 ival=mid
  tc $1-fails-end-01 gen_param maxW=$2 maxK=$3 ival=end
  tc $1-fails-end-02 gen_param maxW=$2 maxK=$3 ival=end
  tc $1-fails-end-03 gen_param maxW=$2 maxK=$3 ival=end
  tc $1-fails-underbegin-01 gen_param maxW=$2 maxK=$3 ival=underbegin
  tc $1-fails-underbegin-02 gen_param maxW=$2 maxK=$3 ival=underbegin
  tc $1-fails-underbegin-03 gen_param maxW=$2 maxK=$3 ival=underbegin
  tc $1-fails-overend-01 gen_param maxW=$2 maxK=$3 ival=overend
  tc $1-fails-overend-02 gen_param maxW=$2 maxK=$3 ival=overend
  tc $1-fails-overend-03 gen_param maxW=$2 maxK=$3 ival=overend
}

# Bruteforce over K
group g1 5
limits maxW=$E18 maxK=10
tw 1 $E18 10
tc 1
tc 2
tc 3

# DP over (curweight, days)
group g2 10
limits maxW=1000 maxK=1000
tw 2 1000 1000
tc 1
tc 2
tc 3

# Naively loop over number of failures and simulate having every number of them in beginning/end
group g3 10
limits maxW=$E18 maxK=1000
include_group g1
include_group g2
tw 3 $E18 1000
tc 1
tc 2
tc 3

# Various high-constant factor interval-based solution in O(number of days)
group g4 5
limits maxW=$E18 maxK=10000
include_group g1
include_group g2
include_group g3
tw 4 $E18 10000
tc 1
tc 2
tc 3

# Reduce to either case 2 or 3 by realizing you never need more than O(X+Z) if it possible
group g5 4
limits maxW=1000 maxK=$E18
include_group g2
tw 5 1000 $E18
tc 1
tc 2
tc 3

# General solution
group g6 11
limits maxW=$E18 maxK=$E18
include_group g1
include_group g2
include_group g3
include_group g4
include_group g5
tw 6 $E18 $E18
tc 1
tc 2
tc 3
