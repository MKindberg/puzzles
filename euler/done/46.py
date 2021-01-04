import math
primes = [2]
def is_prime(n):
    for p in primes:
        if n % p == 0:
            return False
        if p > math.sqrt(n):
            break
    primes.append(n)
    return True

def goldbach(n):
    for p in primes:
        s = p
        j = 0
        while s <= i:
            j += 1
            s = p+2*j**2
            if s == i:
                return True
    return False

i = 1
while True:
    i += 2
    if is_prime(i):
        continue
    if not goldbach(i):
        break

print(i)
