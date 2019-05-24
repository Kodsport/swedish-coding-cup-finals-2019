from util import *
import string

S = int(float(cmdlinearg('s')))
minLength = int(cmdlinearg('minLength'))
maxLength = int(cmdlinearg('maxLength'))

alphabet = string.ascii_lowercase + '0123456789'

domains = set()
ret = []
attemptsLeft = 1e7 // minLength
while S > 0 and attemptsLeft > 0:
    attemptsLeft -= 1
    length = min(random.randint(minLength, maxLength), S)
    domain = ''.join(random.choice(alphabet) for _ in range(length))
    if domain not in domains:
        domains.add(domain)
        ret.append(domain)
        S -= length
    if S <= 3 and attemptsLeft > 20:
        attemptsLeft = 20

print(len(domains))
for domain in ret:
    print(domain)
