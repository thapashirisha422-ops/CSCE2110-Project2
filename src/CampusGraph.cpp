//File : CampusGraph.cpp
//Author: leah rodriguez(member b)
//purpose: implement CampusGraph class for milestone 1

#include "../include/CampusGraph.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <cctype>

using namespace std;

//start total connections at 0
CampusGraph::CampusGraph() {
  totalConnections = 0;
}

//remove extra spaces from front and back of word
string CampusGraph::trim(string str) const{
  int start = 0;
  int len = (int)str.length();

  while(start < len && (str[start] == ' ' || str[start] == '\t' || str[start] == '\r' || str[start] == '\n')){
    start++;
  }

  int end = len - 1;
  while(end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\r' || str[end] == '\n')){
    end--;
  }

  if(start > end){
    return "";
  }
  return str.substr(start, end - start + 1);
}

//turn letters all lowercase
string CampusGraph::toLower(string str) const{
  string result = str;
  for(int i = 0; i < (int)result.length(); i++){
    result[i] = tolower(result[i]);
  }
  return result;
}

//break line at the |, blank, or #
bool CampusGraph::splitFields(string line, vector<string>& fields) const {
  fields.clear();
  string cleanLine = trim(line);

  if (cleanLine == "" || cleanLine[0] == '#'){
    return false;
  }

  string currentWord = "";
  for (int i = 0; i < (int)line.length(); i++){
    if(line[i] == '|'){
      fields.push_back(trim(currentWord));
      currentWord = "";
    } else{
      currentWord += line[i];
    }
  }
  fields.push_back(trim(currentWord));

  return true;
}

//check if buildings are connected
bool CampusGraph::hasEdge(int u, int v) const{
    for(int i = 0; i < (int)buildings[u].neighbors.size(); i++){
      if(buildings[u].neighbors[i] == v){
        return true;
      }
    }
    return false;
}

//looks for building in list and returns spot of -1 if not on list
int CampusGraph::findBuildingIndex(string name) const{
  string target = toLower(trim(name));
  if(target == ""){
    return - 1;
  }
  for (int i = 0; i < (int)buildings.size(); i++){
    if(toLower(buildings[i].name) == target){
      return i;
    }
  }
  return -1;
}

//add new buildings to list
bool CampusGraph::addBuilding(const string& buildingName){
  string cleanName = trim(buildingName);
  if(cleanName == "" || findBuildingIndex(cleanName) != -1){
    return false;
  }
  BuildingNode newNode;
  newNode.name = cleanName;
  buildings.push_back(newNode);
  return true;
}

//connect two buildings and adds 1 to totalConnections
bool CampusGraph::addConnection(const string& buildingA, const string& buildingB){
  int idxA = findBuildingIndex(buildingA);
  int idxB = findBuildingIndex(buildingB);
  if(idxA == -1 || idxB == -1 || idxA == idxB || hasEdge(idxA, idxB)){
    return false;
  }
  buildings[idxA].neighbors.push_back(idxB);
  buildings[idxB].neighbors.push_back(idxA);
  totalConnections++;
  return true;
}

//return true if building is in graph, false if not
bool CampusGraph::hasBuilding(const string& buildingName) const{
  return findBuildingIndex(buildingName) != -1;
}

//returns original spelling from buildings.txt
string CampusGraph::getCanonicalBuildingName(const string& name) const{
  int idx = findBuildingIndex(name);
  if(idx == -1){
    return "";
  }
  return buildings[idx].name;
}

//open buildings.txt and loads ones not bad/dupicate
LoadStats CampusGraph::loadBuildings(string filepath){
  LoadStats stats;
  ifstream inFile(filepath.c_str());
  string filename = "buildings.txt";

  if (!inFile.is_open()){
    cout << "Error: Cannot open file " << filepath << ". Treating as empty.\n";
    cout << filename << ": 0 accepted, 0 rejected\n";
    return stats;
  }

  int accepted = 0;
  int rejected = 0;
  int lineNum = 0;
  string line;

  while (getline(inFile, line)){
    lineNum++;
    vector<string> fields;

    if(!splitFields(line, fields)){
      continue;
    }

    if(fields.size() != 1){
      cout << "Warning [" << filename << " line " << lineNum << "]: Wrong field count. Record rejected.\n";
      rejected++;
      continue;
    }

    string bName = fields[0];

    if(bName == ""){
      cout << "Warning [" << filename << " line " << lineNum << "]: Empty building name. Record rejected.\n";
      rejected++;
      continue;
    }

    if(findBuildingIndex(bName) != -1){
      cout << "Warning [" << filename << " line " << lineNum << "]: Duplicate building '" << bName << "'. Record rejected.\n";
      rejected++;
      continue;
    }

    addBuilding(bName);
    accepted++;
  }
  cout << filename << ": " << accepted << " accepted, " << rejected << " rejected\n";
  stats.acceptedCount = accepted;
  stats.rejectedCount = rejected;
  return stats;
}

//opens connects.txt, ensures both buildings there, then connects
LoadStats CampusGraph::loadConnections(string filepath){
  LoadStats stats;
  ifstream inFile(filepath.c_str());
  string filename = "connections.txt";

  if(!inFile.is_open()){
    cout << "Error: Cannot open file " << filepath << ". Treating as empty.\n";
    cout << filename << ": 0 accepted, 0 rejected\n";
    return stats;
  }

  int accepted = 0;
  int rejected = 0;
  int lineNum = 0;
  string line; 

  while(getline(inFile, line)){
    lineNum++;
    vector<string> fields;

    if(!splitFields(line, fields)){
      continue;
    }

    if(fields.size() != 2){
      cout << "Warning [" << filename << " line " << lineNum << "]: Wrong field count. Record rejected.\n";
      rejected++;
      continue;
    }

  string nameA = fields[0];
  string nameB = fields[1];

  if(nameA == "" || nameB == ""){
    cout << "Warning [" << filename << " line " << lineNum << "]: Empty building field. Record rejected.\n";
    rejected++;
    continue;
  }

  int idxA = findBuildingIndex(nameA);
  if(idxA == -1){
    cout << "Warning [" << filename << " line " << lineNum << "]: Unknown building '" << nameA << "'. Record rejected.\n";
    rejected++;
    continue;
  }

  int idxB = findBuildingIndex(nameB);
  if(idxB == -1){
    cout << "Warning [" << filename << " line " << lineNum << "]: Unknown building '" << nameB << "'. Record rejected.\n";
    rejected++;
    continue;
  }

  if(idxA == idxB){
    cout << "Warning [" << filename << " line " << lineNum << "]: Self-connection on '" << buildings[idxA].name << "'. Record rejected.\n";
    rejected++;
    continue;
  }

  if(hasEdge(idxA, idxB)){
    cout << "Warning [" << filename << " line " << lineNum << "]: Duplicate connection between '" << buildings[idxA].name << "' and '" << buildings[idxB].name << "'. Record rejected.\n";
    rejected++;
    continue;
  }

  addConnection(nameA,nameB);
  accepted++;
  }

  cout << filename << ": " << accepted << " accepted, " << rejected << " rejected\n";
  stats.acceptedCount = accepted;
  stats.rejectedCount = rejected;
  return stats;
}

//menu option 3(prints every building and all buildings connected)
void CampusGraph::displayGraph() const{
  if(buildings.empty()){
    cout << "No buildings are loaded in the campus graph.\n";
    return;
  }

  cout << "\n--- Campus Graph ---\n";
  for(int i = 0; i < (int)buildings.size(); i++){
    cout << buildings[i].name << " -> ";

    if(buildings[i].neighbors.empty()){
      cout << "(no connections)";
    }else{
      for(int j = 0; j < (int)buildings[i].neighbors.size(); j++){
        int neighborIndex = buildings[i].neighbors[j];
        cout << buildings[neighborIndex].name;

        if(j + 1 < (int)buildings[i].neighbors.size()){
          cout << ", ";
        }
      }
    }
    cout << "\n";
  }
}

//menu option 4, how many connections
void CampusGraph::displayCountsAndDegrees() const{
  if(buildings.empty()){
    cout << "No buildings are loaded in the campus graph.\n";
    cout << "Total buildings: 0. Total connections: 0.\n";
    return;
  }

  cout << "\n--- Graph Counts and Degrees ---\n";
  for(int i = 0; i < (int)buildings.size(); i++){
    cout << buildings[i].name << ": " << buildings[i].neighbors.size() << "\n";
  }
  cout << "Total buildings: " << buildings.size() << ". Total connections: " << totalConnections << ".\n";
}

//menu option 5, use BFS to find buildings walk from start
void CampusGraph::findReachableBuildings(const string& startBuildingName) const{
    if(buildings.empty()){
      cout << "No buildings are loaded in the campus graph.\n";
      return;
    }

    string cleanStart = trim(startBuildingName);
    if(cleanStart == ""){
      cout << "Error: Building name cannot be blank.\n";
      return;
    }

    int startIdx = findBuildingIndex(cleanStart);
    if(startIdx == -1){
      cout << "Error: Unknown building '" << cleanStart << "'.\n";
      return;
    }

    int numBuildings = (int)buildings.size();
    vector<bool> visited(numBuildings, false);
    vector<int> distance(numBuildings, 0);
    queue<int> bfsQueue;

    visited[startIdx] = true;
    distance[startIdx] = 0;
    bfsQueue.push(startIdx);

    int reachableCount = 0;

    cout << "\nFrom " << buildings[startIdx].name << ":\n";

    while(!bfsQueue.empty()){
      int current = bfsQueue.front();
      bfsQueue.pop();
      reachableCount++;

      cout << buildings[current].name << " (distance " << distance[current] << ")\n";

      for(int i = 0; i < (int)buildings[current].neighbors.size(); i++){
        int nextNeighbor = buildings[current].neighbors[i];

        if(!visited[nextNeighbor]){
          visited[nextNeighbor] = true;
          distance[nextNeighbor] = distance[current] + 1;
          bfsQueue.push(nextNeighbor);
        }
      }
    }

    cout << "Reachable: " << reachableCount << " of " << numBuildings << " buildings\n";
}

// how many total buildings in graph(returns)
int CampusGraph::getBuildingCount() const{
  return (int)buildings.size();
}

// how many total connections in graph(returns)
int CampusGraph::getConnectionCount() const{
  return totalConnections;
}

//shared team function(calls loadBuildings)
LoadStats loadBuildings(const string& path, CampusGraph& graph){
  return graph.loadBuildings(path);
}

//shared team function(calls loadConnections)
LoadStats loadConnections(const string& path, CampusGraph& graph){
  return graph.loadConnections(path);
}

