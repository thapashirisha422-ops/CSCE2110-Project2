// File: DepartmentTree.cpp
// Author: Aanchal Khadka
// Purpose: Implements the department tree and traversals.

#include "DepartmentTree.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <queue>

using namespace std;

//Remove spaces from the beginning and end 
static string trimName(const string& text) {
    size_t start = text.find_first_not_of(" \t\r\n");

    if (start == string::npos) {
        return "";
    }
    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}
// Convert a department name to lowercase
static string normalizeDepartmentName(const string& name) {
    string result = trimName(name);

    transform(result.begin(), result.end(), result.begin(),
        [] (unsigned char c) {
            return static_cast<char>(tolower(c));
        });
    return result;
}

// Constructor
DepartmentTree::DepartmentTree() {
    root = nullptr;
}
//Destructor
DepartmentTree::~DepartmentTree() {
    deleteTree(root);

}

// Delete all nodes recursively
void DepartmentTree::deleteTree(DepartmentNode* node) {
    if (node == nullptr) {
        return;
    }
    for (DepartmentNode* child : node ->children) {
        deleteTree(child);
    }
    delete node;
}
//Check if tree is empty
bool DepartmentTree::isEmpty() const {
    return root == nullptr;
}

// Search helper
DepartmentNode* DepartmentTree::findDepartment(
    DepartmentNode* node,
    const string& departmentName
) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (normalizeDepartmentName(node->departmentName) ==
        normalizeDepartmentName(departmentName)) {
        return node;
    }
    for (DepartmentNode* child : node->children) {
        DepartmentNode* found =
            findDepartment(child, departmentName);
        if (found != nullptr) {
            return found;
        }
    }

    return nullptr;
}
//Add a new department
bool DepartmentTree::addDepartment(
    const string& departmentName,
    const string& parentName
) {
    string name = trimName(departmentName);
    string parent = trimName(parentName);

    if (name.empty()) {
        return false;
    } 

    //Prevent duplicate department names
    if (findDepartment(root, name) !=nullptr) {
        return false;
    }
    // First department becomes the root
    if (isEmpty()) {
        if (!parent.empty() &&
            normalizeDepartmentName(parent) != "none") {
            return false;
        
    }
        root = new DepartmentNode(name);
        return true;
}
    // Additional roots are not allowed
    if (parent.empty() ||
    normalizeDepartmentName(parent) == "none") {
    return false;
}
    // Find the parent department
    DepartmentNode* parentNode =
    findDepartment(root,parent);
    if (parentNode == nullptr) {
    return false;
}
    //Create and attach the new department
    DepartmentNode* newNode =
         new DepartmentNode(name, parentNode);

    parentNode->children.push_back(newNode);
    return true;
}
//Search for a department
void DepartmentTree::searchDepartment(
    const string& departmentName
) const {
    DepartmentNode* found =
        findDepartment(root, departmentName);
    
    if (found == nullptr) {
        cout << "Department not found. " << endl;
        return;
    }
    int depth = 0;
    DepartmentNode* current = found;

    while (current->parent != nullptr) {
        depth++;
        current = current ->parent;
    }

    cout << "Department: " << found->departmentName << endl;

    if (found->parent == nullptr) {
        cout << "Parent: None" <<endl;
    } else {
        cout << "Parent: "
        << found->parent->departmentName << endl;
    }
    cout << "Direct children: "
         << found->children.size() << endl;
    
         cout << "Depth: " << depth << endl;
}
//Display hierarchy recursively
void DepartmentTree::displayHierarchyHelper(
    DepartmentNode* node,
    int depth
) const {
    if (node == nullptr) {
        return;
    }

    cout << string(depth *4, ' ')
         << node->departmentName << endl;
    
    for (DepartmentNode* child : node->children) {
        displayHierarchyHelper(child, depth + 1);
    }
}

//Display the entire hierarchy
void DepartmentTree::displayHierarchy() const {
    if (isEmpty()) {
        cout << "Department tree is empty." << endl;
        return;
    }

    displayHierarchyHelper(root, 0);
}
//Preorder traversal helper
void DepartmentTree::preorderHelper(
    DepartmentNode* node
) const {
    if (node == nullptr) {
        return;
    }

    cout << node->departmentName << endl;

    for (DepartmentNode* child : node->children) {
        preorderHelper(child);
    }
} 
//Display preorder traversal
void DepartmentTree::preorderTraversal() const {
    if (isEmpty()) {
        cout << "Department tree is empty." << endl;
        return;
    }
    preorderHelper(root);
}

// Postorder traversal helper
void DepartmentTree::postorderHelper(DepartmentNode* node) const {
    if (node == nullptr) {
        return;
    }
    // Visit all children first
    for (DepartmentNode* child : node->children) {
        postorderHelper(child);
    }
    // Visit parent last
    cout << node->departmentName << endl;
}
    // Postorder traversal
    void DepartmentTree::postorderTraversal() const {
    if (isEmpty()) {
        cout << "Department tree is empty." << endl;
        return;
    }
    postorderHelper(root);
    }
    void DepartmentTree::levelOrderTraversal() const {
        if (isEmpty()) {
            cout << "Department tree is empty." << endl;
            return;
        }

        queue<DepartmentNode*> q;

        // Start with the root
        q.push(root);

        while (!q.empty()) {
            // Get the next department
            DepartmentNode* current = q.front();
            q.pop();

            // Visit this department
            cout << current->departmentName << endl;

            // Add its children to the queue
            for (DepartmentNode* child : current->children) {
                q.push(child);
            }
        }

    }

    // Count all departments recursively
    int DepartmentTree::countHelper(DepartmentNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        int count = 1;
        for (DepartmentNode* child : node->children) {
            count += countHelper(child);
        }
        return count;
    }
    //Return total number of departments
    int DepartmentTree::countDepartments() const{
        return countHelper(root);
    }


 // Calculate height recursively
int DepartmentTree::heightHelper(DepartmentNode* node) const {
    if (node == nullptr) {
        return -1;
    }

    int maxChildHeight = -1;

    for (DepartmentNode* child : node->children) {
        int childHeight = heightHelper(child);

        if (childHeight > maxChildHeight) {
            maxChildHeight = childHeight;
        }
    }

    return maxChildHeight + 1;
}

// Return the height of the department tree
int DepartmentTree::treeHeight() const {
    return heightHelper(root);
}

    
 



