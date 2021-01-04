import math
tot = 0

num = 1
den = 2
for _ in range(1000):
    num2=den
    den2 = 2*den+num
    num = num2//math.gcd(num2, den2)
    den = den2//math.gcd(num2, den2)
    if len(str(num+den)) > len(str(den)):
        tot += 1

print(tot)
