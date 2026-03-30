#ifndef NODEHELPER_HPP  // 1. Check if this "key" exists
#define NODEHELPER_HPP  // 2. If not, create the "key" and read the file

#include <string>

struct Residents {
    // Data fields 
    std::string residentID;
    int age;
    std::string modeOfTransport;
    int dailyDistance;
    float carbonEmissionFactor;
    int averageDayPerMonth;

    // Link to the next node
    Residents* next;

    // Initialize the data
    Residents(std::string id, int age, std::string transport, int distance, float emissionFactor, int days) {
        // Assign values to your data fields
        this->residentID = id;
        this->age = age;
        this->modeOfTransport = transport;
        this->dailyDistance = distance;
        this->carbonEmissionFactor = emissionFactor;
        this->averageDayPerMonth = days;
        this->next = nullptr;
    }
};

Residents* addResidents(Residents* head, std::string id, int age, std::string transport, int distance, float emissionFactor, int days);

#endif // 3. End of the guard