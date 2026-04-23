#ifndef NODEHELPER_HPP
#define NODEHELPER_HPP

#include <string>

extern int currentMaxStackDepth;

struct Residents {
    // Data fields 
    std::string residentID;
    int age;
    std::string modeOfTransport;
    int dailyDistance;
    float carbonEmissionFactor;
    int averageDayPerMonth;
    std::string ageGroup;

    // Link to the next node
    Residents* next;

    // Initialize the data
    Residents(std::string id, int age, std::string transport, int distance, float emissionFactor, int days, std::string ageGroup) {
        // Assign values to your data fields
        this->residentID = id;
        this->age = age;
        this->modeOfTransport = transport;
        this->dailyDistance = distance;
        this->carbonEmissionFactor = emissionFactor;
        this->averageDayPerMonth = days;
        this->ageGroup = ageGroup;
        this->next = nullptr;
    }
};

Residents* addResidents(Residents* head, std::string id, int age, std::string transport, int distance, float emissionFactor, int days, std::string ageGroup);

std::string ageGrouping(int age);

Residents* searchMenu(Residents* head);

int countResidents(Residents* head);

Residents* getMiddle(Residents* head);

Residents* sortedMerge(Residents* a, Residents* b, std::string target);

void mergeSort(Residents** headRef, std::string target, int currentDepth = 1);

#endif // 3. End of the guard