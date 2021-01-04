mod = 1000000007

def s(n):
    return ((n%9+1) * pow(10, n//9, mod) -1) % mod

def S(k):
    acc = (4*pow(10, (k)//9, mod)+ pow(10, (k)//9, mod)-5) % mod
    acc = (acc + (pow(10, (k)//9, mod)-1) - 9*((k)//9)) % mod
    for i in range((k) % 9):
        acc = (acc + s(k-i)) % mod
    return acc 
fib = [0, 1]

for _ in range(2, 91):
    fib.append((fib[-2] + fib[-1]))

acc = 0
for f in fib[2:]:
    r = S(f)
    acc = (acc + r) % mod

print(acc)
