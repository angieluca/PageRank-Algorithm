#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include "AdjacencyList.h"

int main() {
    int numLines, powerItr;
    std::string fromPage, toPage;
    std::cin >> numLines;
    std::cin >> powerItr;
    //adjacency matrix is key:string, value: vector of {string,int} pairs
    std::map<std::string, std::vector<std::pair<std::string, int>>> adjMatrix;

    //Get user input of graph and store in map for adjacency matrix
    //Fill each element with zero
    for (int i = 0; i < numLines; i++) {
        std::cin >> fromPage;
        std::cin >> toPage;
        adjMatrix[fromPage].emplace_back(std::make_pair(toPage,0));
        adjMatrix[toPage].emplace_back(std::make_pair(fromPage,0));
        adjMatrix[fromPage].emplace_back(std::make_pair(fromPage,0));
        adjMatrix[toPage].emplace_back(std::make_pair(toPage,0));
    }

    //Output adjacency matrix as a 2D array
    //Output the Column Titles
    for (auto element: adjMatrix){
        std::cout << "\t" << element.first << " ";
    }
    std::cout << "\n";
    //Output the actual data
    for (auto element : adjMatrix){
        std::cout << element.first << " ";
        for (auto things: element.second){
            std::cout << things.second << " ";
        }
        std::cout << "\n";
    }
    //Create a graph object
    // Created_Graph.PageRank(power_iterations);}
}

