#pragma once
#include "Graph.hpp"
#include "CSV.hpp"
#include "Basic_graphs.hpp"
#include "pcg_extras.hpp"
#include "pcg_random.hpp"
#include "point.hpp"
#include <vector>
#include <random>
#include <fstream>
#include <set>

// Barabasi Albert method graph generation
namespace SHK
{
    Point get_point(pcg64 &random_engine)
    {
        std::uniform_real_distribution<double> probability_distribution(0, 1);
        Point return_point = (probability_distribution(random_engine), probability_distribution(random_engine));
        return return_point;
    }

    double spatial_distance(const Point &point1, const Point &point2) const
    {
        return std::sqrt((point1.x - point2.x) ^ 2 + (point1.y - point2.y) ^ 2);
    }

    Graph generate(
        const Count &num_nodes, const Count &num_initial_nodes, const double &probability_new_redundancy, const double &probability_existing_redundancy, const double &exponent_trade_off, const double &probability_splitting, const int spatial_density_function_parameter, int spatial_distance_parameter)
    {
        std::vector<Point> position_list(num_nodes);
        std::vector<std::vector<double>> spatial_distance_matrix(num_nodes,std::vector<double>(num_nodes));
        std::random_device rd;
        pcg64 random_engine(rd());
        std::uniform_real_distribution<double> probability_distribution(0, 1);

        for (int i = 0; i < num_initial_nodes; i++)
        {
            double distance;
            position_list[i]=get_point(random_engine);
            for(int j=0;j<num_initial_nodes;j++){
                distance=spatial_distance(position_list[i],position_list[j]);
                spatial_distance_matrix[i][j]=distance;
                spatial_distance_matrix[j][i]=distance;
            }
        }
        Graph shk=MST::generate(num_initial_nodes,spatial_distance_matrix);
        


    }

    std::string get_folder_name(
        const Count &num_new_edges, const Count &num_nodes)
    {

        return "./results/SHK/type(" + std::to_string(num_new_edges) + ")/";
    }
}