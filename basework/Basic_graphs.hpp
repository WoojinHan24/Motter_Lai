#pragma once
#include "Graph.hpp"

//fully connect generate
namespace Clique{
    Graph generate(const Count& num_nodes){
        Graph g(num_nodes);
        for(int node1=0;node1<num_nodes;node1++){
            for(int node2=0;node2<node1;node2++){
                g.add_edge(node1,node2);
            }
        }
        return g;
    }
}

//minimal spanning tree
namespace MST{
    
}