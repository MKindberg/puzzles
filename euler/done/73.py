from math import floor, ceil, gcd

fracs = 0

for d in range(4, 12001):
    for r in range(ceil(d/3), ceil(d/2)):
        if gcd(d, r) == 1:
            fracs += 1

print(fracs)
