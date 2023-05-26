import numpy as np

class Graph:
    maxsize = 100000000000000000

    def __init__(self, num_node, adjacency_matrix=None, clique = False, MST = None):
        #initial setting of the graph can be clique or MST
        #Set up clique = True : adjacency_matrix input never counts
        #Set up MST = distance function between two node

        self.num_node = num_node
        if adjacency_matrix is not None:
            self.adjacency_matrix = adjacency_matrix
        elif clique is True:
            self.adjacency_matrix = np.ones(shape=(num_node,num_node),dtype = np.float64) - np.identity(num_node)
        else:
            self.adjacency_matrix = np.zeros(shape = (num_node,num_node), dtype = np.float64)

            if MST is not None:
                self.initialize_mst(distance = MST)
    

    def add_node(self, linkage_index = []):
        #linkage_index : is the index list of the initial linkage
        added_row = [0 for node in range(self.num_node)]
        self.adjacency_matrix = np.r_[self.adjacency_matrix, [added_row]]

        self.num_node += 1
        added_row.append(0)
        self.adjacency_matrix = np.c_[self.adjacency_matrix, added_row]

        for node in linkage_index:
            self.add_edge(self.num_node-1,node)
    
    def add_edge(self, node1, node2):
        if self.is_linked(node1, node2) == True:
            raise ValueError("linkage is already exsist",node1, node2)

        self.adjacency_matrix[node1][node2]=1
        self.adjacency_matrix[node2][node1]=1

    def is_linked(self, node1, node2):
        if self.adjacency_matrix[node1][node2] != 0:
            if self.adjacency_matrix[node2][node1] != 0:
                return True
            else:
                raise ValueError("Symmetry problem exist",node1, node2)
        elif self.adjacency_marix[node2][node1] == 0:
            return False
        else:
            raise ValueError("Symmetry problem exist",node1, node2)
        
    def delete_edge(self, node1, node2):
        if self.is_linked(node1, node2) == False:
            raise ValueError("linkage is already deleted",node1, node2)
        
        self.adjacency_matrix[node1][node2] = 0
        self.adjacency_matrix[node2][node1] = 0
    

    def initialize_mst(self, distance):
        if self.num_node < 2:
            raise ValueError("Minimum number of nodes required for MST initialization is 2")

        key = [self.maxsize] * self.num_node
        parent = [None] * self.num_node
        mst_set = [False] * self.num_node

        key[0] = 0  # Start with the first node

        for _ in range(self.num_node):
            u = self.get_min_key(key, mst_set)
            mst_set[u] = True

            for v in range(self.num_node):
                if (
                    self.adjacency_matrix[u][v] == 0
                    and not mst_set[v]
                    and distance(u, v) < key[v]
                ):
                    key[v] = distance(u, v)
                    parent[v] = u

        self.adjacency_matrix = np.zeros((self.num_node, self.num_node), dtype=np.float64)

        for v in range(1, self.num_node):
            self.adjacency_matrix[parent[v]][v] = 1
            self.adjacency_matrix[v][parent[v]] = 1

    def get_min_key(self, key, mst_set):
        min_key = self.maxsize
        min_index = None

        for v in range(self.num_node):
            if key[v] < min_key and not mst_set[v]:
                min_key = key[v]
                min_index = v

        return min_index
    
    def print(self, file_export = None):
        
        adjacency_matrix_string=''
        for i in range(self.num_node):
            for j in range(self.num_node):
                adjacency_matrix_string += f'{self.adjacency_matrix[i][j]}  '
            adjacency_matrix_string += '\n'

        if file_export is not None:
            with open(file_export, 'w') as f:
                f.write(adjacency_matrix_string)
                f.close()
            return

        print("adjacency matrix of num_node ", self.num_node)
        print(adjacency_matrix_string)

    def partition_function(self, temperature, diameter = None):
        if diameter is None:
            diameter = self.num_node
        
        z = np.exp(-1/temperature)
        A = self.adjacency_matrix
        return np.linalg.inv(np.identity(self.num_node)-z*A)
    
    def soft_betweenness_centrality(self, temperature, diameter = None):
        Z = self.partition_function(self,temperature, diameter)
        Z_1 = np.reciprocal(Z)
        return np.diag(np.matmul(np.matmul(Z,Z_1),Z))
    
    def betweenness_centrality(self):
        betweenness = np.zeros(self.num_node)

        for s in range(self.num_node):
            stack = []
            pred = [[] for _ in range(self.num_node)]
            sigma = np.zeros(self.num_node)
            sigma[s] = 1
            dist = np.full(self.num_node, -1)
            dist[s] = 0

            queue = [s]
            while queue:
                v = queue.pop(0)
                stack.append(v)
                for w in range(self.num_node):
                    if self.adjacency_matrix[v][w] == 1:
                        if dist[w] < 0:
                            queue.append(w)
                            dist[w] = dist[v] + 1
                        if dist[w] == dist[v] + 1:
                            sigma[w] += sigma[v]
                            pred[w].append(v)

            delta = np.zeros(self.num_node)
            while stack:
                w = stack.pop()
                for v in pred[w]:
                    delta[v] += (sigma[v] / sigma[w]) * (1 + delta[w])
                    if v != s:
                        betweenness[v] += delta[v]

        return betweenness


            




