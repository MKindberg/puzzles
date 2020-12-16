import re

def is_valid(f, val):
    return (val >= f[0][0] and val <= f[0][1]) or (val >= f[1][0] and val <= f[1][1])

def find_unique(l, c):
    i = len(c)
    if i >= len(l):
        return c+["done"]
    for e in l[i]:
        if e not in c:
            u = find_unique(l, c+[e])
            if u != []:
                return u
    return []


f = open("16.in", "r")
blocks = f.read().strip().split("\n\n")
f.close()


# Parse fields
fieldPattern = "([a-z ]+): (\d+)-(\d+) or (\d+)-(\d+)"
fields = {}
for line in blocks[0].splitlines():
    m = re.match(fieldPattern, line)
    fields[m.group(1)] = [(int(m.group(2)), int(m.group(3))), (int(m.group(4)), int(m.group(5)))]

# Parse tickets
tickets = [[int(x) for x in blocks[1].splitlines()[1].split(',')]]
for line in blocks[2].splitlines()[1:]:
    tickets.append([int(x) for x in line.split(',')])

# Filter out valid
sum_invalid = 0
valid_tickets = []
for ticket in tickets:
    for val in ticket:
        invalid = True
        for f in fields.values():
            if is_valid(f, val):
                invalid = False
                break
        if invalid:
            sum_invalid += val
            break
    if not invalid:
        valid_tickets.append(ticket)

print(sum_invalid)

# Find all possible valid fields for each place
possible_fields = [list(fields.keys()) for x in range(len(tickets[0]))]
for i in range(len(possible_fields)):
    for t in valid_tickets:
        for f in possible_fields[i]:
            if not is_valid(fields[f], t[i]):
                possible_fields[i].remove(f)
                break

# Sort to make next step faster
for i in range(len(possible_fields)):
    possible_fields[i] = sorted(possible_fields[i])
# Find the unique field matching each place
u_fields = find_unique(possible_fields, [])

# Calculate product of departure* fields
prod = 1
for i in range(len(u_fields)):
    if "departure" in u_fields[i]:
        prod *= tickets[0][i]
print(prod)
