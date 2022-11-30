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

'''
def bfs(graph, vertex):
    visited = set()
    queue = [vertex]
    visited.add(vertex)
    while queue:
        v = queue.pop(0)
        print(v)
        for edges in graph[v]:
            if edges not in visited:
                visited.add(edges)
                queue.append(edges)
'''

def helper(v, vSet, p, dir, q):
    if v not in vSet:
        vSet.add(v)
        p.append(dir)
        q.append((v, p))

def bfs(start, end):
    visited = set()
    queue = [(start, [])]
    visited.add(start)

    while queue:
        node, path = queue.pop(0)
        # print(path)
        if node == end:
            return path
        visit = None
        if node.north:
            # print('north')
            visit = node.north
            helper(visit, visited, path.copy(), 'N', queue)
        if node.south:
            # print('south')
            visit = node.south
            helper(visit, visited, path.copy(), 'S', queue)
        if node.west:
            # print('west')
            visit = node.west
            helper(visit, visited, path.copy(), 'W', queue)
        if node.east:
            # print('east')
            visit = node.east
            helper(visit, visited, path.copy(), 'E', queue)
        if node.up:
            # print('up')
            visit = node.up
            helper(visit, visited, path.copy(), 'U', queue)
        if node.down:
            # print('down')
            visit = node.down
            helper(visit, visited, path.copy(), 'D', queue)

if __name__ == "__main__":
    binaryGraph, levels = readGraph('/Users/emanuelaseghehey/Development/Itsy-Bitsy-Spider-algo/textfiles/tiny-maze.txt')
    # print(binaryGraph)
    graph = {i: [] for i in range(levels)}
    lvl = 0

    for k, v in binaryGraph.items():
        for i in range(len(v)):
            temp = []
            for j in range(len(v[i])):
                temp.append(Node())
            graph[lvl].append(temp)
        lvl += 1

    # print(direction(4, binaryGraph[1][0][0]))
    dir = {i: [] for i in range(levels)}
    lvl = 0
    for k, v in binaryGraph.items():
        for i in range(len(v)):
            temp = []
            for j in range(len(v[i])):
                temp.append(direction(v[i][j]))
            dir[lvl].append(temp)
        lvl += 1

    # print(dir)
    # print(binaryGraph)
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

    # print(graph)
    f_analysis = open('analysis', 'w')
    for k, v in dir.items():
        for vals in v:
            f_analysis.write('    '.join(vals) + '\n')
        f_analysis.write('\n')
    f_analysis.close()
    # print(dir[3][2][2])
    # print(graph.keys())
    f_out = open('output.txt', 'w')
    f_out.write(' '.join(bfs(graph[0][0][0], graph[2][2][2])))
    f_out.close()
    # print(bfs(graph[1][0][0], graph[1][1][0]))

    # print(graph[0][0][0])