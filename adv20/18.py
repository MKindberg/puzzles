def parse_rec(exp, i):
    parsed = []
    j = i
    while j < len(exp):
        if exp[j] == '(':
            sub, j = parse_rec(exp, j+1)
            parsed.append(sub)
        elif exp[j] == ')':
            break
        else:
            parsed.append(exp[j])
        j += 1

    return parsed, j
def parse(exp):
    res, _ = parse_rec(exp, 0)
    return res

def group_plus(exp):
    exp2 = [group_plus(exp[0]) if isinstance(exp[0], list) else exp[0]]
    j = 1
    while j < len(exp) - 1:
        term2 = group_plus(exp[j+1]) if isinstance(exp[j+1], list) else exp[j+1]
        if exp[j] == '+':
            exp2.append([exp2.pop(), '+', term2])
        elif exp[j] == '*':
            exp2.append('*')
            exp2.append(term2)
        else:
            print("Error in grouping!")
            exit()
        j += 2
    return exp2

def solve(exp):
    ans = solve(exp[0]) if isinstance(exp[0], list) else int(exp[0])
    j = 1
    while j < len(exp) - 1:
        term2 = solve(exp[j+1]) if isinstance(exp[j+1], list) else int(exp[j+1])
        if exp[j] == '+':
            ans += term2
        elif exp[j] == '*':
            ans *= term2
        else:
            print("Error in solving!")
            exit()
        j += 2
    return ans

f = open("18.in", "r")
data = f.read().strip().splitlines()
f.close()
data = [x.replace(' ', '') for x in data]

print(sum(map(lambda x: solve(parse(x)), data)))
print(sum(map(lambda x: solve(group_plus(parse(x))), data)))
