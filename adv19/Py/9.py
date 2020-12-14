import itertools

def get_arg(program, mode, rel_base, argN):
    m = mode % 10
    res = 0
    if m == 0:
        res = program[argN]
    elif m == 1:
        res = argN
    elif m == 2:
        res = program[argN] + rel_base
    else:
        print("Invalid mode " + str(mode))
        exit()
    return (res, mode // 10)

def run_program(p, inp, first_inst = 0, first_inp = 0, reset = True):
    if reset:
        program = p[:]
    else:
        program = p

    output = []
    inp_count = first_inp
    i = first_inst
    rel_base = 0
    while program[i] != 99:
        instruction = program[i]
        opcode = instruction % 100
        mode = instruction // 100
        if opcode == 1: # Add
            arg1, mode = get_arg(program, mode, rel_base, i+1)
            arg2, mode = get_arg(program, mode, rel_base, i+2)
            arg3, mode = get_arg(program, mode, rel_base, i+3)
            program[arg3] = program[arg1] + program[arg2]
            i += 4
        elif opcode == 2: # Multiply
            arg1, mode = get_arg(program, mode, rel_base, i+1)
            arg2, mode = get_arg(program, mode, rel_base, i+2)
            arg3, mode = get_arg(program, mode, rel_base, i+3)
            program[arg3] = program[arg1] * program[arg2]
            i += 4
        elif opcode == 3: # Input
            arg1, mode = get_arg(program, mode, rel_base, i+1)
            program[arg1] = inp[inp_count]
            inp_count += 1
            i += 2
        elif opcode == 4: # Output
            arg1, mode = get_arg(program, mode, rel_base, i+1)
            output.append(program[arg1])
            i += 2
        elif opcode == 5: # Jump if
            arg1, mode = get_arg(program, mode, rel_base, i+1)
            arg2, mode = get_arg(program, mode, rel_base, i+2)
            if program[arg1] != 0:
                i = program[arg2]
            else:
                i += 3
        elif opcode == 6: # Jump if not
            arg1, mode = get_arg(program, mode, rel_base, i+1)
            arg2, mode = get_arg(program, mode, rel_base, i+2)
            if program[arg1] == 0:
                i = program[arg2]
            else:
                i += 3
        elif opcode == 7: # Less than
            arg1, mode = get_arg(program, mode, rel_base, i+1)
            arg2, mode = get_arg(program, mode, rel_base, i+2)
            arg3, mode = get_arg(program, mode, rel_base, i+3)
            if program[arg1] < program[arg2]:
                program[arg3] = 1
            else:
                program[arg3] = 0
            i += 4
        elif opcode == 8: # Equal
            arg1, mode = get_arg(program, mode, rel_base, i+1)
            arg2, mode = get_arg(program, mode, rel_base, i+2)
            arg3, mode = get_arg(program, mode, rel_base, i+3)
            if program[arg1] == program[arg2]:
                program[arg3] = 1
            else:
                program[arg3] = 0
            i += 4
        elif opcode == 9: # Relative
            arg1, mode = get_arg(program, mode, rel_base, i+1)
            rel_base += program[arg1]
            i += 2
        else:
            print("Invalid opcode " + str(opcode))
            exit()
    return (-1, output)

f = open("../inp/9.in", "r")
data = f.read().strip()
f.close()
program = [int(x) for x in data.split(",")]

print(run_program(program+[0]*1000, [2]))
