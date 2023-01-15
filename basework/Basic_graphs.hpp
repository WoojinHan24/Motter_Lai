#pragma once
#include "Graph.hpp"
#include <vector>
#include <queue>


//fully connect generate
namespace Clique{
    Graph generate(const Count& num_nodes) const {
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
    Graph generate (const Count& num_nodes, const std::vector<std::vector<double>>& weight_matrix) const{
        Graph g(num_nodes);

        std::vector<int> initialize_visited(num_initial_nodes,0);
        std::priority_queue<std::pair<double,std::pair<int,int>>> edge_priority_queue; // {-spatial distance, {primary_node,next_node}}
        std::pair<int,int> edge_picked;
        int node_picked=0;
        initialize_visited[0]=1;

        for(int i=0;i<num_nodes;i++){
                if(initialize_visited[i]!=0||i==node_picked){
                    continue;
                }
                edge_priority_queue.push({-spatial_distance_matrix[node_picked][i],{node_picked,i}});
        }
        
        while(edge_priority_queue.size()){
            edge_picked=edge_priority_queue.top().second;
            edge_priority_queue.pop();

            node_picked=edge_picked.second;
            if(initialize_visited[node_picked]!=0){
                continue;
            }

            initialize_visited[node_picked]=1;
            g.add_edge(edge_picked.first,edge_picked.second);

            for(int i=0;i<num_nodes;i++){
                if(initialize_visited[i]!=0||i==node_picked){
                    continue;
                }
                edge_priority_queue.push({-spatial_distance_matrix[node_picked][i],{node_picked,i}});
            }
        }
        return g;
    }
}