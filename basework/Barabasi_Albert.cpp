#include "BA.hpp"
#include "Graph.hpp"
#include "CSV.hpp"
#include <iostream>

int main(int argc, char* argv[]){
    if(argc<2){
        std::cout << "Barabasi_Albert.cpp has two argumets, m,n\n";
        return -1;
    }
    Count num_new_edges=std::stol(argv[1]);
    Count num_nodes=std::stol(argv[2]);

    Graph g=BA::generate(num_new_edges,num_nodes);

    CSV::write(g.get_adjacency_matrix());

    return 0;
}