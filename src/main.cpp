// CSCE 2110 - Project 2
// Smart Campus Navigation and Facility Analytics System
//File: main.cpp
//Author: Leah, Shirisha, Aanchal
//Purpose: Final project menu

#include <iostream>
#include <string>
#include <cstdlib>
#include "../include/CampusGraph.h"
#include "../include/FacilityHashTable.h"
#include "../include/DepartmentTree.h"
#include "../include/FacilityLoader.h"
#include "../include/DepartmentLoader.h"

using namespace std;

// Removes outer whitespace from input
string trimInput(string str){
  int start = 0;
  int len = (int)str.length();

  while(start < len && (str[start] == ' ' || str[start] == '\t' || str[start] == '\r' || str[start] == '\n')){
    start++;
  }

  int end = len - 1;
  while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\r' || str[end] == '\n')){
    end--;
  }

  if(start > end){
    return "";
  }
  return str.substr(start, end - start + 1);
}

// Displays the final menu
void printMenu(){
  cout << "\n--- Smart Campus Navigation System ---\n";
  cout << "1. View all facilities\n";
  cout << "2. Search facility by ID\n";
  cout << "3. Search facility by name\n";
  cout << "4. Search facility by category\n";
  cout << "5. View campus graph\n";
  cout << "6. Display graph counts and degrees\n";
  cout << "7. Find reachable buildings (BFS)\n";
  cout << "8. Find shortest path (BFS)\n";
  cout << "9. Add department\n";
  cout << "10. Search department\n";
  cout << "11. Display department hierarchy\n";
  cout << "12. Preorder traversal\n";
  cout << "13. Postorder traversal\n";
  cout << "14. Level-order traversal\n";
  cout << "15. Department statistics\n";
  cout << "16. Facility category report\n";
  cout << "17. Graph connectivity report\n";
  cout << "18. Exit\n";
  cout << "Enter choice: ";
}

// Loads data and handles menu choices
  int main(int argc, char* argv[]){
  cout << "Smart Campus Navigation System" << endl;

  string dataDirectory = "data";
  if(argc >= 2){
    dataDirectory = argv[1];
  }

  CampusGraph campusGraph;
  FacilityHashTable facilityTable;
  DepartmentTree departmentTree;

  loadBuildings(dataDirectory + "/buildings.txt", campusGraph);
  loadConnections(dataDirectory + "/connections.txt", campusGraph);
  loadFacilities(dataDirectory + "/facilities.txt",campusGraph, facilityTable);
  loadDepartments(dataDirectory + "/departments.txt", departmentTree);

  bool running = true;
  while(running){
    printMenu();

    string userInput;
    if(!getline(cin, userInput)){
      break;
    }
    string trimmed = trimInput(userInput);

    if(trimmed == ""){
      cout << "Error: Please enter a number from 1 to 18(or 0 to exit).\n";
      continue;
    }
    bool allDigits = true;
    for (int i = 0; i < (int)trimmed.length(); i++){
      if(trimmed[i] < '0' || trimmed[i] > '9'){
      allDigits = false;
      break;
      }
    }
    if(!allDigits || trimmed.length() > 4){
      cout << "Error: Invalid menu input '" << trimmed << "'. Please enter a valid option number.\n";
      continue;
    }

    int choice = atoi(trimmed.c_str());

    if(choice == 1){
      facilityTable.displayFacilities();
    }
   else if(choice == 2){
  cout << "Enter facility ID: ";
  string facilityId;
  getline(cin, facilityId);

  facilityId = trimInput(facilityId);

  // Convert ID to uppercase
  for(char& letter : facilityId){
    if(letter >= 'a' && letter <= 'z'){
      letter = letter - 'a' + 'A';
    }
  }

  // Check ID format
  bool validId = facilityId.length() == 4 && facilityId[0] == 'F';

  if(validId){
    for(int i = 1; i < 4; i++){
      if(facilityId[i] < '0' || facilityId[i] > '9'){
        validId = false;
      }
    }
  }

  if(facilityId.empty()){
    cout << "Error: Facility ID cannot be blank.\n";
  }
  else if(!validId){
    cout << "Invalid ID format. Use F followed by three digits.\n";
  }
  else{
    const Facility* result = facilityTable.findById(facilityId);

    if(result == nullptr){
      cout << "Facility " << facilityId << " not found.\n";
    }
    else{
      cout << result->facilityId << " | "
           << result->facilityName << " | "
           << result->buildingName << " | "
           << result->category << endl;
    }
  }
}

      else if(choice == 3){
      cout << "Enter facility name: ";
      string name;
      getline(cin, name);

      if(trimInput(name) == ""){
        cout << "Error: Facility name cannot be blank.\n";
      }else{
        facilityTable.searchByName(name);
      }
    }
    else if(choice == 4){
      cout << "Enter facility category: ";
      string category;
      getline(cin, category);

      if(trimInput(category) == ""){
        cout << "Error: Category cannot be blank.\n";
      }else{
        facilityTable.searchByCategory(category);
      }
    }   
    else if (choice == 5){
      campusGraph.displayGraph();
    }
    else if(choice == 6){
      campusGraph.displayCountsAndDegrees();
    }
    else if (choice == 7){
      cout << "Enter starting building name: ";
      string buildingName;
      getline(cin, buildingName);
      if(trimInput(buildingName) == ""){
        cout << "Error: Building name cannot be blank.\n";
      }else{
        campusGraph.findReachableBuildings(buildingName);
      }
    }
    else if(choice == 9){
      cout << "Enter department name: ";
      string departmentName;
      getline(cin, departmentName);
      if(trimInput(departmentName) == ""){
        cout << "Error: Department name cannot be blank.\n";
      }else if(departmentTree.isEmpty()){
        departmentTree.addDepartment(trimInput(departmentName), "NONE");
      }else{
        cout << "Enter parent department name: ";
        string parentName;
        getline(cin, parentName);
        if(trimInput(parentName) == ""){
          cout << "Error: Parent department name cannot be blank.\n";
        }else{
          if (departmentTree.departmentExists(trimInput(departmentName))) {
    cout << "Error: Department already exists.\n";
}
else if (!departmentTree.departmentExists(trimInput(parentName))) {
    cout << "Error: Parent department not found.\n";
}
else {
    departmentTree.addDepartment(trimInput(departmentName), trimInput(parentName));
}
        }
      }
    }
    else if(choice == 10){
      cout << "Enter department name: ";
      string departmentName;
      getline(cin, departmentName);
      if(trimInput(departmentName) == ""){
        cout << "Error: Department name cannot be blank.\n";
      }else{
        departmentTree.searchDepartment(trimInput(departmentName));
      }
    }
    else if(choice == 11){
      departmentTree.displayHierarchy();
    }
    else if(choice == 12){
      departmentTree.preorderTraversal();
    }
          else if(choice == 16){
      facilityTable.displayCategoryReport();
    }
    else if(choice == 8 || choice == 13 || choice == 14 ||
            choice == 15 || choice == 17){
      cout << "This option is pending team integration.\n";
    }
    else if (choice == 18 || choice == 0){
      cout << "Exiting program.\n";
      running = false;
    }
    else{
      cout << "Error: Option " << choice << " is not an option. Please enter a number from 1 to 18(or 0 to exit).\n";
    }
  }

  return 0;
}
      
      
        


