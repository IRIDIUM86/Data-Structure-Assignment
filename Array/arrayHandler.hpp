#ifndef ARRAY_HANDLER_HPP
#define ARRAY_HANDLER_HPP

#include <string>

struct UserData {
    std::string id;
    int age;
    std::string transport;
    int distance;
    float emissionFactor;
    int days;
    float emission;
};

const int maxRows = 525;
const int maxColumns = 6;

void addArray(std::string id, int age, std::string transport, int distance, float emissionFactor, int days);
void displayData();
float totalEmission();
void emissionByTransport();
void analyzeAgeGroup(int minAge, int maxAge, std::string groupName);

#endif