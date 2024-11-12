#pragma once
#include <map>
#include <set>
#include <iostream>
#include <iomanip>
#include <sstream>

struct adjList{
    void createAdjList(int &numLines, std::map<std::string, std::set<std::string>> &adjMap);

    void visualizeList(const std::map<std::string, std::set<std::string>> &adjMap);

    std::map<std::string, float> createDefRanks(std::map<std::string,std::set<std::string>> &adjMap, float &pageRank);

    void calculateRanks(std::map<std::string, std::set<std::string>> &adjMap, std::map<std::string, float> &ranks, std::map<std::string, float> &tempRanks, int &powerItr);

    std::string printRanks(std::map<std::string, float> &ranks);
};