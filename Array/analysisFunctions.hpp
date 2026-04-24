#ifndef ANALYSISFUNCTIONS_HPP
#define ANALYSISFUNCTIONS_HPP

#include "arrayHandler.hpp"
#include <string>

struct AgeGroupStats {
    int residentCount = 0;
    double totalEmissions = 0.0;
    // index 0: Car, 1: Bus, 2: Bicycle, 3: Walking, 4: School Bus, 5: Carpool
    int transportCounts[6] = {0, 0, 0, 0, 0, 0};
    double emissionCounts[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
};

extern UserData userData[maxRows];
extern int dataCount;
extern AgeGroupStats group[5];

void displaySummary(int size);
int getGroupIndex(int age);
std::string getSummaryData(int size, AgeGroupStats group[]);

void displaySortMenu(int& size);
void quickSort(int low, int high, std::string target);
int partition(int low, int high, std::string target);

#endif
