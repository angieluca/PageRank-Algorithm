#include "adjList.h"

void adjList::createAdjList(int &numLines, std::map<std::string, std::set<std::string>> &adjMap){
    std::string fromPage, toPage;
    //Get user input of website
    for (int i = 0; i < numLines; i++) {
        std::cin >> fromPage;
        if (adjMap.find(fromPage) == adjMap.end()){
            adjMap[fromPage] = std::set<std::string>(); //Insert "from" website with empty vector
        }
        std::cin >> toPage;
        if (adjMap.find(toPage) == adjMap.end()) {
            adjMap[toPage] = std::set<std::string>(); //Insert "to" website with empty vector
        }
        if (adjMap[fromPage].count(toPage) == 0){ //Check if website already in set
            adjMap[fromPage].emplace(toPage);
        }
    }
}

void adjList::visualizeList(const std::map<std::string, std::set<std::string>> &adjMap){
    //Visualization of adjacency list:
    for (auto const &element: adjMap){
        std::cout << element.first << " -> ";
        for (auto const &thing: element.second){
            std::cout << thing << " ";
        }
        std::cout << "\n";
    }
}

std::map<std::string, float> adjList::createDefRanks(std::map<std::string,std::set<std::string>> &adjMap, float &pageRank){
    //Make each website's rank default page rank
    std::map<std::string, float> ranks;
    for (const auto &website: adjMap){
        ranks[website.first] = pageRank; //website.first means website name
    }
    return ranks;
}

void adjList::calculateRanks(std::map<std::string, std::set<std::string>> &adjMap, std::map<std::string, float> &ranks, std::map<std::string, float> &tempRanks, int &powerItr){
    //Calculate ranks
    float tempRank;
    int iterations = 1;
    while (iterations < powerItr){
        //Go through each unique website, but we're actually calculating ranks of their out websites
        for (const auto &website: adjMap){
            int outdegree = website.second.size();
            //Iterate through each indegree website and change their page rank
            for (const auto &outWebs: website.second){
                //Rank of "to" site will be ("from" site rank divided by "from" site's out degree)
                float fromRank = ranks[website.first]; //rank of from site
                tempRank = fromRank/outdegree;
                tempRanks[outWebs] += tempRank;
            }
        }
        for (const auto &website: adjMap){
            ranks[website.first] = tempRanks[website.first];
            tempRanks[website.first] = 0; //reset temp ranks
        }
        iterations++;
    }
}

std::string adjList::printRanks(std::map<std::string, float> &ranks){
    std::string output;
    //Print out each website and rank
    for (const auto &website: ranks){
        std::cout << website.first << " " << std::fixed << std::setprecision(2) << website.second << std::endl;
        std::ostringstream outputss;
        outputss << std::fixed << std::setprecision(2) << website.second;
        output += website.first + " " + outputss.str() + "\n";
    }
    return output;
}
