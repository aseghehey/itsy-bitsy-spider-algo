fin = open('/Users/emanuelaseghehey/Development/Itsy-Bitsy-Spider-algo/textfiles/tiny-maze.txt','r')
content = fin.readlines()

nrc = (content[0].replace('\n','')).split()
n, r, c = int(nrc[0]), int(nrc[1]), int(nrc[-1])
start = content[1].replace('\n','').split()
end = content[2].replace('\n','').split()

graph = {i + 1: [] for i in range(n)}
level = 0

for i in range(3, len(content), 3):
    level += 1

    for j in range(i, i + 3):
        cur = content[i].replace('\n', '').split()
        graph[level].append(cur)

# find directions
# t = graph[1][0][0]
def getDirections(lvl):
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

wholegraph = []
wholegraph.append(getDirections(1))
wholegraph.append(getDirections(2))
wholegraph.append(getDirections(3))
