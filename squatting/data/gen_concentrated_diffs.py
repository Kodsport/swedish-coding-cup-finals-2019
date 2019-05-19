from random import randint
from util import *

S    = int(cmdlinearg('S'))
length    = int(cmdlinearg('length'))

baseString = ""
for i in range(length):
    baseString += (chr(ord('a')+randint(0, 25)))

domains = set()
domains.add(baseString)
attemptsLeft = 1e7//length
maxI = 0
while 2**(maxI+1) < length:
    maxI += 1

while S >= length and attemptsLeft > 0:
    attemptsLeft -= 1
    i = randint(0, maxI)
    j = 2**i
    domain = ""
    for k in range(j):
        domain += (chr(ord('a')+randint(0, 25)))
    domain = baseString[:(length-j)] + domain
    if not domain in domains:
        domains.add(domain)
        S -= length

print(len(domains))
for domain in domains:
    print(domain)
