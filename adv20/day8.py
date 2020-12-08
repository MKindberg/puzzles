def swap(i):
    if i == "nop":
        return "jmp"
    elif i == "jmp":
        return "nop"
    return i

def run_program(program):
    current = 0
    acc = 0
    res = 0
    executed = [False] * len(program)
    while i != len(program):
        instruction, arg = program[i]
        if executed[i]:
            res = 1
            break
        executed[i] = True
        if instruction == "nop":
            pass
        elif instruction == "acc":
            acc += arg
        elif instruction == "jmp":
            i += arg
            continue
        i += 1
    return (res, acc)

f = open("inp8.txt", "r")
data = f.read().strip().split("\n")
f.close()

program = list(map(lambda x: [x.split()[0], int(x.split()[1])], data))


acc = 0
print(run_program(program)[1])
for i in program:
    if i[0] == "nop" or i[0] == "jmp":
        i[0] = swap(i[0])
        res, acc = run_program(program)
        i[0] = swap(i[0])
        if res == 0:
            break

print(acc)


