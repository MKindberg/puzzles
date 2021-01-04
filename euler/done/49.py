import itertools
import math

primes = [2, 3, 5, 7, 11, 13]
def is_prime(n):
    if n in primes:
        return True
    for p in primes:
        if n % p == 0:
            return False
        if p > math.sqrt(n):
            primes.append(n)
            return True
    primes.append(n)
    return True

for i in range(15, 10000, 2):
    is_prime(i)

p1000 = primes.index(1009)
pp = set() 
for i in primes[p1000:]:
    p = [int(''.join(x)) for x in sorted(set(itertools.permutations(str(i))))]
    p = list(filter(lambda x: x > 1000 and is_prime(x), p))
    if(i != p[0]):
        continue
    for k in range(len(p)-2):
        if not is_prime(p[k]):
            continue
        for l in range(k+1, len(p)-1):
            if not is_prime(p[l]):
                continue
            for m in range(l+1, len(p)):
                if not (p[l]-p[k] == p[m]-p[l] and is_prime(p[m])):
                    continue
                pp.add((p[k], p[l], p[m]))

for p in pp:
    print(p)
    print(*p, sep='')
