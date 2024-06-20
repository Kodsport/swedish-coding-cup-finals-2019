from util import *
import random

numn = int(cmdlinearg('n'))
k = int(cmdlinearg('k'))

days = []
for i in range(min(numn//k, k)):
    I = i % k
    for j in range(I+1):
        days.append('B')
    days.append('1')
    for j in range(k-I-2):
        days.append('B')
while len(days) < numn:
    days.append('B')
while len(days) > numn:
    del days[-1]
print(len(days), k)
print(''.join(days))
