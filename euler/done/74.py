from math import factorial

def digit_factorial(n):
    s = 0
    for d in str(n):
        s += factorial(int(d))
    return s

def chainlen(n):
    chain = [n]
    df = n
    while len(chain) < 61:
        df = digit_factorial(df)
        if df in chain:
            return len(chain)
        chain.append(df)
    return -1
        
assert chainlen(69) == 5
assert chainlen(78) == 4
assert chainlen(540) == 2
assert chainlen(169) == 3
assert chainlen(871) == 2
assert chainlen(872) == 2

len60 = 0
for i in range(1000000):
    if chainlen(i) == 60:
        len60 += 1

print(len60)
