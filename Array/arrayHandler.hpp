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
    int datasetId; // 0 = CityA, 1 = CityB, 2 = CityC
};

const int maxRows = 525;
const int maxColumns = 6;

extern UserData userData[maxRows];
extern int dataCount;
extern int currentRow;

void addArray(std::string id, int age, std::string transport, int distance, float emissionFactor, int days, int datasetId = 0);
void displayData();
float totalEmission();
void emissionByTransport();
void analyzeAgeGroup(int minAge, int maxAge, std::string groupName);
void sortUserData(int criteria);
void getActualMemoryUsage();
void searchByTransport(std::string targetMode);
void searchByDistance(int threshold);
int binarySearchAge(int targetAge);

#endif