import math
import time

def encrypt(loop_count, subj):
    return pow(subj, loop_count, 20201227)

def calc_loop_size(pub_key):
    val = 1
    loop = 0
    while val != pub_key:
        val = (val*7)%20201227
        loop += 1
    return loop

card_pub = 12578151
door_pub = 5051300

card_loop = calc_loop_size(card_pub)
door_loop = calc_loop_size(door_pub)

e_card = encrypt(card_loop, door_pub)
e_door = encrypt(door_loop, card_pub)

assert e_card == e_door

print(e_card)
