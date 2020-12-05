import time
import re
import functools

rules = [
    (r"byr:(\S+)", lambda byr: int(byr) >= 1920 and int(byr) <= 2002),
    (r"iyr:(\S+)", lambda iyr: int(iyr) >= 2010 and int(iyr) <= 2020),
    (r"eyr:(\S+)", lambda eyr: int(eyr) >= 2020 and int(eyr) <= 2030),
    (r"hgt:(\S+)", lambda hgt: hgt[-2:] == "cm" and int(hgt[:-2]) >= 150 and int(hgt[:-2]) <= 193 or hgt[-2:] == "in" and int(hgt[:-2]) >= 59 and int(hgt[:-2]) <= 76),
    (r"hcl:(\S+)", lambda hcl: re.match(r"^#[0-9a-f]{6}$", hcl) != None),
    (r"ecl:(\S+)", lambda ecl: ecl in ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]),
    (r"pid:(\S+)", lambda pid: re.match(r"^\d{9}$", pid) != None)
]

def hasFields(passport):
    return functools.reduce(lambda acc, rule: re.search(rule[0], passport) != None if acc else False, rules, True)

def validateFields(passport):
    return functools.reduce(lambda acc, rule: rule[1](re.search(rule[0], passport).group(1)) if acc else False, rules, True)

f = open("inp4.txt", "r")
data = f.read().split("\n\n")
f.close()

valid1 = list(filter(hasFields, data))
print(len(valid1))

valid2 = list(filter(validateFields, valid1))
print(len(valid2))
