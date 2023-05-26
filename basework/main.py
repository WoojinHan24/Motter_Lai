import graph as gph

def distance(i,j):
    return (i-j)**2

g = gph.Graph(10, MST = distance)
print(g.betweenness_centrality())
g.print("./temp.txt")