#pragma once
#include <vector>
#include <set>
#include <queue>
#include <cassert>
#include <random>
#include <algorithm>

using Count = int;
using Node = int;
using Edge = std::pair<Node, Node>;

/*
undirected, unweighted, unlooped graph
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
    void add_edge(const Node &, const Node &);
    void add_edge(const Edge &);
    void delete_edge(const Node &, const Node &);
    void delete_edge(const Edge &);
    void delete_edge(const Count &); // edge list index delete

    bool has_edge(const Node &, const Node &) const;
    bool has_edge(const Edge &) const;

    std::vector<std::vector<bool>> get_adjacency_matrix() const;
    std::vector<Edge> get_edge_list() const;
    std::vector<Count> get_degree_distribution() const;
    std::vector<double> get_betweenness_centrality() const;
    std::vector<Count> get_avalanche_size() const;
};

void Graph::add_node()
{
    num_nodes++;
    adjacency_list.emplace_back(std::set<Node>());
}

void Graph::add_edge(const Node &t_node1, const Node &t_node2)
{
    if (t_node1 == t_node2)
    {
        exit(1);
    }
    assert(t_node1 >= 0);
    assert(t_node2 >= 0);

    Node node1 = t_node1 < t_node2 ? t_node1 : t_node2;
    Node node2 = t_node1 < t_node2 ? t_node2 : t_node1;

    adjacency_list[node1].emplace(node2);
    adjacency_list[node2].emplace(node1);
    edge_list.emplace_back((Edge){node1, node2});
}

void Graph::add_edge(const Edge &t_edge)
{
    add_edge(t_edge.first, t_edge.second);
}

void Graph::delete_edge(const Node &t_node1, const Node &t_node2)
{
    assert(t_node1 >= 0);
    assert(t_node2 >= 0);

    Node node1 = t_node1 < t_node2 ? t_node1 : t_node2;
    Node node2 = t_node1 < t_node2 ? t_node2 : t_node1;

    if (has_edge(node1, node2) == false)
    {
        return;
    }

    adjacency_list[t_node1].erase(t_node2);
    adjacency_list[t_node2].erase(t_node1);
    edge_list.erase(remove(edge_list.begin(), edge_list.end(), (Edge){node1, node2}), edge_list.end());
}

void Graph::delete_edge(const Edge &t_edge)
{
    delete_edge(t_edge.first, t_edge.second);
}

void Graph::delete_edge(const Count &index)
{
    Edge deleting_edge = edge_list[index];
    adjacency_list[deleting_edge.first].erase(deleting_edge.second);
    adjacency_list[deleting_edge.second].erase(deleting_edge.first);
    edge_list[index] = edge_list[edge_list.size() - 1];
    edge_list.pop_back();
}

bool Graph::has_edge(const Node &t_node1, const Node &t_node2) const
{
    // t_node1 == t_node2 true
    if (t_node1 == t_node2)
    {
        return true;
    }
    assert(t_node1 >= 0);
    assert(t_node2 >= 0);

    if (adjacency_list[t_node1].size() > adjacency_list[t_node2].size())
    {
        return (adjacency_list[t_node2].find(t_node1) != adjacency_list[t_node2].end());
    }
    else
    {
        return (adjacency_list[t_node1].find(t_node2) != adjacency_list[t_node1].end());
    }
}

bool Graph::has_edge(const Edge &t_edge) const
{
    return has_edge(t_edge.first, t_edge.second);
}

std::vector<std::vector<bool>> Graph::get_adjacency_matrix() const
{
    std::vector<std::vector<bool>> adjacency_matrix(num_nodes, std::vector<bool>(num_nodes, 0));
    for (Node node1 = 0; node1 < num_nodes; node1++)
    {
        for (Node link : adjacency_list[node1])
        {
            adjacency_matrix[node1][link] = 1;
        }
    }
    return adjacency_matrix;
}

std::vector<Count> Graph::get_degree_distribution() const
{
    std::vector<Count> degree_distribution(num_nodes);
    for (Node index = 0; index < num_nodes; index++)
    {
        degree_distribution[index] = adjacency_list[index].size();
    }
    return degree_distribution;
}
std::vector<double> Graph::get_betweenness_centrality() const
{
    std::vector<double> betweenness_centrality(num_nodes);
    for (Node root = 0; root < num_nodes; root++)
    {
        // Set up a precdecessor matrix

        // distance vector must be sorted by its distance, and index to be memorized
        std::vector<std::pair<Node, Node>> distance(num_nodes, {0, 0});
        for (Node i = 0; i < num_nodes; i++)
        {
            distance[i].second = i;
        }

        std::vector<std::vector<Node>> precdecessor(num_nodes);
        std::queue<std::pair<Node, std::pair<Node, Node>>> precdecessor_setup_queue;
        precdecessor_setup_queue.push({root, {root, 0}});
        std::pair<Node, std::pair<Node, Node>> cursor;
        Node cursor_index;
        Node cursor_precdecessor;
        Node cursor_distance;

        while (precdecessor_setup_queue.size() != 0)
        {
            cursor = precdecessor_setup_queue.front();
            precdecessor_setup_queue.pop();
            cursor_index = cursor.first;
            cursor_precdecessor = cursor.second.first;
            cursor_distance = cursor.second.second;
            if (distance[cursor_index].first != 0)
            {
                if (distance[cursor_index].first < cursor_distance)
                {
                    continue;
                }
                if (distance[cursor_index].first > cursor_distance)
                {
                    precdecessor[cursor_index].clear();
                }
            }
            precdecessor[cursor_index].push_back(cursor_precdecessor);
            distance[cursor_index].first = cursor_distance;
            for (int next_node : adjacency_list[cursor_index])
            {
                if (next_node == cursor_precdecessor)
                {
                    continue;
                }
                precdecessor_setup_queue.push({next_node, {cursor_index, cursor_distance + 1}});
            }
        }

        // Sending a packet from farthest node from root
        std::vector<double> temperory_betweenness(num_nodes, 1);
        std::sort(distance.begin(), distance.end());

        Node node_index;
        double temp;
        for (Node i = num_nodes - 1; i >= 0; i--)
        {
            node_index = distance[i].second;
            if (node_index == root)
            {
                temperory_betweenness[node_index] -= 1;
                continue;
            }
            temp = temperory_betweenness[node_index] / precdecessor[node_index].size();
            for (Node j : precdecessor[node_index])
            {
                temperory_betweenness[j] += temp;
            }
        }

        // Sum up to betweenness vector
        for (Node i = 0; i < num_nodes; i++)
        {
            betweenness_centrality[i] += temperory_betweenness[i];
        }
    }

    return betweenness_centrality;
}

std::vector<Count> Graph::get_avalanche_size() const
{
}