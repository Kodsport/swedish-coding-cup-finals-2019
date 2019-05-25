from util import *
import random

num1 = int(cmdlinearg('1'))
num2 = int(cmdlinearg('2'))
numb = int(cmdlinearg('b'))
k = int(cmdlinearg('k'))
mult = float(cmdlinearg('mult', 1))

num1 = int(num1 * mult)
num2 = int(num2 * mult)
numb = int(numb * mult)

days = []
for i in range(num1):
    days.append('1')
for i in range(num2):
    days.append('2')
for i in range(numb):
    days.append('B')
random.shuffle(days)
print(len(days), k)
print(''.join(days))
