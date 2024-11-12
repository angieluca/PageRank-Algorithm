#include "adjList.h"

int main() {
    std::map<std::string, std::set<std::string>> adjMap; //Adjacency List
    std::map<std::string, float> tempRanks; //temporarily keep values during one iteration
    std::map<std::string, float> ranks; //official ranks
    float pageRank;
    int numLines, powerItr;
    std::cin >> numLines;
    std::cin >> powerItr;

    //Create adjacent List object and use class functions
    adjList graph;

    graph.createAdjList(numLines, adjMap);
    //graph.visualizeList(adjMap); //for debugging purposes

    //Default page rank of each is 1/(number of websites); remains when power iterator is 1
    pageRank = (float)1/adjMap.size();
    //Everything first has default ranks
    ranks = graph.createDefRanks(adjMap, pageRank);
    //Calculate new ranks if powerItr > 1
    if (powerItr > 1) graph.calculateRanks(adjMap, ranks, tempRanks, powerItr);

    std::string output = graph.printRanks(ranks); //Print each website and their ranks

}

