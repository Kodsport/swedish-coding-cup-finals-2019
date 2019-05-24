#!/usr/bin/env bash

PPATH=$(realpath ..)

. ../../testdata_tools/gen.sh

use_solution fieldtrip2_js.cpp

compile gen_rand.py
compile gen_samea.py
compile gen_exact.py
compile gen_onebox.py
compile gen_randomsum.py
compile gen_biggroup.py

MAXK=1000000000
MAXA=1000000000
MAXM=100000
MAXASUM=100000000000000

samplegroup
limits maxA=$MAXA maxM=$MAXM maxAsum=$MAXASUM maxK=$MAXK
sample 1
sample 2

group g1 10
limits maxA=2 maxM=$MAXM maxAsum=$MAXASUM maxK=$MAXK
tc smalla-big01 gen_rand a=1 m=100000 k=100000
tc smalla-big02 gen_rand a=2 m=100000 k=100000
tc smalla-mid01 gen_rand a=2 m=100000 k=50000
tc smalla-mid02 gen_rand a=2 m=100000 k=10000
tc smalla-mid03 gen_rand a=2 m=100000 k=1000
tc smalla-small01 gen_rand a=2 m=100000 k=2
tc smalla-small02 gen_rand a=2 m=10 k=3
tc smalla-small03 gen_rand a=2 m=10 k=3
tc smalla-small04 gen_rand a=2 m=10 k=3
tc smalla-samea01 gen_samea a=2 m=100000 k=200000
tc smalla-samea02 gen_samea a=2 m=100000 k=200001
tc smalla-samea03 gen_samea a=2 m=100000 k=2
tc smalla-exact01 gen_exact a=2 m=100000
tc smalla-exact02 gen_exact a=2 m=100000
tc smalla-exact03 gen_exact a=2 m=100000
tc smalla-onebox01 gen_onebox a=2 m=100000
tc smalla-onebox02 gen_onebox a=2 m=100000
tc smalla-onebox03 gen_onebox a=2 m=100000

group g2 11
limits maxA=$MAXA maxM=2 maxAsum=$MAXASUM maxK=$MAXK
tc smallm-big01 gen_rand a=$MAXA m=2 k=100000
tc smallm-big02 gen_rand a=$MAXA m=2 k=100000
tc smallm-big03 gen_rand a=$MAXA m=2 k=100000
tc smallm-mid01 gen_rand a=$MAXA m=2 k=1000
tc smallm-mid02 gen_rand a=$MAXA m=2 k=1000
tc smallm-mid03 gen_rand a=$MAXA m=2 k=1000
tc smallm-mid04 gen_rand a=$MAXA m=2 k=1000
tc smallm-mid05 gen_rand a=$MAXA m=2 k=1000
tc smallm-small01 gen_rand a=$MAXA m=2 k=3
tc smallm-small02 gen_rand a=$MAXA m=2 k=3
tc smallm-samea01 gen_samea a=$MAXA m=2 k=100000
tc smallm-samea02 gen_samea a=$MAXA m=2 k=2
tc smallm-exact01 gen_exact a=$MAXA m=2
tc smallm-exact02 gen_exact a=$MAXA m=2
tc smallm-exact03 gen_exact a=$MAXA m=2
tc smallm-onebox01 gen_onebox a=$MAXA m=2
tc smallm-onebox02 gen_onebox a=$MAXA m=2
tc smallm-onebox03 gen_onebox a=$MAXA m=2
tc smallm-onebox04 gen_onebox a=10 m=2
tc smallm-onebox05 gen_onebox a=10 m=2
tc smallm-onebox06 gen_onebox a=10 m=2

group g3 12
limits maxA=$MAXA maxM=$MAXM maxAsum=1000000 maxK=$MAXK
include_group g1
tc smallsum-small01 gen_randomsum suma=1000000 groups=10
tc smallsum-small02 gen_randomsum suma=1000000 groups=10
tc smallsum-small03 gen_randomsum suma=1000000 groups=100
tc smallsum-small04 gen_randomsum suma=1000000 groups=100
tc smallsum-big01 gen_randomsum suma=1000000 groups=100000
tc smallsum-big02 gen_randomsum suma=1000000 groups=100000
tc smallsum-big03 gen_randomsum suma=1000000 groups=100000
tc smallsum-big04 gen_randomsum suma=1000000 groups=100000
tc smallsum-biggroup01 gen_biggroup suma=1000000 groups=10
tc smallsum-biggroup02 gen_biggroup suma=1000000 groups=10
tc smallsum-biggroup03 gen_biggroup suma=1000000 groups=100
tc smallsum-biggroup04 gen_biggroup suma=1000000 groups=100
tc smallsum-exact01 gen_exact a=100 m=10000
tc smallsum-exact02 gen_exact a=1000 m=1000
tc smallsum-exact03 gen_exact a=10000 m=100
tc smallsum-onebox01 gen_onebox a=10000 m=100
tc smallsum-onebox02 gen_onebox a=1000 m=1000
tc smallsum-onebox03 gen_onebox a=100 m=10000

group g4 14
limits maxA=$MAXA maxM=$MAXM maxAsum=$MAXASUM maxK=$MAXK
include_group g1
include_group g2
include_group g3
tc small01 gen_randomsum suma=$MAXA groups=10
tc small02 gen_randomsum suma=$MAXA groups=10
tc small03 gen_randomsum suma=$MAXA groups=100
tc small04 gen_randomsum suma=$MAXA groups=100
tc big01 gen_randomsum suma=$MAXA groups=100000
tc big02 gen_randomsum suma=$MAXA groups=100000
tc big03 gen_randomsum suma=$MAXA groups=100000
tc big04 gen_randomsum suma=$MAXA groups=100000
tc biggroup01 gen_biggroup suma=$MAXA groups=10
tc biggroup02 gen_biggroup suma=$MAXA groups=10
tc biggroup03 gen_biggroup suma=$MAXA groups=1000
tc biggroup04 gen_biggroup suma=$MAXA groups=1000
tc biggroup05 gen_biggroup suma=$MAXA groups=100000
tc biggroup06 gen_biggroup suma=$MAXA groups=100000
tc exact01 gen_exact a=$MAXA m=10
tc exact02 gen_exact a=$MAXA m=1000
tc exact03 gen_exact a=$MAXA m=10000
tc onebox01 gen_onebox a=$MAXA m=10
tc onebox02 gen_onebox a=$MAXA m=1000
tc onebox03 gen_onebox a=$MAXA m=100000
