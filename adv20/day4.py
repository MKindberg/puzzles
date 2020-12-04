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

def validate(acc, passport):
    valid = True
    for i in range(len(rules)):
        m = re.search(rules[i][0], passport)
        if m == None:
            return acc
        valid = valid and rules[i][1](m.group(1))
    if valid:
        return (acc[0]+1, acc[1]+1)
    return (acc[0]+1, acc[1])

f = open("inp4.txt", "r")
data = f.read().split("\n\n")
f.close()

print(functools.reduce(validate, data, (0, 0)))
