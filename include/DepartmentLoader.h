// File: DepartmentLoader.h
// Author: Aanchal Khadka
// Purpose: Declares the function for loading department records from a file.

#ifndef DEPARTMENT_LOADER_H
#define DEPARTMENT_LOADER_H
#include <string>
#include "DepartmentTree.h"
#include "LoadStats.h"

using namespace std;

//Load department records from a text file
LoadStats loadDepartments(
    const string& path,
    DepartmentTree& tree
);
#endif
