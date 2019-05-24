from util import *
import string

S = int(float(cmdlinearg('s')))
length = int(float(cmdlinearg('length', S)))

alphabet = string.ascii_lowercase + '0123456789'

baseString = ''.join(random.choice(alphabet) for _ in range(length))

domains = set()
ret = []
domains.add(baseString)
ret.append(baseString)
S -= len(baseString)
attemptsLeft = 1e7//length
logn = 0
while 2**(logn+1) < length:
    logn += 1
assert 2**logn < length

while S >= length and attemptsLeft > 0:
    attemptsLeft -= 1
    i = random.randint(0, logn)
    j = 2**i
    domain = baseString[:(length-j)] + ''.join(random.choice(alphabet) for _ in range(j))
    if domain not in domains:
        domains.add(domain)
        ret.append(domain)
        S -= length

random.shuffle(ret)
print(len(domains))
for domain in ret:
    print(domain)
