#!/usr/bin/env bash

PPATH=$(realpath ..)

# Inkludera hjälpskriptet. Kopiera hela testdata_tools-mappen och lägg in i repot och
# referera till den härifrån.
. ../../testdata_tools/gen.sh

# Välj vilken lösning som ska användas för att generera svar-filerna, ska finnas i
# submissions/accepted/. Kör på en tom .py-fil tills vi har en faktisk lösning:
use_solution squatting_mw.cpp opt

# Specificera vilka generatorer som finns
compile gen_random.py

# Hjälpvariabler, helt frivilligt men gör det enkelt att ändra gränserna senare

# Totala antalet tecken i input
MAXS=1000000

# Specifikation av sample-datan. Det bör existera en mapp data/sample/ med filer 1.in,
# 2.in, ... som alla nämns som "sample X" nedan.
# .ans- och testdata.yaml-filerna autogenereras.
# Parametrarna i limits skickas till inputvalidatorn.
samplegroup
limits sMax=$MAXS
sample 1

# Declarera grupp 1, med 5 poäng (av max 100 som är kutym, även om just coding cup-finalen
# körde andra totalsummor förra året)
# "tc a b c d" betyder "skapa ett testfall med namn a genom att anropa generator b med
# parametrar c d... och sist ett slumpseed"
# (anledningen till att testdata_tools beräknar och skickar med ett slumpseed är att
# generatorn då kan blir helt deterministisk, så att man inte får ny testdata varje gång
# man kör skriptet)

group group1 5
limits sMax=$MAXS
tc bign0 gen_random S=$MAXS minLength=1 maxLength=10
