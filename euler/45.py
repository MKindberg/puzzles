def T(n):
    return n*(n+1)//2
def P(n):
    return n*(3*n-1)//2
def H(n):
    return n*(2*n-1)

nxt = [T, P, H]
idx = [286, 166, 144]
num = [nxt[i](idx[i]) for i in range(3)]

while not (num[0] == num[1] and num[0] == num[2] and num[1] == num[2]):
    mn = min(num)
    i = num.index(mn)
    idx[i] += 1
    num[i] = nxt[i](idx[i])

print(num[0])
