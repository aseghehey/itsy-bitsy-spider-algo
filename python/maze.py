from collections import defaultdict
import readFromGraph

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

class Graph:
    def __init__(self, n) -> None:
        self.graph = {i + 1: [] for i in range(n)}
    
    def addNode(self, level, n, s, w, e, u, d):
        node = Node(n, s, w, e, u, d)
        self.graph[level].append(node)
    
    def printLevel(self, level):
        return self.graph[level]
    
if __name__ == "__main__":
    graph = Graph(3)
    t1 = Node()
    t2 = Node(t1)
    print(t2.north == t1)


        
