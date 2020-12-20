import itertools
debug = False

def flip(block, idx):
    width = len(block[0])
    height = len(block)
    b = [[block[y][x] for x in range(width)] for y in range(height)]
    if idx == 1:
        for y in range(height):
            for x in range(width):
                b[height-1-y][x] = block[y][x]
    elif idx == 2:
        for y in range(height):
            for x in range(width):
                b[y][width-1-x] = block[y][x]
    return b

def rotate(block):
    width = len(block[0])
    height = len(block)
    b = [[block[y][x] for x in range(width)] for y in range(height)]

    for y in range(height):
        for x in range(width):
            b[x][width-1-y] = block[y][x]
    return b

def fits(b1, b2):
    width = len(b1[0])
    height = len(b1)
    if debug:
        input()
        print(*b1, sep='\n')
        print()
        print(*b2, sep='\n')
    for x in range(width):
        if b1[0][x] != b2[height-1][x]:
            break
    else:
        return 3 # top
    for x in range(width):
        if b1[height-1][x] != b2[0][x]:
            break
    else:
        return 1 # bottom
    for y in range(height):
        if b1[y][0] != b2[y][width-1]:
            break
    else:
        return 2 # left
    for y in range(height):
        if b1[y][width-1] != b2[y][0]:
            break
    else:
        return 4 # right
    return 0

def follow_edge(connections, edge_blocks, corner_blocks, current):
    for b in connections[current]:
        if b in corner_blocks:
            connections[current].remove(b)
            connections[b].remove(current)
            return [current, b]
        elif b in edge_blocks:
            connections[current].remove(b)
            connections[b].remove(current)
            return [current] + follow_edge(connections, edge_blocks, corner_blocks, b)
    
def find_edges(connections, corner_blocks, edge_blocks):
    edges = []
    cb = list(corner_blocks)
    i = cb[0]
    for _ in range(len(corner_blocks)):
        edge_block = connections[i][0]
        connections[i].remove(edge_block)
        connections[edge_block].remove(i)
        edges.append([i] + follow_edge(connections, edge_blocks, corner_blocks, edge_block))
        i = edges[-1][-1]
    return edges

def add_edges(image, edges):
    width = len(image[0])
    height = len(image)
    # top
    for x in range(width):
        image[0][x] = edges[0][x]
    # right
    for y in range(height):
        image[y][width-1] = edges[1][y]

    # bottom
    for x in range(width):
        image[height-1][x] = edges[2][width-1-x]

    # left
    for y in range(height):
        image[y][0] = edges[3][height-1-y]

def fill_image(image, connections):
    width = len(image[0])
    height = len(image)
    for y in range(1, height-1):
        for x in range(1, width-1):
            b = list(set(connections[image[y-1][x]]).intersection(connections[image[y][x-1]]))[0]
            image[y][x] = b
            connections[image[y-1][x]].remove(b)
            connections[image[y][x-1]].remove(b)
            connections[b].remove(image[y-1][x])
            connections[b].remove(image[y][x-1])

def fit_pair(blocks, left, right, edge = 4):
    p1 = blocks[left]
    p2 = blocks[right]
    border = None
    for f in [0, 1, 2, 1]:
        p2 = flip(p2, f)
        for _ in range(4):
            p2 = rotate(p2)
            border = fits(p1, p2)
            if border != 0:
                break
        if border != 0:
            break

    for _ in range((edge-border)%4):
        p1 = rotate(p1)
        p2 = rotate(p2)

    assert fits(p1, p2) == edge
    blocks[left] = p1
    blocks[right] = p2


def fit_blocks(blocks, image):
    width = len(image[0])
    height = len(image)
    for y in range(height):
        for x in range(width-1):
            fit_pair(blocks, image[y][x], image[y][x+1])
    for y in range(1, height):
        if fits(blocks[image[y-1][0]], blocks[image[y][0]]) != 1:
            for x in range(width):
                blocks[image[y][x]] = flip(blocks[image[y][x]], 1)

def find_monster(image, monster, y, x):
    m_width = len(monster[0])
    m_height = len(monster)
    for y2 in range(m_height):
        for x2 in range(m_width):
            if monster[y2][x2] == '#' and image[y+y2][x+x2] != '#':
                return False
    return True

def set_monster(image, monster, y, x):
    m_width = len(monster[0])
    m_height = len(monster)
    for y2 in range(m_height):
        for x2 in range(m_width):
            if monster[y2][x2] == '#':
                image[y+y2][x+x2] = 'O'


def find_monsters(image, monster):
    i_width = len(image[0])
    i_height = len(image)
    m_width = len(monster[0])
    m_height = len(monster)

    monsters = 0
    y = 0
    x = 0
    for y in range(i_height-m_height):
        for x in range(i_width-m_width):
            if find_monster(image, monster, y, x):
                set_monster(image, monster, y, x)
                monsters += 1
    return monsters


f = open("20.in", "r")
data = [x.splitlines() for x in f.read().strip().split('\n\n')]
f.close()

blocks = {}
for b in data:
    num = int(b[0][5:-1])
    block = [list(x) for x in b[1:]]
    blocks[num] = block

corner_blocks = set()
edge_blocks = set()
middle_blocks = set()
connections = {}
for k1 in blocks.keys():
    p1 = blocks[k1]
    fitting = set()
    for k2 in blocks.keys():
        if k1 != k2:
            p2 = blocks[k2]
            for f in [0, 1, 2, 1]:
                p2 = flip(p2, f)
                for r in [1, 1, 1, 1]:
                    p2 = rotate(p2)
                    if fits(p1, p2) != 0:
                        fitting.add(k2)
                        break
    if len(fitting) == 2:
        corner_blocks.add(k1)
    elif len(fitting) == 3:
        edge_blocks.add(k1)
    elif len(fitting) == 4:
        middle_blocks.add(k1)
    else:
        print("Error, fitting = " + str(len(fitting)))
        exit()
    connections[k1] = list(fitting)
p = 1
for c in corner_blocks:
    p*=c
print(p)

edges = find_edges(connections, corner_blocks, edge_blocks)
image = [[0 for x in edges[0]] for y in edges[1]]
add_edges(image, edges)
fill_image(image, connections)
fit_blocks(blocks, image)

for b in blocks:
    block = blocks[b][1:-1]
    for y in range(len(block)):
        block[y] = block[y][1:-1]
    blocks[b] = block

monster = """                  # 
#    ##    ##    ###
 #  #  #  #  #  #   """
monster = [list(x) for x in monster.splitlines()]
width = len(image[0])*8
height = len(image)*8
full_img = [['.' for x in range(width)] for y in range(height)]

for y in range(height):
    for x in range(width):
        full_img[y][x] = blocks[image[y//8][x//8]][y%8][x%8]

m = 0
for a in [1, 1, 1, 1, 2, 1, 1, 1]:
    if a == 1:
        full_img = rotate(full_img)
    else:
        full_img = flip(full_img, 1)
    m = find_monsters(full_img, monster)
    if m != 0:
        print(m)
        break

print(m)
s = 0
for row in full_img:
    s+=row.count('#')
    print(''.join(row))
print(s)
