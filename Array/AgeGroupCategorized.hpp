#ifndef AGE_GROUP_CATEGORIZED_HPP
#define AGE_GROUP_CATEGORIZED_HPP

#include "arrayHandler.hpp" 
#include <string>


struct AgeGroupStats {
    std::string groupName;
    int count;
    double totalEmission;
    
    
    int carCount, busCount, bikeCount, walkCount, schoolBusCount, carpoolCount;

    AgeGroupStats() : groupName(""), count(0), totalEmission(0), 
                      carCount(0), busCount(0), bikeCount(0), 
                      walkCount(0), schoolBusCount(0), carpoolCount(0) {}
};


void categorizeByAge(UserData data[], int size, AgeGroupStats groups[]);
void displayResults(AgeGroupStats groups[]);

#endif