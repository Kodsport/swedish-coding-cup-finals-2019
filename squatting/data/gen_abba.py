from util import *
import string

n = 2 ** int(cmdlinearg('logn'))

alphabet = string.ascii_lowercase + '0123456789'

print(5)
for it in range(5):
    abba = ''.join(chr(101 + (bin(i).count('1') + i) % 2 * 8) for i in range(n))
    print(random.choice(alphabet) + abba)
