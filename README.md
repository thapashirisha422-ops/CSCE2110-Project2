# CSCE2110-Project2
Smart Campus Navigation and Facility Analytics System

## Course
CSCE 2110 - Project 1

## PROJECT DESCRIPTION
This project is a C++ console application that manages campus facilities, building connections, and academic department information.

The system uses:
-A custom hash table for facility lookup
-A graph and BFS for campus navigation
-A general tree for department hierarchy

## PROJECT STRUCTURE
src/             - C++ source files
include/         - Header files
data/            - Instructor-provided data files
testdata/        - Additional test files

##Compilation Instructions
CONTRIBUTIONS.txt – Individual team member contributions.
design_document.txt – Data structure explanations and design decisions.
test_results.txt – Test cases, expected outputs, and actual results.
The project uses header C++17 header files stored inside the 'include' directory.

## Run Instructions
##Model overview

## Module Overview
Department Tree Module
Uses a general tree to organize departments in a parent-child hierarchy. It supports adding and searching departments, displaying the hierarchy, preorder, postorder, and level-order traversals, counting departments, and calculating tree height.

Facility Hash Table Module
Uses a hash table to store facility records and support efficient searching by facility ID. The hash table is designed to handle collisions and manage facility information.

Campus Graph Module
Uses a graph to represent campus buildings and their connections. Buildings are represented as vertices, while connections are represented as edges. The module supports graph traversal and campus navigation operations.

Hash Function and Collision Strategy
The proposed Facility module uses a hash function to convert a facility ID into an index in the hash table. A possible implementation is to process each character of the facility ID using a polynomial rolling hash and take the result modulo the table size.
The proposed collision strategy is separate chaining, where multiple facility records that produce the same index are stored in the same bucket. This allows collisions to be handled without overwriting existing records.
These hash-function and collision-strategy details must be checked against the final Facility module implementation.

Graph Representation
The proposed Campus Graph module uses an adjacency list to represent buildings and their connections. Each building maintains a list of its neighboring buildings.

This representation is memory-efficient for graphs with relatively few connections and supports traversal algorithms such as BFS and DFS.
./project2

## Error Handling
The program handles invalid menu selections, duplicate entries, missing or invalid parent departments, and unsuccessful searches. It checks for invalid facility information, duplicate facility records, and invalid connections between campus locations. The program also handles missing files, incorrectly formatted data, and invalid user input to prevent errors during execution.

## GitHub Repository
https://github.com/thapashirisha422-ops/CSCE2110-Project2.git
