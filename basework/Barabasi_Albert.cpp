#include "BA.hpp"
#include "Graph.hpp"
#include "CSV.hpp"
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]){
    if(argc<2){
        std::cout << "Barabasi_Albert.cpp has two argumets, m,n\n";
        return -1;
    }
    Count num_new_edges=std::stol(argv[1]);
    Count num_nodes=std::stol(argv[2]);

    std::string folder_name=BA::get_folder_name(num_new_edges,num_nodes);
    std::filesystem::create_directories(folder_name);
    
    Graph g = BA::generate(num_new_edges,num_nodes);

    std::ofstream output_file;
    output_file.open(folder_name+ "/Adjacency_List(N" + std::to_string(num_nodes) + ").txt");
    CSV::write(g.adjacency_list,output_file);

    std::ofstream output_file2;
    output_file2.open(folder_name+"/Edge_List(N" + std::to_string(num_nodes) + ").txt");
    CSV::write(g.edge_list,output_file2);

    std::ofstream output_file3;
    output_file3.open(folder_name+"/Betweenness_Centrality(N" + std::to_string(num_nodes) + ").txt");
    CSV::write(g.get_betweenness_centrality(),output_file3);


    return 0;
}