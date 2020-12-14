import re
import itertools
from copy import deepcopy

def add_mem(mem, mask, addr, val):
    new_val = []
    bin_val = bin(val)[2:]
    masked = itertools.zip_longest(bin_val[::-1], mask[::-1], fillvalue = '0')
    for m in masked:
        if m[1] == 'X':
            new_val.append(m[0])
        else:
            new_val.append(m[1])
    mem[addr] = int(''.join(new_val[::-1]), 2)
    return mem

def add_mem2(mem, mask, addr, val):
    new_addr = [[]]
    bin_addr = bin(addr)[2:]
    masked = itertools.zip_longest(bin_addr[::-1], mask[::-1], fillvalue = '0')
    for m in masked:
        if m[1] == '0':
            for n in new_addr:
                n.append(m[0])
        elif m[1] == '1':
            for n in new_addr:
                n.append('1')
        else:
            n0 = []
            for n in new_addr:
                n0.append(n+['0'])
                n.append('1')
            new_addr += n0

    for i in range(len(new_addr)):
        a = int(''.join(new_addr[i][::-1]), 2)
        mem[a] = val
    return mem

def init_mem(data, mem_func):
    mem = {}
    mask = ""
    p_mask = "mask = ([01X]+)"
    p_mem = "mem\[(\d+)\] = (\d+)"
    for i in data:
        m_mask = re.match(p_mask, i)
        m_mem = re.match(p_mem, i)
        addr = 0
        val = 0
        if m_mask:
            mask = m_mask.group(1)
        elif m_mem:
            addr = int(m_mem.group(1))
            val = int(m_mem.group(2))
            mem = mem_func(mem, mask, addr, val)
        else:
            print("Error!")
            exit(1)
    return mem

f = open("14.in", "r")
data = f.read().strip().splitlines()
f.close()

mem = init_mem(data, add_mem)
print(sum(mem.values()))
mem = init_mem(data, add_mem2)
print(sum(mem.values()))
