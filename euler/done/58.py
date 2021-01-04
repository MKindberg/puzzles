from math import *

def is_prime(n):
    if n == 2:
        return True
    for i in range(2, ceil(sqrt(n))+1):
        if n % i == 0:
            return False
    return True

primes = []
non_primes = [1]
ratio = 1
side = 1
n = 1
while ratio >= 0.1:
    side += 2
    for i in range(4):
        n+=side-1
        if is_prime(n):
            primes.append(n)
        else:
            non_primes.append(n)
    ratio = len(primes)/(len(primes)+len(non_primes))

print(side)
