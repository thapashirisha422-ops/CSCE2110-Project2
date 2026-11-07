// File: LoadStats.h
// Author: Aanchal Khadka
// Purpose: Defines a structure for tracking accepted and rejected records.

#ifndef LOAD_STATS_H
#define LOAD_STATS_H

//Stores the number of accepted and rejected records
struct LoadStats {
    int accepted = 0;
    int rejected = 0;
};

#endif

