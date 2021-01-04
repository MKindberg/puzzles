import math

tot = 0

for n in range(23, 101):
    r = n//2
    i = 0
    while math.comb(n, r) > 1000000:
        i += 1
        r -= 1
    i *= 2
    if i > 0 and n % 2 == 0:
        i -= 1
    tot += i

print(tot)

