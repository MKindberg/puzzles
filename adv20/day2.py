import re
import functools

def validate(num_valid, string):
    pattern = "^(\d+)-(\d+) ([a-z]): ([a-z]+)$"
    m = re.match(pattern, string)
    low = int(m.group(1))
    high = int(m.group(2))
    letter = m.group(3)
    pwd = m.group(4)

    num = len(list(filter(lambda l: l == letter, pwd)))
    if(num >= low and num <= high):
        num_valid[0] += 1
    if(pwd[low-1] == letter and pwd[high-1] != letter or
       pwd[low-1] != letter and pwd[high-1] == letter):
        num_valid[1] += 1
    return num_valid


f = open("inp2.txt", "r")
pwds = f.read().split("\n")
f.close()

print(functools.reduce(validate, pwds[:-1], [0, 0]))
