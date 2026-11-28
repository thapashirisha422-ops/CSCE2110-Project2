CSCE 2110 - Project 2
Smart Campus Navigation and Facility Analytics System

README - FINAL SUBMISSION

PROJECT DESCRIPTION

This project is a C++ console application that manages campus facilities, building connections, and academic department information.

The system uses:
- A custom hash table for facility storage and searching.
- An undirected graph and Breadth-First Search (BFS) for campus navigation.
- A general tree to organize academic departments.

MODULE OVERVIEW

Facility Module:
FacilityHashTable and FacilityLoader manage facility records.
The program supports ID, name, and category searches.
Facility IDs are stored in a custom hash table with a default capacity of 17 buckets.
The hash function starts at 0 and calculates:
hashValue = (hashValue * 31 + character ASCII value) % capacity
The program uses separate chaining with vectors to handle collisions.
A collision is counted when a valid facility is inserted into a nonempty bucket.
Name and category searches scan the accepted facility records.

Campus Graph Module:
CampusGraph stores buildings and connections using an adjacency list.
Connections are undirected, and neighbor insertion order is preserved.
BFS uses a queue to find reachable buildings and shortest paths.
The graph also provides building statistics and a connectivity report.

Department Tree Module:
DepartmentTree stores departments using a general tree.
It supports adding, searching, and displaying departments.
It includes preorder, postorder, and level-order traversals.
The statistics report shows total departments, leaves, and tree height.

PROJECT STRUCTURE

src/                  - C++ source files
include/              - Header files
data/                 - Instructor-provided data files
testdata/             - Additional testing files
README.txt            - Build and execution instructions
design_document.txt   - Data structure design and implementation details
test_results.txt      - Testing documentation
CONTRIBUTIONS.txt     - Team member contributions
.gitignore            - Excludes compiled files and editor files

TEAM MEMBERS

Aanchal Khadka
Leah Rodriguez
Shirisha Thapa

BUILD AND RUN
Open a Linux terminal in the main project directory.

Compile the program using:
g++ -std=c++17 -Iinclude src/*.cpp -o campus

Run the program using:
./campus

The program loads four files from the data/ directory by default:
- buildings.txt
- connections.txt
- facilities.txt
- departments.txt

To run with another dataset, use:
./campus testdata/collision

PROGRAM MENU
1. View all facilities
2. Search facility by ID
3. Search facility by name
4. Search facility by category
5. View campus graph
6. Display graph counts and degrees
7. Find reachable buildings (BFS)
8. Find shortest path (BFS)
9. Add department
10. Search department
11. Display department hierarchy
12. Preorder traversal
13. Postorder traversal
14. Level-order traversal
15. Department statistics
16. Facility category report
17. Graph connectivity report
18. Exit

DEPARTMENT TREE FEATURES

The Department Tree supports adding and searching departments, displaying the hierarchy, and performing preorder, postorder, and level-order traversals.
It also provides statistics showing the total number of departments, the number of leaf departments, and the tree height.
The system handles duplicate department names, nonexistent parent departments, blank inputs, and empty trees.

TESTING
The program has been tested using the original input files and additional test datasets.

The Department Tree was tested with:
- Valid department records
- Duplicate department names
- Invalid parent departments
- Blank department names
- Existing and nonexistent department searches
- Preorder, postorder, and level-order traversals
- Empty and root-only trees
- Department statistics

Detailed test results are recorded in test_results.txt.

ERROR HANDLING

The program validates menu choices and handles invalid inputs without crashing.
Invalid file records are rejected, and the program displays warning messages when appropriate.
The program also checks for missing files, invalid facility IDs, duplicate departments, and nonexistent parent departments.

EXITING THE PROGRAM
Select option 18 to exit the program normally.
