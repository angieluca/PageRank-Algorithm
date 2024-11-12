#include <catch2/catch_test_macros.hpp>
#include "adjList.h"

using namespace std;

TEST_CASE("Test 1 - Only one website inserted") {
    string input = R"(4 2
google.com google.com
google.com google.com
google.com google.com
google.com google.com)";

    string expectedOutput = "google.com 1.00\n";

    //Same as main file:
    std::map<std::string, std::set<std::string>> adjMap; //Adjacency List
    std::map<std::string, float> tempRanks; //temporarily keep values during one iteration
    std::map<std::string, float> ranks; //official ranks
    float pageRank;
    int numLines = 4;
    int powerItr = 2;

    //Create adjacent List object and use class functions
    adjList graph;
    std::string fromPage, toPage;
    //Get user input of website (not calling function cuz don't want to use cin in test case)
    for (int i = 0; i < numLines; i++) {
        fromPage = "google.com";
        if (adjMap.find(fromPage) == adjMap.end()){
            adjMap[fromPage] = std::set<std::string>(); //Insert "from" website with empty vector
        }
        toPage = "google.com";
        if (adjMap.find(toPage) == adjMap.end()) {
            adjMap[toPage] = std::set<std::string>(); //Insert "to" website with empty vector
        }
        if (adjMap[fromPage].count(toPage) == 0){ //Check if website already in set
            adjMap[fromPage].emplace(toPage);
        }
    }
    pageRank = (float)1/adjMap.size();
    ranks = graph.createDefRanks(adjMap, pageRank);
    if (powerItr > 1) graph.calculateRanks(adjMap, ranks, tempRanks, powerItr);
    std::string actualOutput = graph.printRanks(ranks); //Print each website and their ranks

    REQUIRE (expectedOutput == actualOutput);
}

TEST_CASE("Test 2 - Check self loops") {
    string input = R"(2 1
google.com ufl.com
google.com google.com)";

    string expectedOutput = "google.com 0.50\nufl.com 0.50\n";

    //Same as main file:
    std::map<std::string, std::set<std::string>> adjMap; //Adjacency List
    std::map<std::string, float> tempRanks; //temporarily keep values during one iteration
    std::map<std::string, float> ranks; //official ranks
    float pageRank;
    int powerItr = 1;

    //Create adjacent List object and use class functions
    adjList graph;
    std::string fromPage, toPage;
    //Get user input of website (not calling function cuz don't want to use cin in test case)
    fromPage = "google.com";
    if (adjMap.find(fromPage) == adjMap.end()){
        adjMap[fromPage] = std::set<std::string>(); //Insert "from" website with empty vector
    }
    toPage = "ufl.com";
    if (adjMap.find(toPage) == adjMap.end()) {
        adjMap[toPage] = std::set<std::string>(); //Insert "to" website with empty vector
    }
    if (adjMap[fromPage].count(toPage) == 0){ //Check if website already in set
        adjMap[fromPage].emplace(toPage);
    }
    fromPage = "google.com";
    if (adjMap.find(fromPage) == adjMap.end()){
        adjMap[fromPage] = std::set<std::string>(); //Insert "from" website with empty vector
    }
    toPage = "google.com";
    if (adjMap.find(toPage) == adjMap.end()) {
        adjMap[toPage] = std::set<std::string>(); //Insert "to" website with empty vector
    }
    if (adjMap[fromPage].count(toPage) == 0){ //Check if website already in set
        adjMap[fromPage].emplace(toPage);
    }
    pageRank = (float)1/adjMap.size();
    ranks = graph.createDefRanks(adjMap, pageRank);
    if (powerItr > 1) graph.calculateRanks(adjMap, ranks, tempRanks, powerItr);
    std::string actualOutput = graph.printRanks(ranks); //Print each website and their ranks

    REQUIRE (expectedOutput == actualOutput);
}

TEST_CASE("Test 3 - Duplicates of same lines") {
    //Duplicates shouldn't matter
    string input = R"(3 2
maps.com ufl.com
google.com google.com
maps.com ufl.com)";

    string expectedOutput = "google.com 0.33\n"
                            "maps.com 0.00\n"
                            "ufl.com 0.33\n";

    //Same as main file:
    std::map<std::string, std::set<std::string>> adjMap; //Adjacency List
    std::map<std::string, float> tempRanks; //temporarily keep values during one iteration
    std::map<std::string, float> ranks; //official ranks
    float pageRank;
    int powerItr = 2;

    //Create adjacent List object and use class functions
    adjList graph;
    std::string fromPage, toPage;
    //Get user input of website (not calling function cuz don't want to use cin in test case)
    fromPage = "maps.com";
    if (adjMap.find(fromPage) == adjMap.end()){
        adjMap[fromPage] = std::set<std::string>(); //Insert "from" website with empty vector
    }
    toPage = "ufl.com";
    if (adjMap.find(toPage) == adjMap.end()) {
        adjMap[toPage] = std::set<std::string>(); //Insert "to" website with empty vector
    }
    if (adjMap[fromPage].count(toPage) == 0){ //Check if website already in set
        adjMap[fromPage].emplace(toPage);
    }
    fromPage = "google.com";
    if (adjMap.find(fromPage) == adjMap.end()){
        adjMap[fromPage] = std::set<std::string>(); //Insert "from" website with empty vector
    }
    toPage = "google.com";
    if (adjMap.find(toPage) == adjMap.end()) {
        adjMap[toPage] = std::set<std::string>(); //Insert "to" website with empty vector
    }
    if (adjMap[fromPage].count(toPage) == 0){ //Check if website already in set
        adjMap[fromPage].emplace(toPage);
    }
    fromPage = "maps.com";
    if (adjMap.find(fromPage) == adjMap.end()){
        adjMap[fromPage] = std::set<std::string>(); //Insert "from" website with empty vector
    }
    toPage = "ufl.com";
    if (adjMap.find(toPage) == adjMap.end()) {
        adjMap[toPage] = std::set<std::string>(); //Insert "to" website with empty vector
    }
    if (adjMap[fromPage].count(toPage) == 0){ //Check if website already in set
        adjMap[fromPage].emplace(toPage);
    }

    pageRank = (float)1/adjMap.size();
    ranks = graph.createDefRanks(adjMap, pageRank);
    if (powerItr > 1) graph.calculateRanks(adjMap, ranks, tempRanks, powerItr);
    std::string actualOutput = graph.printRanks(ranks); //Print each website and their ranks

    REQUIRE (expectedOutput == actualOutput);
}

TEST_CASE("Test 4 - All ranks should be zero with large iterator") {
    //Duplicates shouldn't matter
    string input = R"(2 20
maps.com ufl.com
ufl.com google.com)";

    string expectedOutput = "google.com 0.00\n"
                            "maps.com 0.00\n"
                            "ufl.com 0.00\n";

    //Same as main file:
    std::map<std::string, std::set<std::string>> adjMap; //Adjacency List
    std::map<std::string, float> tempRanks; //temporarily keep values during one iteration
    std::map<std::string, float> ranks; //official ranks
    float pageRank;
    int powerItr = 20;

    //Create adjacent List object and use class functions
    adjList graph;
    std::string fromPage, toPage;
    //Get user input of website (not calling function cuz don't want to use cin in test case)
    fromPage = "maps.com";
    if (adjMap.find(fromPage) == adjMap.end()){
        adjMap[fromPage] = std::set<std::string>(); //Insert "from" website with empty vector
    }
    toPage = "ufl.com";
    if (adjMap.find(toPage) == adjMap.end()) {
        adjMap[toPage] = std::set<std::string>(); //Insert "to" website with empty vector
    }
    if (adjMap[fromPage].count(toPage) == 0){ //Check if website already in set
        adjMap[fromPage].emplace(toPage);
    }
    fromPage = "ufl.com";
    if (adjMap.find(fromPage) == adjMap.end()){
        adjMap[fromPage] = std::set<std::string>(); //Insert "from" website with empty vector
    }
    toPage = "google.com";
    if (adjMap.find(toPage) == adjMap.end()) {
        adjMap[toPage] = std::set<std::string>(); //Insert "to" website with empty vector
    }
    if (adjMap[fromPage].count(toPage) == 0){ //Check if website already in set
        adjMap[fromPage].emplace(toPage);
    }

    pageRank = (float)1/adjMap.size();
    ranks = graph.createDefRanks(adjMap, pageRank);
    if (powerItr > 1) graph.calculateRanks(adjMap, ranks, tempRanks, powerItr);
    std::string actualOutput = graph.printRanks(ranks); //Print each website and their ranks

    REQUIRE (expectedOutput == actualOutput);
}

TEST_CASE("Test 5 - Confirm rounding works well") {
    //Should properly round to 0.33 (1/3)
    string input = R"(3 1
google.com gmail.com
google.com maps.com
maps.com google.com
)";

    string expectedOutput = "gmail.com 0.33\n"
                            "google.com 0.33\n"
                            "maps.com 0.33\n";

    //Same as main file:
    std::map<std::string, std::set<std::string>> adjMap; //Adjacency List
    std::map<std::string, float> tempRanks; //temporarily keep values during one iteration
    std::map<std::string, float> ranks; //official ranks
    float pageRank;
    int powerItr = 1;

    //Create adjacent List object and use class functions
    adjList graph;
    std::string fromPage, toPage;
    //Get user input of website (not calling function cuz don't want to use cin in test case)
    fromPage = "google.com";
    if (adjMap.find(fromPage) == adjMap.end()){
        adjMap[fromPage] = std::set<std::string>(); //Insert "from" website with empty vector
    }
    toPage = "gmail.com";
    if (adjMap.find(toPage) == adjMap.end()) {
        adjMap[toPage] = std::set<std::string>(); //Insert "to" website with empty vector
    }
    if (adjMap[fromPage].count(toPage) == 0){ //Check if website already in set
        adjMap[fromPage].emplace(toPage);
    }
    fromPage = "google.com";
    if (adjMap.find(fromPage) == adjMap.end()){
        adjMap[fromPage] = std::set<std::string>(); //Insert "from" website with empty vector
    }
    toPage = "maps.com";
    if (adjMap.find(toPage) == adjMap.end()) {
        adjMap[toPage] = std::set<std::string>(); //Insert "to" website with empty vector
    }
    if (adjMap[fromPage].count(toPage) == 0){ //Check if website already in set
        adjMap[fromPage].emplace(toPage);
    }
    fromPage = "maps.com";
    if (adjMap.find(fromPage) == adjMap.end()){
        adjMap[fromPage] = std::set<std::string>(); //Insert "from" website with empty vector
    }
    toPage = "google.com";
    if (adjMap.find(toPage) == adjMap.end()) {
        adjMap[toPage] = std::set<std::string>(); //Insert "to" website with empty vector
    }
    if (adjMap[fromPage].count(toPage) == 0){ //Check if website already in set
        adjMap[fromPage].emplace(toPage);
    }

    pageRank = (float)1/adjMap.size();
    ranks = graph.createDefRanks(adjMap, pageRank);
    if (powerItr > 1) graph.calculateRanks(adjMap, ranks, tempRanks, powerItr);
    std::string actualOutput = graph.printRanks(ranks); //Print each website and their ranks

    REQUIRE (expectedOutput == actualOutput);
}