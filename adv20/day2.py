import re
import functools

def parse(string):
    pattern = "^(\d+)-(\d+) ([a-z]): ([a-z]+)$"
    m = re.match(pattern, string)
    low = int(m.group(1))
    high = int(m.group(2))
    letter = m.group(3)
    pwd = m.group(4)
    return (low, high, letter, pwd)

def rule1(data):
    low = data[0]
    high = data[1]
    letter = data[2]
    pwd = data[3]

    num = len(list(filter(lambda l: l == letter, pwd)))
    return num >= low and num <= high

def rule2(data):
    low = data[0]
    high = data[1]
    letter = data[2]
    pwd = data[3]

    return (pwd[low-1] == letter and pwd[high-1] != letter or
           pwd[low-1] != letter and pwd[high-1] == letter)

f = open("inp2.txt", "r")
pwds = f.read().split("\n")[:-1]
f.close()

data = list(map(parse, pwds))
print(len(list(filter(rule1, data))))
print(len(list(filter(rule2, data))))
