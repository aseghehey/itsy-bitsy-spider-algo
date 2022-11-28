from collections import defaultdict
from readFromGraph import *

class Node:
    def __init__(self, n=None, s=None, w=None, e=None, u=None, d=None) -> None:
        self.north = n
        self.south = s
        self.west = w
        self.east = e
        self.up = u
        self.down = d

    def NodeDirections(self, pointer):
        direction = {self.north: 'N', self.south: 'S', self.west: 'W', self.east: 'E', self.up: 'U', self.down: 'D'}
        return direction[pointer] if pointer else None

'''
class Graph:
    def __init__(self, n) -> None:
        self.graph = {i + 1: [] for i in range(n)}
    
    def addNode(self, level, n, s, w, e, u, d):
        node = Node(n, s, w, e, u, d)
        self.graph[level].append(node)
    
    def printLevel(self, level):
        return self.graph[level]
'''   

def direction(bits):
    directions = {0: 'N', 1:'E', 2:'S', 3:'W', 4:'U', 5:'D'}
    res = ''
    for num, b in enumerate(bits):
        if int(b):
            res += directions[num]
    return res

if __name__ == "__main__":
    binaryGraph, levels = readGraph('/Users/emanuelaseghehey/Development/Itsy-Bitsy-Spider-algo/textfiles/tiny-maze.txt')
    # print(binaryGraph)
    graph = {i + 1: [] for i in range(levels)}
    lvl = 0

    for k, v in binaryGraph.items():
        lvl += 1
        for i in range(len(v)):
            temp = []
            for j in range(len(v[i])):
                temp.append(Node())
            graph[lvl].append(temp)

    # print(direction(4, binaryGraph[1][0][0]))
    dir = {i + 1: [] for i in range(levels)}
    lvl = 0
    for k, v in binaryGraph.items():
        lvl += 1
        for i in range(len(v)):
            temp = []
            for j in range(len(v[i])):
                temp.append(direction(v[i][j]))
            dir[lvl].append(temp)
    # print(dir)

    for lvl, vals in dir.items():
        for i in range(len(vals)):
            for j in range(len(vals[i])):
                for w in vals[i][j]:
                    if w == 'N':
                        graph[lvl][i][j].north = graph[lvl][i-1][j]
                    elif w == 'S':
                        graph[lvl][i][j].south = graph[lvl][i + 1][j]
                    elif w == 'W':
                        graph[lvl][i][j].west = graph[lvl][i][j-1]
                    elif w == 'E':
                        graph[lvl][i][j].east = graph[lvl][i][j+1]
                    elif w == 'U':
                        graph[lvl][i][j].up = graph[lvl + 1][i][j]
                    else:
                        graph[lvl][i][j].down = graph[lvl - 1][i][j]

    print(graph, '\n')
    print(dir, '\n')
    print(graph[1][0][0].up == graph[2][0][0])
    print(graph[1][0][1].east == graph[1][0][2])


