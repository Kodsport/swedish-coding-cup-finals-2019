from util import *
import random

# Apparently this produces inputs on which n2_jumps is slow.
# I don't really know why.

n = int(cmdlinearg('n'))
k = int(cmdlinearg('k'))

a = k
b = 0
if random.choice([True, False]):
    a,b = b,a

s = []
i = 0
while i < n:
    assert i < max(a, b)
    if i < min(a, b):
        c = random.choice('1' * 10 + '2' * 5)
    else:
        rem = max(a, b) - i
        pick = (random.uniform(0, max(1, rem - 0.5)) < 1)
        if i >= a:
            if pick:
                c = '1'
                a = min(i + k, n)
            else:
                c = random.choice('2' * 14 + 'B')
        else:
            if pick:
                c = '2'
                b = min(i + k, n)
            else:
                c = random.choice('1' * 20 + 'B')
    s.append(c)
    i += 1

print(n, k)
print(''.join(s))
