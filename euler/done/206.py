from math import *
target = "1_2_3_4_5_6_7_8_9_0"
# For n^2 to end in 0 n must also end in 0
for i in range(ceil(sqrt(1020304050607080900))//10*10, floor(sqrt(1929394959697989990)), 10):
    n = str(i*i)
    for j in range(len(target)):
        if target[j] != '_' and n[j] != target[j]:
            break
    else:
        print(i)
        break
