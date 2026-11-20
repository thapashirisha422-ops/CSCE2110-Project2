#ifndef FACILITY_HASH_TABLE_H
#define FACILITY_HASH_TABLE_H

#include <iostream>
#include <string>
#include <vector>
#include "Facility.h"

using namespace std;

// Author: Shirisha Thapa
// Stores campus facilities using a hash table.

class FacilityHashTable {
private:
    // Each bucket stores facilities with the same hash index
    vector<vector<Facility>> buckets;

    // Keeps facilities in the order they were loaded
    vector<Facility> facilities;

    size_t collisionCount;

    // Finds the hash index for a facility ID
    size_t hashFunction(const string& facilityId) const;

public:
    // Creates the hash table
    FacilityHashTable(size_t capacity = 17);

    // Adds a facility to the table
    bool insertFacility(const Facility& facility);

    // Finds a facility using its ID
    const Facility* findById(const string& facilityId) const;

    // Displays all facilities
    void displayFacilities() const;

    // Searches facilities by name
    void searchByName(const string& name) const;

    // Searches facilities by category
    void searchByCategory(const string& category) const;

    // Displays the facility category report
    void displayCategoryReport() const;

    // Returns hash table capacity
    size_t getCapacity() const;

    // Returns number of facilities
    size_t getEntryCount() const;

    // Returns number of collisions
    size_t getCollisionCount() const;
};

#endif
