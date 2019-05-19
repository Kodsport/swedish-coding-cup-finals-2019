from util import *
import random

NUM1    = int(cmdlinearg('NUM1'))
NUM2    = int(cmdlinearg('NUM2'))
NUMB    = int(cmdlinearg('NUMB'))

days = []
for i in range(NUM1):
    days.append('1')
for i in range(NUM2):
    days.append('2')
for i in range(NUMB):
    days.append('B')
random.shuffle(days)
print(len(days))
print(''.join(map(str, days)))
