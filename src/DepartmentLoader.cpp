#include "DepartmentLoader.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//Remove whitespace from the beginning and end 
static string trimField(const string& text) {
    size_t start = text.find_first_not_of(" \t\r\n");

    if (start == string::npos) {
        return "";
    }
    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

//Convert text to lowercase for comparisons
static string lowerField(string text) {
    for (char& c : text) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }
    return text;
}
//Load department hierarchy from a file
LoadStats loadDepartments(
    const string& path,
    DepartmentTree& tree
) {
    LoadStats stats;

    ifstream file(path);

   if (!file.is_open()) {
    cout << "Error: Cannot open " << path << endl;
    cout << path << ": 0 accepted, 0 rejected" << endl;
    return stats;
}
string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;

        string cleanedLine = trimField(line);

        // Ignore blank and comment lines
        if (cleanedLine.empty() || cleanedLine[0] == '#') {
            continue;
        }

        // Check that exactly two fields exist
        size_t separator = line.find('|');

        if (separator == string::npos ||
            line.find('|', separator + 1) != string::npos) {
            cout << "Warning: " << path
                 << ", line " << lineNumber
                 << ": Expected two fields." << endl;

            stats.rejected++;
            continue;
        }

        string departmentName =
            trimField(line.substr(0, separator));

        string parentName =
            trimField(line.substr(separator + 1));

        // Reject empty fields
        if (departmentName.empty() || parentName.empty()) {
            cout << "Warning: " << path
                 << ", line " << lineNumber
                 << ": Empty department or parent name."
                 << endl;

            stats.rejected++;
            continue;
        }

        // First accepted record must be the root
        if (tree.isEmpty() &&
            lowerField(parentName) != "none") {
            cout << "Warning: " << path
                 << ", line " << lineNumber
                 << ": Root must have NONE as parent."
                 << endl;

            stats.rejected++;
            continue;
        }

        // Add department; rejects duplicates and unknown parents
        if (!tree.addDepartment(departmentName, parentName)) {
            cout << "Warning: " << path
                 << ", line " << lineNumber
                 << ": Duplicate department or invalid parent: "
                 << departmentName << endl;

            stats.rejected++;
            continue;
        }

        stats.accepted++;
    }

    cout << path << ": "
         << stats.accepted << " accepted, "
         << stats.rejected << " rejected" << endl;

    return stats;
}
