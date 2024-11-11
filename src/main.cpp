#include <iostream>
#include <map>
#include <set>
#include <iomanip>

void createAdjList(int &numLines, std::map<std::string, std::set<std::string>> &adjMap){
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

void visualizeList(const std::map<std::string, std::set<std::string>> &adjMap){
    //Visualization of adjacency list:
    for (auto const &element: adjMap){
        std::cout << element.first << " -> ";
        for (auto const &thing: element.second){
            std::cout << thing << " ";
        }
        std::cout << "\n";
    }
}

std::map<std::string, float> createDefRanks(std::map<std::string,std::set<std::string>> &adjMap, float &pageRank){
    //Make each website's rank default page rank
    std::map<std::string, float> ranks;
    for (const auto &website: adjMap){
        ranks[website.first] = pageRank; //website.first means website name
    }
    return ranks;
}

void calculateRanks(std::map<std::string, std::set<std::string>> &adjMap, std::map<std::string, float> &ranks, std::map<std::string, float> &tempRanks, int &powerItr){
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

std::string printRanks(std::map<std::string, float> &ranks){
    std::string output;
    //Print out each website and rank
    for (const auto &website: ranks){
        std::cout << website.first << " " << std::fixed << std::setprecision(2) << website.second << std::endl;
        output += website.first + " " + std::to_string(website.second) + "\n";
    }
    return output;
}

int main() {
    std::map<std::string, std::set<std::string>> adjMap; //Adjacency List
    std::map<std::string, float> tempRanks; //temporarily keep values during one iteration
    std::map<std::string, float> ranks; //official ranks
    float pageRank;
    int numLines, powerItr;
    std::string fromPage, toPage;
    std::cin >> numLines;
    std::cin >> powerItr;

    createAdjList(numLines, adjMap);
    //visualizeList(adjMap); //for debugging purposes

    //Default page rank of each is 1/(number of websites); remains when power iterator is 1
    pageRank = (float)1/adjMap.size();
    //Everything first has default ranks
    ranks = createDefRanks(adjMap, pageRank);
    //Calculate new ranks if powerItr > 1
    if (powerItr > 1) calculateRanks(adjMap, ranks, tempRanks, powerItr);

    std::string output = printRanks(ranks); //Print each website and their ranks

}

