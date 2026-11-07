//File: CampusGraph.h
//Author: Leah Rodriguez(member b)
//Purpose: Declare CampusGraph class for storing running BFS, buildings, and walkways.

#ifndef CAMPUS_GRAPH_H
#define CAMPUS_GRAPH_H

#include <string>
#include <vector>

using namespace std;

//tally of how many lines accepted & rejected when loading files
#ifndef LOAD_STATS_DEFINED
#define LOAD_STATS_DEFINED
struct LoadStats{
  int acceptedCount = 0;
  int rejectedCount = 0;
};
#endif

//one building name plus list of connected buildings
struct BuildingNode{
  string name;
  vector<int> neighbors;
};

class CampusGraph{

private:
  vector<BuildingNode> buildings; //all buildings in graph
  int totalConnections; //amount of walkways

  //helper functions (cleaning words, splitting lines, & checking vconnections)
  string trim(string str) const;
  string toLower(string str) const;
  bool splitFields(string line, vector<string>& fields) const;
  bool hasEdge(int u, int v) const;

public:
  CampusGraph();

  //buildings.txt and connections.txt loaded and opened
  LoadStats loadBuildings(string filepath);
  LoadStats loadConnections(string filepath);

  //look for building return spot (-1 if no)
  int findBuildingIndex(string name) const;
  //team functions 
  bool addBuilding(const string& buildingName);
  bool addConnection(const string& buildingA, const string& buildingB);
  bool hasBuilding(const string& buildingName) const;
  string getCanonicalBuildingName(const string& name) const;

  //menu options 3,4,5
  void displayGraph() const;
  void displayCountsAndDegrees() const;
  void findReachableBuildings(const string& startBuildingName) const;

  //number of buildings and connections 
  int getBuildingCount() const;
  int getConnectionCount() const;
};

//shared team functions to call loadBuildings and loadConnections
LoadStats loadBuildings(const string& path, CampusGraph& graph);
LoadStats loadConnections(const string& path, CampusGraph& graph);

#endif
