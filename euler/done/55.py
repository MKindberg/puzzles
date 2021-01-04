def is_palindrome(n):
    return str(n) == str(n)[::-1]

def next_num(n):
    return i+int(str(i)[::-1])

lychrel = 0
for i in range(1, 10000):
    for _ in range(50):
        i = next_num(i)
        if is_palindrome(i):
            break
    else:
        lychrel += 1

print(lychrel)
