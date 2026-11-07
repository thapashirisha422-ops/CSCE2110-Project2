CSCE 2110 - Project 2
Smart Campus Navigation and Facility Analytics System

PROJECT DESCRIPTION
This project is a C++ console application that manages campus facilities, building connections, and academic department information.

The system uses:
- A custom hash table for facility lookup
- A graph and BFS for campus navigation
- A general tree for department hierarchy

PROJECT STRUCTURE
src/             - C++ source files
include/         - Header files
data/            - Instructor-provided data files
testdata/        - Additional test files

TEAM MEMBERS
Aanchal Khadka
Leah Rodriguez
Shirisha Thapa

CURRENT STATUS
Milestone 1 features have been implemented and tested.
All documentation and final verification have been completed.

BUILD AND RUN
Open a Linux terminal in the main project folder.

Compile the program using:

g++ -std=c++17 -Iinclude src/*.cpp -o campus

Run the program using:

./campus

The program loads the four files in the data/ folder by default.

To run the program with the additional collision test files, use:

./campus testdata/collision

PROGRAM MENU
Options 1 through 9 provide the Milestone 1 features.
Option 10 exits the program.
