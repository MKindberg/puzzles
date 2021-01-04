import itertools

def high(hand):
    return hand[-1][0]

def pair(hand):
    for i in range(len(hand) - 1):
        if hand[i][0] == hand[i+1][0]:
            return hand[i][0]
    return -1

def two_pair(hand):
    pairs = []
    for i in range(len(hand) - 1):
        if hand[i][0] == hand[i+1][0]:
            pairs.append(hand[i][0])
    return max(pairs) if len(pairs) == 2 else -1

def three_kind(hand):
    for i in range(len(hand) - 2):
        if hand[i][0] == hand[i+1][0] and hand[i][0] == hand[i+2][0]:
            return hand[i][0]
    return -1

def straight(hand):
    for i in range(len(hand) - 1):
        if hand[i][0] != hand[i+1][0] - 1:
            return -1
    return hand[0][0]

def flush(hand):
    if len(list(filter(lambda x: x[1] == hand[0][1], hand))) == len(hand):
        return high(hand)
    return -1

def full_house(hand):
    if hand[0][0] == hand[1][0] == hand[2][0] and hand[3][0] == hand[4][0]:
        return hand[0][0]*100 + hand[4][0]
    if hand[0][0] == hand[1][0] and hand[2][0] == hand[3][0] == hand[4][0]:
        return hand[4][0]*100 + hand[0][0]
    return -1

def four_kind(hand):
    if hand[0][0] == hand[1][0] == hand[2][0] == hand[3][0] or hand[1][0] == hand[2][0] == hand[3][0] == hand[4][0]:
        return hand[1][0]
    return -1

def straight_flush(hand):
    if flush(hand) != -1:
        return straight(hand)
    return -1

def royal_straight_flush(hand):
    if straight_flush(hand) and hand[0][0] == 10:
        return 10
    return -1

ranks = [
    high,
    pair,
    two_pair,
    three_kind,
    straight,
    flush,
    full_house,
    four_kind,
    straight_flush,
    royal_straight_flush
]

def getRank(hand):
    for i in range(len(ranks)-1, -1, -1):
        r = ranks[i](hand)
        if r != -1:
            return i*10000 + r

def play(hand1, hand2):
    r1 = getRank(hand1)
    r2 = getRank(hand2)
    if r1 > r2:
        return 1
    if r2 > r1:
        return 2
    for i in range(len(hand1)-1, -1, -1):
        if hand1[i][0] > hand2[i][0]:
            return 1
        if hand2[i][0] > hand1[i][0]:
            return 2
    return 0

def parseHand(hand):
    hand = hand.strip().split()
    hand = [(int(card.replace('T', '10').replace('J', '11').replace('Q', '12').replace('K', '13').replace('A', '14')[:-1]), card[-1]) for card in hand]
    hand = sorted(hand, key = lambda x: x[0])
    return hand

hand1 = parseHand("5H 5C 6S 7S KD")
hand2 = parseHand("2C 3S 8S 8D TD")
assert play(hand1, hand2) == 2
hand1 = parseHand("5D 8C 9S JS AC")
hand2 = parseHand("2C 5C 7D 8S QH")
assert play(hand1, hand2) == 1
hand1 = parseHand("2D 9C AS AH AC")
hand2 = parseHand("3D 6D 7D TD QD")
assert play(hand1, hand2) == 2
hand1 = parseHand("4D 6S 9H QH QC")
hand2 = parseHand("3D 6D 7H QD QS")
assert play(hand1, hand2) == 1
hand1 = parseHand("2H 2D 4C 4D 4S")
hand2 = parseHand("3C 3D 3S 9S 9D")
assert play(hand1, hand2) == 1

f = open("poker.txt", "r")
data = f.read().strip().splitlines()
f.close()
p1_won = 0
for h in data:
    hand1 = parseHand(h[:len(h)//2])
    hand2 = parseHand(h[len(h)//2:])
    if play(hand1, hand2) == 1:
        p1_won += 1

print(p1_won)
