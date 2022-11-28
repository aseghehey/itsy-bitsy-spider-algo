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

    def directions(self, pointer):
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

    print(binaryGraph[1][0][0])
        
