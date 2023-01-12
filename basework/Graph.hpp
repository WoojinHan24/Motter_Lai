#pragma once
#include <vector>
#include <set>
#include <cassert>
#include <random>
#include <algorithm>

using Count = int;
using Node = int;
using Edge = std::pair<Node, Node>;

/*
undirected, unweighted graph
*/

struct Graph
{
    Count num_nodes;
    std::vector<std::set<Node>> adjacency_list;
    std::vector<Edge> edge_list; // {small,big}

    Graph() {}
    Graph(const Count &t_num_nodes)
    {
        assert(t_num_nodes >= 0);
        num_nodes = t_num_nodes;
        adjacency_list.assign(num_nodes, std::set<Node>());
    }

    // Node operators
    void add_node();

    // Edge operators
    void add_edge(const Node& ,const Node&);
    void add_edge(const Edge&);
    void delete_edge(const Node& ,const Node&);
    void delete_edge(const Edge&);
    void delete_edge(const Count&); //edge list index delete
    
    bool has_edge(const Node&,const Node&) const;
    bool has_edge(const Edge&) const;

    std::vector<std::vector<bool>> get_adjacency_matrix() const;
    std::vector<Edge> get_edge_list() const;
};

void Graph::add_node()
{
    num_nodes++;
    adjacency_list.emplace_back(std::set<Node>());
}

void Graph::add_edge(const Node &t_node1, const Node &t_node2)
{
    if(t_node1==t_node2){
        exit(1);
    }
    assert(t_node1 >= 0);
    assert(t_node2 >= 0);

    Node node1 =std::min(t_node1);
    Node node2 =std::max(t_node2);

    adjacency_list[node1].emplace(node2);
    adjacency_list[node2].emplace(node1);
    edge_list.emplace_back({node1,node2});
}

void Graph::add_edge(const Edge &t_edge)
{
    add_edge(t_edge.first, t_edge.second);
}

void Graph::delete_edge(const Node &t_node1, const Node &t_node2)
{
    assert(t_node1 >= 0);
    assert(t_node2 >= 0);

    Node node1 =std::min(t_node1);
    Node node2 =std::max(t_node2);

    if(has_edge(node1,node2)==false){
        return;
    }

    adjacency_list[t_node1].erase(t_node2);
    adjacency_list[t_node2].erase(t_node1);
    edge_list.erase(remove(edge_list.begin(),edge_list.end(),(Edge){node1,node2}),edge_list.end());

}

void Graph::delete_edge(const Edge &t_edge)
{
    delete_edge(t_edge.first,t_edge.second);
}

void Graph::delete_edge(const Count &index)
{
    Edge deleting_edge=edge_list[index];
    adjacency_list[deleting_edge.first].erase(deleting_edge.second);
    adjacency_list[deleting_edge.second].erase(deleting_edge.first);
    edge_list[index]=edge_list[edge_list.size()-1];
    edge_list.pop_back();
}

bool Graph::has_edge(const Node &t_node1, const Node &t_node2) const
{
    // t_node1 == t_node2 true
    if(t_node1==t_node2){
        return true;
    }
    assert(t_node1 >= 0);
    assert(t_node2 >= 0);

    if(adjacency_list[t_node1].size()>adjacency_list[t_node2].size()){
        return (adjacency_list[t_node2].find(t_node1)!=adjacency_list[t_node2].end());
    } else {
        return (adjacency_list[t_node1].find(t_node2)!=adjacency_list[t_node1].end());
    }
}

bool Graph::has_edge(const Edge &t_edge) const
{
    return has_edge(t_edge.first,t_edge.second);
}

std::vector<std::vector<bool>> Graph::get_adjacency_matrix() const
{
    std::vector<std::vector<bool>> adjacency_matrix(num_nodes, std::vector<bool>(num_nodes,0));
    for(Node node1=0;node1<num_nodes;node1++){
        for(Node link : adjacency_list[node1]){
            adjacency_matrix[node1][link]=1;
        }
    }
    return adjacency_matrix;
}
