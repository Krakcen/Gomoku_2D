#!/usr/bin/env python3

from collections import OrderedDict
from random import randint
import copy
import math

SIZE = 19
IA_PION = 'B'
PLAYER_PION = 'R'

def find_player_pion(themap, first_x, first_y, x, y, xplus, yplus):
    i, j = x, y
    if (x + xplus >= 0 and x + xplus < SIZE and y + yplus >= 0 and y + yplus < SIZE and themap[y + yplus][x + xplus] == PLAYER_PION):
        i, j = find_player_pion(themap, first_x, first_y, x + xplus, y + yplus, xplus, yplus)
    if (i != first_x or j != first_y):
        get_players_pion.pos.append((i, j))
    return ((i, j))

def get_players_pion(themap, x, y):
    get_players_pion.pos = []
    get_players_pion.pos.append((x, y))
    find_player_pion(themap, x, y, x, y, -1, 0)
    find_player_pion(themap, x, y, x, y, -1, -1)
    find_player_pion(themap, x, y, x, y, 0, -1)
    find_player_pion(themap, x, y, x, y, 1, -1)
    find_player_pion(themap, x, y, x, y, 1, 0)
    find_player_pion(themap, x, y, x, y, 1, 1)
    find_player_pion(themap, x, y, x, y, 0, 1)
    find_player_pion(themap, x, y, x, y, -1, 1)
    return (list(set(get_players_pion.pos)))

def search_next_player_pion(themap, x, y, xplus, yplus, n_player_pion, step):
    if (x + xplus < 0 or x + xplus >= SIZE or y + yplus < 0 or y + yplus >= SIZE):
        if (n_player_pion == 3):
            if (x + xplus >= 0 and x + xplus < SIZE and y + yplus >= 0 and y + yplus < SIZE and themap[y + yplus][x + xplus] != IA_PION):
                search_player_pion.x_y = (x + xplus, y + yplus)
                return (1)
        return (0)
    if (themap[y + yplus][x + xplus] == PLAYER_PION):
        return (search_next_player_pion(themap, x + xplus, y + yplus, xplus, yplus, n_player_pion + 1, step))
    if (n_player_pion >= 4):
        search_player_pion.x_y = (x, y)
        return (2)
    elif (n_player_pion == 3):
        if (x + xplus >= 0 and x + xplus < SIZE and y + yplus >= 0 and y + yplus < SIZE and themap[y + yplus][x + xplus] != IA_PION):
            search_player_pion.x_y = (x + xplus, y + yplus)
            return (1)
    elif (n_player_pion == 2 and step != 2):
        newmap = copy.deepcopy(themap)
        if (x + xplus >= 0 and x + xplus < SIZE and y + yplus >= 0 and y + yplus < SIZE and themap[y + yplus][x + xplus] != IA_PION):
            newmap[y + yplus][x + xplus] = PLAYER_PION
            pos = get_players_pion(newmap, x + xplus, y + yplus)
            for p in pos:
                x2, y2 = p
                if (search_player_pion(newmap, x2, y2, 1, 2)):
                    search_player_pion.yee_x_y = (x + xplus, y + yplus)
                    return (1)
    return (0)

def go_to_the_back(themap, x, y, xplus, yplus):
    while (x + xplus >= 0 and x + xplus < SIZE and y + yplus >= 0 and y + yplus < SIZE and themap[y + yplus][x + xplus] == PLAYER_PION):
        x += xplus
        y += yplus
    return ((x, y))

def search_player_pion(themap, x, y, n_player_pion, step):
    nb_line = 0
    i, j = go_to_the_back(themap, x, y, -1, 0)
    nb_line += search_next_player_pion(themap, i, j, 1, 0, n_player_pion, step)
    i, j = go_to_the_back(themap, x, y, -1, -1)
    nb_line += search_next_player_pion(themap, i, j, 1, 1, n_player_pion, step)
    i, j = go_to_the_back(themap, x, y, 0, -1)
    nb_line += search_next_player_pion(themap, i, j, 0, 1, n_player_pion, step)
    i, j = go_to_the_back(themap, x, y, 1, -1)
    nb_line += search_next_player_pion(themap, i, j, -1, 1, n_player_pion, step)
    i, j = go_to_the_back(themap, x, y, 1, 0)
    nb_line += search_next_player_pion(themap, i, j, -1, 0, n_player_pion, step)
    i, j = go_to_the_back(themap, x, y, 1, 1)
    nb_line += search_next_player_pion(themap, i, j, -1, -1, n_player_pion, step)
    i, j = go_to_the_back(themap, x, y, 0, 1)
    nb_line += search_next_player_pion(themap, i, j, 0, -1, n_player_pion, step)
    i, j = go_to_the_back(themap, x, y, -1, 1)
    nb_line += search_next_player_pion(themap, i, j, 1, -1, n_player_pion, step)
    nb_line = int(math.ceil(nb_line / 2))
    if (nb_line >= 2):
        return (True)
    elif (nb_line == 1 and step != 2):
        return (True)
    return (False)

def check_three_aligned(themap):
    search_player_pion.yee_x_y = (-1, -1)
    search_player_pion.x_y = (-1, -1)
    for y in range(0, SIZE):
        for x in range(0, SIZE):
            if (themap[y][x] == PLAYER_PION):
                if (search_player_pion(themap, x, y, 1, 1)):
                    return (True)
    return (False)

def search_next(themap, x, y, xplus, yplus):
    if ((x + xplus, y + yplus) in search_exit_door.x_y_check):
        return (0)
    search_exit_door.x_y_check.append((x + xplus, y + yplus))
    if (x + xplus < 0 or x + xplus >= SIZE or y + yplus < 0 or y + yplus >= SIZE):
        return (0)
    elif (themap[y + yplus][x + xplus] == PLAYER_PION):
        search_exit_door.nb_ia_pions += 1
        return (search_exit_door(themap, x + xplus, y + yplus))
    elif (themap[y + yplus][x + xplus] == IA_PION):
        return (0)
    else:
        search_exit_door.exit_doors.append((x + xplus, y + yplus))
        return (1)

def search_exit_door(themap, x, y):
    n = 0
    n += search_next(themap, x, y, -1, 0)
    n += search_next(themap, x, y, 0, -1)
    n += search_next(themap, x, y, 1, 0)
    n += search_next(themap, x, y, 0, 1)
    return (n)
    
def exit_door(themap):
    antiobject_map = []
    dico = OrderedDict()
    for i in range(0, SIZE):
        antiobject_map.append([])
        for j in range(0, SIZE):
            antiobject_map[i].append(0)
    for y in range(0, SIZE):
        for x in range(0, SIZE):
            if (themap[y][x] == PLAYER_PION):
                search_exit_door.x_y_check = []
                search_exit_door.exit_doors = []
                search_exit_door.nb_ia_pions = 0
                n = search_exit_door(themap, x, y)
                n = (19 * 19 - n) * 100 + search_exit_door.nb_ia_pions
                if (n in dico) == False:
                    dico[n] = []
                dico[n] += search_exit_door.exit_doors
                for i, j in search_exit_door.exit_doors:
                    antiobject_map[j][i] += n
    return (antiobject_map, dico)

def check_valid(x, y):
    if (x < 0 or x >= SIZE or y < 0 or y >= SIZE):
        return (False)
    return (True)

def beginning(themap):
    pos = (-1, -1)
    n = 0
    for y in range(0, SIZE):
        for x in range(0, SIZE):
            if (themap[y][x] == PLAYER_PION):
                n += 1
                pos = (x, y)
    if (n != 1):
        return (-1, -1)
    all_pos = []
    x, y = pos
    i = 0
    xplus = -3
    yplus = -2
    while (i < 16):
        if i < 5:
            xplus += 1
        elif i < 9:
            yplus += 1
        elif i < 13:
            xplus -= 1
        else:
            yplus -= 1
        if (check_valid(x + xplus, y + yplus)):
            all_pos.append((x + xplus, y + yplus))
        i += 1
    rnd = randint(0, len(all_pos) - 1)
    return (all_pos[rnd])

def main(themap):
    x, y = beginning(themap)
    if (x != -1 and y != -1):
        print ("Put pion on : " + str(x) + ", " + str(y))
        return
    if (check_three_aligned(themap)):
        if (search_player_pion.yee_x_y != (-1, -1)):
            x, y = search_player_pion.yee_x_y
        else:
            x, y = search_player_pion.x_y
        print ("Put pion on : " + str(x) + ", " + str(y))
        return
    antiobject_map, dico = exit_door(themap)
    dico = OrderedDict(sorted(dico.items(), key=lambda t: t[0]))

    if (len(dico) == 0):
        x, y = randint(0, SIZE - 1), randint(0, SIZE - 1)
        print ("Put pion on : " + str(x) + ", " + str(y))
        return        
    for key, value in reversed(dico.items()):
        n = OrderedDict()
        for i, tup in enumerate(value):
            x, y = tup
            newmap = copy.deepcopy(themap)
            newmap[y][x] = IA_PION
            search_exit_door.x_y_check = []
            search_exit_door.exit_doors = []
            search_exit_door.nb_ia_pions = 0
            ret = search_exit_door(newmap, x, y)
            if (ret in n) == False:
                n[ret] = []
            n[ret].append(tup)
        n = OrderedDict(sorted(n.items(), key=lambda t: t[0]))
        for i, j in reversed(n.items()):
            rnd = randint(0, len(j) - 1)
            x, y = j[rnd]
            print ("Put pion on : " + str(x) + ", " + str(y))
            return

amap = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 'R', 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 'R', 'B', 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]
main(amap)
