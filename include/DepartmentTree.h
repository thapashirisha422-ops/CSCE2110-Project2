#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H

#include <string>
#include "DepartmentNode.h"

using namespace std;

class DepartmentTree {
private:
    DepartmentNode* root;
     //Helper functions
     DepartmentNode* findDepartment(
        DepartmentNode* node,
        const string& departmentName
    ) const;

    void displayHierarchyHelper(
    DepartmentNode* node,
    int depth
    ) const;

    void preorderHelper(
    DepartmentNode* node
    ) const;

    void deleteTree(
    DepartmentNode* node
    );
    void postorderHelper(DepartmentNode* node) const;

    int countHelper(DepartmentNode* node) const;

    int heightHelper(DepartmentNode* node) const;

public:
    // Constructor
    DepartmentTree();

    // Destructor
    ~DepartmentTree();
    
    // Prevent accidental copying of raw pointers
    DepartmentTree(const DepartmentTree&) = delete;
    DepartmentTree& operator=(const DepartmentTree&) = delete;

    //Add a new department
    bool addDepartment(
        const string& departmentName,
        const string& parentName
    );

    //Check whether the tree is empty
    bool isEmpty() const;

    // Check whether a department already exists
    bool departmentExists(const string& departmentName) const;

    // Search department
    void searchDepartment(
        const string& departmentName
    ) const;

    // Display department hierarchy
    void displayHierarchy() const;

    // Preorder traversal
    void preorderTraversal() const;

    // Postorder traversal
    void postorderTraversal() const;

    // Level-order traversal (BFS)
    void levelOrderTraversal() const;

    int countDepartments() const;
    int treeHeight() const;


};
#endif
