#ifndef GENERALFUNCTIONS_HPP
#define GENERALFUNCTIONS_HPP

#include "nodeHelper.hpp"

struct AgeGroupStats {
    int residentCount = 0;
    double totalEmissions = 0.0;
    // index 0: Car, 1: Bus, 2: Bicycle, 3: Walking, 4: School Bus, 5: Carpool
    int transportCounts[6] = {0, 0, 0, 0, 0, 0}; 
};

extern AgeGroupStats group[5];

void displaySummary(Residents* head);
int getGroupIndex(std::string category);
std::string getSummaryData (Residents* head, AgeGroupStats group[]);

#endif