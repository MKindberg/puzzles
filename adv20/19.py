import re

def expand_rules(rules, n, d):
    if d > 10:
        return 'x'
    if not rules[n][0].isdigit():
        if rules[n][0] == '"':
            rules[n] = rules[n][1:-1]
        return rules[n]
    expanded = []
    for i in rules[n].split():
        if i == '|':
            expanded.append('|')
        else:
            expanded.append(expand_rules(rules, int(i), d+1))
    rules[n] = '(' + ''.join(expanded) + ')'
    return rules[n]


f = open("19.in", "r")
data = f.read().strip().split('\n\n')
f.close()

rules = [[int(x.split(": ")[0]), x.split(": ")[1]] for x in data[0].splitlines()]
rules = [x[1] for x in sorted(rules, key=lambda x: x[0])]

messages = data[1].splitlines()

expand_rules(rules, 0, 0)

matches = 0
for m in messages:
    if re.fullmatch(rules[0], m) != None:
        matches += 1

print(matches)

rules = [[int(x.split(": ")[0]), x.split(": ")[1]] for x in data[0].splitlines()]
rules = [x[1] for x in sorted(rules, key=lambda x: x[0])]
rules[8] = "42 | 42 8"
rules[11] = "42 31 | 42 11 31"

expand_rules(rules, 0, 0)

matches = 0
for m in messages:
    if re.fullmatch(rules[0], m) != None:
        matches += 1

print(matches)
