import math

limit = 50000000

primes = [2, 3, 5, 7, 11, 13]
def is_prime(n):
    if n in primes:
        return True
    for p in primes:
        if n % p == 0:
            return False
        if p > math.sqrt(n):
            break
    primes.append(n)
    return True

for i in range(primes[-1]+1, math.ceil(math.sqrt(limit))):
    is_prime(i)

count = 0
nums = set()
for p1 in primes:
    if p1**2 + 2**3 + 2**4 >= limit:
        break
    for p2 in primes:
        if p1**2 + p2**3 + 2**4 >= limit:
            break
        for p3 in primes:
            if p1**2 + p2**3 + p3**4 >= limit:
                break
            nums.add(p1**2+p2**3+p3**4)
print(len(nums))
