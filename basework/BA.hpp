#pragma once
#include "Graph.hpp"
#include "CSV.hpp"
#include "Basic_graphs.hpp"
#include "pcg_extras.hpp"
#include "pcg_random.hpp"
#include <vector>
#include <random>
#include <fstream>
#include <set>

// Barabasi Albert method graph generation
namespace BA
{
    Node get_random_node(const Graph &g, pcg64 &random_engine)
    {
        // get random edge and select randomly
        std::uniform_real_distribution<double> probability_distribution(0, 1);
        Count random_edge_index = (Count)(probability_distribution(random_engine) * g.edge_list.size());
        if (probability_distribution(random_engine) > 0.5)
        {
            return g.edge_list[random_edge_index].first;
        }
        else
        {
            return g.edge_list[random_edge_index].second;
        }
    }

    Graph generate(const Count &num_new_edges, const Count &num_nodes)
    {
        // fully connected until num_new_edges+1
        std::random_device rd;
        pcg64 random_engine(rd());
        const Count fully_connected = std::min(num_new_edges + 1, num_nodes);
        Graph barabasi = Clique::generate(fully_connected);

        Node random_node;
        for (Count time = fully_connected; time < num_nodes; time++)
        {
            barabasi.add_node();
            for (Count i = 0; i < num_new_edges; i++)
            {
                while (true)
                {
                    random_node = BA::get_random_node(barabasi, random_engine);
                    if (barabasi.has_edge(time, random_node) == 0)
                    {
                        break;
                    }
                }
                barabasi.add_edge(time, random_node);
            }
        }
        return barabasi;
    }

    std::string get_folder_name(
        const Count &num_new_edges, const Count &num_nodes)
    {
        return "./results/BA/m("+std::to_string(num_new_edges)+")/";
    }
}