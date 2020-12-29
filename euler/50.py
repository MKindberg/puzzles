import math

primes = [2, 3, 5, 7, 11, 13]
def is_prime(n):
    if n in primes:
        return True
    for p in primes:
        if n % p == 0:
            return False
        if p > math.sqrt(n):
            return True
    return True

def add_prime():
    i = primes[-1] + 2
    while not is_prime(i):
        i += 2
    primes.append(i)

def in_primes(n):
    if n < primes[-1]:
        return n in primes
    return is_prime(n)

limit = 1000000

mx_len = 1
mx_sum = 0
start = 0
s = 2
i = 1
while s < limit:
    while s < limit:
        while start+i > len(primes):
            add_prime()
        if in_primes(s):
            mx_len = i
            mx_sum = s
        i += 1
        s = sum(primes[start:start+i])
    start += 1
    i = mx_len + 1
    s = sum(primes[start:start+i])

print(mx_sum, mx_len)
