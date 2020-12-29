import math
import itertools

def is_prime(n):
    for i in range(2, math.ceil(math.sqrt(n))):
        if n % i == 0:
            return False
    return True

m = 0
for i in range(10, 2, -1):
    nums = ''.join(map(str, range(1, i)))
    for j in itertools.permutations(nums):
        n = int(''.join(j))
        if n > m and is_prime(n):
            m = n
    if m != 0:
        break

print(m)
