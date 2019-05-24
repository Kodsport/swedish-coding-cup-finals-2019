from util import *
import random
import string

def rand_name():
    le = random.choice([8,9,10])
    return ''.join(random.choice(string.ascii_lowercase) for _ in range(le))

l = int(cmdlinearg('l'))
k = int(cmdlinearg('k'))
n = int(cmdlinearg('n'))
onlyacq = int(cmdlinearg('onlyacq', 0))

mutex_names = [rand_name() for _ in range(k)]

func_starts = [0] + random.sample(range(1, l), n-1)
funcs = []
func_name = None
prev_func_names = []
for i in range(l):
    if i in func_starts:
        instr = []
        if func_name is not None:
            prev_func_names.append(func_name)
        func_name = 'main' if len(funcs) == n-1 else rand_name()
        funcs.append((instr, func_name))

    t = random.randrange(4)
    if t == 3 and prev_func_names:
        ins = ('call', random.choice(prev_func_names))
    elif onlyacq:
        ins = ('acquire', random.choice(mutex_names))
    else:
        ins = (['release', 'acquire', 'access', 'acquire'][t], random.choice(mutex_names))
    instr.append(ins)

assert len(funcs) == n
random.shuffle(funcs)

print(n)
for fu in funcs:
    print(len(fu[0]), fu[1])
    for ins in fu[0]:
        print(ins[0], ins[1])
