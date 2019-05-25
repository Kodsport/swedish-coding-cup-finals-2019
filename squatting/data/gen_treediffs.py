from util import *
import string

n = int(cmdlinearg('n'))
l = int(cmdlinearg('l'))

alphabet = string.ascii_lowercase + '0123456789'

strs = [
    ''.join(random.choice(alphabet) for _ in range(l))
]

for i in range(1, n):
    base = list(random.choice(strs))
    mod = base[:]
    while mod == base:
        mod[random.randrange(l)] = random.choice(alphabet)
    strs.append(''.join(mod))

strs = sorted(list(set(strs)))
random.shuffle(strs)
print(len(strs))
for s in strs:
    print(s)
