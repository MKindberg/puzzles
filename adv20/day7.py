import re
import functools

def can_be_contained(parents, bag):
    return functools.reduce(lambda acc, x: acc.union(can_contain(parents, x)), parents.get(bag, set()), parents.get(bag, set()))

def contains(children, bag):
    return functools.reduce(lambda acc, x: acc + int(x[0]) * contains(children, x[1]), children[bag], 1)

f = open("inp7.txt", "r")
rules = f.read().strip().split("\n")
f.close()

container_pattern = "(.*) bags contain"
content_pattern = "(?:contain|,) (\d*) (.*?) bag"

parents = {}
children = {}

for rule in rules:
    container = re.search(container_pattern, rule).group(1)
    content = re.findall(content_pattern, rule)
    for c in content:
        parents[c[1]] = parents.get(c[1], set()).union({container})
    children[container] = content

print(len(can_be_contained(parents, "shiny gold")))

print(contains(children, "shiny gold") - 1)
