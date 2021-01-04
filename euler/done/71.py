from math import floor

mx = 0
nd = (0, 0)
for d in range(2, 1000001):
    n = floor(3/7*d)
    if n/d > mx and n/d != 3/7:
        mx = (n)/d
        nd = (n, d)
print(mx, nd)
