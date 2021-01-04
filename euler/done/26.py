from decimal import *

def shortest_cycle(d):
    for i in range(1, 1000):
        if d[5:i+5] == d[i+5:2*i+5]: # Cycles don't have to start on the first decimal
            return i
    return 0

getcontext().prec = 2000
mx = 0
mx_i = 0
for i in range(3, 1000, 2):
    d = Decimal(1)/Decimal(i)
    d = str(d)[2:]
    if len(d) < 500:
        continue
    s = shortest_cycle(d)
    if mx < s:
        mx = s
        mx_i = i

print(mx_i, mx)
