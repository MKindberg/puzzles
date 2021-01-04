# https://mathworld.wolfram.com/FullReptendPrime.html
mx = 0
mx_p = 0

for p in range(3, 1000, 2):
    for k in range(1, p):
        r = pow(10, k, p)
        if r == 0:
            break
        if r == 1:
            if k > mx:
                mx = k
                mx_p = p
            break

print(mx_p, mx)
