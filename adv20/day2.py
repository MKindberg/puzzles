import re

f = open("inp2.txt", "r")
pwds = f.read().split("\n")
f.close()

pattern = "^(\d+)-(\d+) ([a-z]): ([a-z]+)$"

num_valid1 = 0
num_valid2 = 0
for data in pwds[:-1]:
    m = re.match(pattern, data)
    low = int(m.group(1))
    high = int(m.group(2))
    letter = m.group(3)
    pwd = m.group(4)

    num = len(list(filter(lambda l: l == letter, pwd)))
    if(num >= low and num <= high):
        num_valid1 += 1
    if(pwd[low-1] == letter and pwd[high-1] != letter or
       pwd[low-1] != letter and pwd[high-1] == letter):
        num_valid2 += 1

print(num_valid1)
print(num_valid2)
