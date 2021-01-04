# Takes almost 10 minutes
import math

def phi(n):
    res = 0
    step = 2 - (n % 2)
    for i in range(1, n//2+1, step):
        if math.gcd(i, n) == 1:
            res += 2
    return res


m = 0
v = 0
for i in range(999990, 10, -30):
    ratio = i/phi(i)
    if m < ratio:
        m = ratio
        v = i

print(v, m)
