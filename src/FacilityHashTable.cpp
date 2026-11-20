#include "FacilityHashTable.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Author: Shirisha Thapa
// Implements the custom hash table for campus facilities.

// Removes outer spaces and converts text to lowercase
static string cleanText(string text) {
    size_t start = text.find_first_not_of(" \t\r\n");

    if (start == string::npos) {
        return "";
    }

    size_t end = text.find_last_not_of(" \t\r\n");
    text = text.substr(start, end - start + 1);

    for (char& letter : text) {
        if (letter >= 'A' && letter <= 'Z') {
            letter = letter - 'A' + 'a';
        }
    }

    return text;
}

// Displays information about one facility
static void printFacility(const Facility& facility) {
    cout << facility.facilityId << " | "
         << facility.facilityName << " | "
         << facility.buildingName << " | "
         << facility.category << endl;
}

// Removes extra spaces and converts an ID to uppercase
static string cleanId(string id) {
    while (!id.empty() &&
           (id[0] == ' ' || id[0] == '\t' || id[0] == '\r')) {
        id.erase(0, 1);
    }

    while (!id.empty() &&
           (id.back() == ' ' || id.back() == '\t' || id.back() == '\r')) {
        id.pop_back();
    }

    for (char& letter : id) {
        if (letter >= 'a' && letter <= 'z') {
            letter = letter - 'a' + 'A';
        }
    }

    return id;
}

// Checks if an ID follows the F001 format
static bool validId(const string& id) {
    if (id.length() != 4 || id[0] != 'F') {
        return false;
    }

    for (int i = 1; i < 4; i++) {
        if (id[i] < '0' || id[i] > '9') {
            return false;
        }
    }

    return true;
}

// Creates a hash table with the given capacity
FacilityHashTable::FacilityHashTable(size_t capacity)
    : buckets(capacity == 0 ? 17 : capacity), collisionCount(0) {
}

// Calculates the index for a facility ID
size_t FacilityHashTable::hashFunction(const string& facilityId) const {
    size_t hashValue = 0;

    for (char letter : facilityId) {
        hashValue = (hashValue * 31 + letter) % buckets.size();
    }

    return hashValue;
}

// Inserts a facility into the hash table
bool FacilityHashTable::insertFacility(const Facility& facility) {
    Facility newFacility = facility;
    newFacility.facilityId = cleanId(facility.facilityId);

    if (!validId(newFacility.facilityId)) {
        return false;
    }

    size_t index = hashFunction(newFacility.facilityId);

    // Check for duplicate IDs
    for (const Facility& current : buckets[index]) {
        if (current.facilityId == newFacility.facilityId) {
            return false;
        }
    }

        // Keep the spelling of the first accepted category
    for (const Facility& current : facilities) {
        if (cleanText(current.category) == cleanText(newFacility.category)) {
            newFacility.category = current.category;
            break;
        }
    }

    // Count a collision if the bucket is not empty
    if (!buckets[index].empty()) {
        collisionCount++;
    }

    buckets[index].push_back(newFacility);
    facilities.push_back(newFacility);

    return true;
}

// Searches for a facility by ID
const Facility* FacilityHashTable::findById(const string& facilityId) const {
    string id = cleanId(facilityId);

    if (!validId(id)) {
        return nullptr;
    }

    size_t index = hashFunction(id);

    for (const Facility& facility : buckets[index]) {
        if (facility.facilityId == id) {
            return &facility;
        }
    }

    return nullptr;
}

// Displays all facilities in file order
void FacilityHashTable::displayFacilities() const {
    if (facilities.empty()) {
        cout << "No facilities available." << endl;
        cout << "Total facilities: 0" << endl;
        return;
    }

        for (const Facility& facility : facilities) {
        printFacility(facility);
    }

    cout << "Total facilities: " << facilities.size() << endl;
}

// Searches facilities by complete name
void FacilityHashTable::searchByName(const string& name) const {
    string searchName = cleanText(name);
    int matches = 0;

    for (const Facility& facility : facilities) {
        if (cleanText(facility.facilityName) == searchName) {
            printFacility(facility);
            matches++;
        }
    }

    if (matches == 0) {
        cout << "No facilities found with that name." << endl;
    }

    cout << "Matches: " << matches << endl;
}

// Searches facilities by category
void FacilityHashTable::searchByCategory(const string& category) const {
    string searchCategory = cleanText(category);
    int matches = 0;

    for (const Facility& facility : facilities) {
        if (cleanText(facility.category) == searchCategory) {
            printFacility(facility);
            matches++;
        }
    }

    if (matches == 0) {
        cout << "No facilities found in that category." << endl;
    }

    cout << "Matches: " << matches << endl;
}

// Displays facility counts and percentages by category
void FacilityHashTable::displayCategoryReport() const {
    if (facilities.empty()) {
        cout << "No facilities available." << endl;
        cout << "Total facilities: 0" << endl;
        return;
    }

    vector<string> categories;
    vector<int> counts;

    for (const Facility& facility : facilities) {
        size_t index = 0;

        while (index < categories.size() &&
               cleanText(categories[index]) != cleanText(facility.category)) {
            index++;
        }

        if (index == categories.size()) {
            categories.push_back(facility.category);
            counts.push_back(1);
        }
        else {
            counts[index]++;
        }
    }

    cout << "Category | Count | Percentage" << endl;
    cout << fixed << setprecision(1);

    for (size_t i = 0; i < categories.size(); i++) {
        double percentage = counts[i] * 100.0 / facilities.size();

        cout << categories[i] << " | "
             << counts[i] << " | "
             << percentage << "%" << endl;
    }

    cout << "Total | " << facilities.size() << " | 100.0%" << endl;
    cout << defaultfloat << setprecision(6);
}

// Returns the hash table capacity
size_t FacilityHashTable::getCapacity() const {
    return buckets.size();
}

// Returns the number of stored facilities
size_t FacilityHashTable::getEntryCount() const {
    return facilities.size();
}

// Returns the number of collisions
size_t FacilityHashTable::getCollisionCount() const {
    return collisionCount;
}
