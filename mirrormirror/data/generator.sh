#!/usr/bin/env bash

PPATH=$(realpath ..)

# Inkludera hjälpskriptet. Kopiera hela testdata_tools-mappen och lägg in i repot och
# referera till den härifrån.
. ../../testdata_tools/gen.sh

# Välj vilken lösning som ska användas för att generera svar-filerna, ska finnas i
# submissions/accepted/. Kör på en tom .py-fil tills vi har en faktisk lösning:
use_solution cubic.cpp opt

# Specificera vilka generatorer som finns
compile gen_random.py
compile gen_convex_hull.py
compile gen_line.py
compile gen_answer_is_2.cpp
compile gen_answer_is_barely_3.cpp

# Hjälpvariabler, helt frivilligt men gör det enkelt att ändra gränserna senare

# Antal punkter
MAXN=4000

# Högsta absolutbeloppet av en koordinat (|xi| <= MAXX && |yi| <= MAXX)
MAXX=30000

# Specifikation av sample-datan. Det bör existera en mapp data/sample/ med filer 1.in,
# 2.in, ... som alla nämns som "sample X" nedan.
# .ans- och testdata.yaml-filerna autogenereras.
# Parametrarna i limits skickas till inputvalidatorn.
samplegroup
limits nMax=$MAXN xMax=$MAXX
sample 1

# Declarera grupp 1, med 5 poäng (av max 100 som är kutym, även om just coding cup-finalen
# körde andra totalsummor förra året)
# "tc a b c d" betyder "skapa ett testfall med namn a genom att anropa generator b med
# parametrar c d... och sist ett slumpseed"
# (anledningen till att testdata_tools beräknar och skickar med ett slumpseed är att
# generatorn då kan blir helt deterministisk, så att man inte får ny testdata varje gång
# man kör skriptet)

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

# konstruera testgrupp 2

group group3 13
limits nMax=800 xMax=$MAXX
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

# konstruera testgrupp 4

group group5 13
limits nMax=$MAXN xMax=$MAXX
tc bign_convex0 gen_convex_hull n=$MAXN  maxx=$MAXX
tc bign_convex1 gen_convex_hull n=$MAXN  maxx=$MAXX
tc bign_convex2 gen_convex_hull n=$MAXN  maxx=$MAXX
tc bign_convex3 gen_convex_hull n=$MAXN  maxx=$MAXX
tc bign_convex4 gen_convex_hull n=$MAXN  maxx=$MAXX
tc bign_convex5 gen_convex_hull n=$MAXN  maxx=$MAXX

group group6 13
limits nMax=$MAXN xMax=$MAXX
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
