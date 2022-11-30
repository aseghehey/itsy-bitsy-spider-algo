def readGraph(path):
    fin = open(path,'r')
    content = fin.readlines()
    fin.close()
    nrc = (content[0].replace('\n','')).split()
    n, r, c = int(nrc[0]), int(nrc[1]), int(nrc[-1])

    start = content[1].replace('\n','').split()
    end = content[2].replace('\n','').split()

    graph = {i: [] for i in range(n)}
    level = 0

    for i in range(3, len(content), r):
        for j in range(i, i + c):
            cur = content[j].replace('\n', '').split()
            graph[level].append(cur)
        level += 1
    # print(graph)
    return graph, n

def getDirections(lvl, graph):
    g = []
    directions = {0: 'N', 1:'E', 2:'S', 3:'W', 4:'U', 5:'D'}
    for i in range(len(graph[lvl])):
        for j in range(len(graph[lvl][i])):
            cur = graph[lvl][i][j]
            t = []
            for num, bit in enumerate(cur):
                if int(bit) == 1:
                    t.append(directions[num])
            g.append(t)
    return g

testing_logic, n = readGraph('/Users/emanuelaseghehey/Development/Itsy-Bitsy-Spider-algo/textfiles/tiny-maze.txt')


# for k, v in testing_logic.items():
#     print(f'{k}\n{v}')

# print(getDirections(2, readGraph('/Users/emanuelaseghehey/Development/Itsy-Bitsy-Spider-algo/textfiles/tiny-maze.txt')))