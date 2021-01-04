import itertools
divisors = [1, 2, 3, 5, 7, 11, 13, 17]

s = 0
for p in itertools.permutations('0123456789'):
    p = ''.join(p)
    for i in range(1, len(divisors)):
        if int(p[i:i+3]) % divisors[i] != 0:
            break
    else:
        s += int(p)

print(s)



