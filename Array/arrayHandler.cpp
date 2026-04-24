#include <iostream>
#include <string>
#include <windows.h>
#include <psapi.h>
#include "arrayHandler.hpp"

// Define the variables here
UserData userData[maxRows];
int currentRow = 0;

void addArray(std::string id, int age, std::string transport, int distance, float emissionFactor, int days, int datasetId){
    if (currentRow < maxRows) {
        userData[currentRow].id = id;
        userData[currentRow].age = age;
        userData[currentRow].transport = transport;
        userData[currentRow].distance = distance;
        userData[currentRow].emissionFactor = emissionFactor;
        userData[currentRow].days = days;
        userData[currentRow].emission = distance * emissionFactor * days;
        userData[currentRow].datasetId = datasetId;
        currentRow++;
    } else {
        std::cerr << "Error: Maximum row limit reached!" << std::endl;
    }
}

void displayData() {
    std::cout << "\n========================================================" << std::endl;
    std::cout << "ID\tAge\tTransport\tDistance\tFactor\tDays\tEmission" << std::endl;
    std::cout << "========================================================" << std::endl;

    for (int i = 0; i < currentRow; i++) {
        std::cout << userData[i].id << "\t"
                  << userData[i].age << "\t"
                  << userData[i].transport << "\t\t"
                  << userData[i].distance << "\t\t"
                  << userData[i].emissionFactor << "\t"
                  << userData[i].days << "\t"
                  << userData[i].emission
                  << std::endl;
    }

    if (currentRow == 0) {
        std::cout << "No data found in the array." << std::endl;
    }

    std::cout << "Total Rows: " << currentRow << std::endl;
}

float totalEmission() {
    float total = 0;
    for (int i = 0; i < currentRow; i++) {
        total += userData[i].emission;
    }
    return total;
}

void emissionByTransport() {
    float car = 0, bus = 0, bicycle = 0, walking = 0, carpool = 0, schoolBus = 0;

    for (int i = 0; i < currentRow; i++) {
        if (userData[i].transport == "Car")
            car += userData[i].emission;
        else if (userData[i].transport == "Bus")
            bus += userData[i].emission;
        else if (userData[i].transport == "Bicycle")
            bicycle += userData[i].emission;
        else if (userData[i].transport == "Walking")
            walking += userData[i].emission;
        else if (userData[i].transport == "Carpool")
            carpool += userData[i].emission;
        else if (userData[i].transport == "School Bus")
            schoolBus += userData[i].emission;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "Emission by Transport" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Car: " << car << " kg CO2" << std::endl;
    std::cout << "Bus: " << bus << " kg CO2" << std::endl;
    std::cout << "Bicycle: " << bicycle << " kg CO2" << std::endl;
    std::cout << "Walking: " << walking << " kg CO2" << std::endl;
    std::cout << "Carpool: " << carpool << " kg CO2" << std::endl;
    std::cout << "School Bus: " << schoolBus << " kg CO2" << std::endl;
}

void analyzeAgeGroup(int minAge, int maxAge, std::string groupName) {
    int bicycleCount = 0, walkingCount = 0, busCount = 0, carCount = 0, carpoolCount = 0, schoolBusCount = 0;
    float bicycleEmission = 0, walkingEmission = 0, busEmission = 0, carEmission = 0, carpoolEmission = 0, schoolBusEmission = 0;

    for (int i = 0; i < currentRow; i++) {
        if (userData[i].age >= minAge && userData[i].age <= maxAge) {
            if (userData[i].transport == "Bicycle") {
                bicycleCount++;
                bicycleEmission += userData[i].emission;
            }
            else if (userData[i].transport == "Walking") {
                walkingCount++;
                walkingEmission += userData[i].emission;
            }
            else if (userData[i].transport == "Bus") {
                busCount++;
                busEmission += userData[i].emission;
            }
            else if (userData[i].transport == "Car") {
                carCount++;
                carEmission += userData[i].emission;
            }
            else if (userData[i].transport == "Carpool") {
                carpoolCount++;
                carpoolEmission += userData[i].emission;
            }
            else if (userData[i].transport == "School Bus") {
                schoolBusCount++;
                schoolBusEmission += userData[i].emission;
            }
        }
    }

    float totalGroupEmission = bicycleEmission + walkingEmission + busEmission + carEmission + carpoolEmission + schoolBusEmission;

    std::cout << "\nAge Group: " << groupName << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "Mode\t\tCount\tTotal Emission\tAverage per Resident" << std::endl;

    if (bicycleCount > 0)
        std::cout << "Bicycle\t\t" << bicycleCount << "\t" << bicycleEmission << "\t\t" << (bicycleEmission / bicycleCount) << std::endl;
    if (walkingCount > 0)
        std::cout << "Walking\t\t" << walkingCount << "\t" << walkingEmission << "\t\t" << (walkingEmission / walkingCount) << std::endl;
    if (busCount > 0)
        std::cout << "Bus\t\t" << busCount << "\t" << busEmission << "\t\t" << (busEmission / busCount) << std::endl;
    if (carCount > 0)
        std::cout << "Car\t\t" << carCount << "\t" << carEmission << "\t\t" << (carEmission / carCount) << std::endl;
    if (carpoolCount > 0)
        std::cout << "Carpool\t\t" << carpoolCount << "\t" << carpoolEmission << "\t\t" << (carpoolEmission / carpoolCount) << std::endl;
    if (schoolBusCount > 0)
        std::cout << "School Bus\t" << schoolBusCount << "\t" << schoolBusEmission << "\t\t" << (schoolBusEmission / schoolBusCount) << std::endl;

    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "Total Emission for Age Group: " << totalGroupEmission << " kg CO2" << std::endl;
}

void sortUserData(int criteria) {
    for (int i = 0; i < currentRow - 1; i++) {
        for (int j = 0; j < currentRow - i - 1; j++) {
            bool swapNeeded = false;

            // Calculate emission for comparison if needed
            double emissionJ = userData[j].distance * userData[j].emissionFactor * userData[j].days;
            double emissionJ1 = userData[j+1].distance * userData[j+1].emissionFactor * userData[j+1].days;

            if (criteria == 1) { // Sort by Age
                if (userData[j].age > userData[j + 1].age) swapNeeded = true;
            } 
            else if (criteria == 2) { // Sort by Daily Distance
                if (userData[j].distance > userData[j + 1].distance) swapNeeded = true;
            } 
            else if (criteria == 3) { // Sort by Carbon Emission
                if (emissionJ > emissionJ1) swapNeeded = true;
            }

            if (swapNeeded) {
                // Manual swap since STL <utility> might be restricted
                UserData temp = userData[j];
                userData[j] = userData[j + 1];
                userData[j + 1] = temp;
            }
        }
    }
}

void getActualMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memCounter;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter))) {
        std::cout << "Actual RAM Usage: " << memCounter.WorkingSetSize / 1024 << " KB" << std::endl;
    }
}

// Search by Mode of Transport (e.g., "Car") [cite: 106]
void searchByTransport(std::string targetMode) {
    bool found = false;
    std::cout << "Residents using " << targetMode << ":" << std::endl;
    
    for (int i = 0; i < currentRow; i++) {
        if (userData[i].transport == targetMode) {
            std::cout << "ID: " << userData[i].id << " | Age: " << userData[i].age << std::endl;
            found = true;
        }
    }
    if (!found) std::cout << "No residents found using this mode." << std::endl;
}

// Search by Distance Threshold (e.g., > 15km) [cite: 107]
void searchByDistance(int threshold) {
    std::cout << "Residents traveling more than " << threshold << " km:" << std::endl;
    for (int i = 0; i < currentRow; i++) {
        if (userData[i].distance > threshold) {
            std::cout << "ID: " << userData[i].id << " | Distance: " << userData[i].distance << " km" << std::endl;
        }
    }
}

// Prerequisite: userData must be sorted by Age
int binarySearchAge(int targetAge) {
    int low = 0, high = currentRow - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (userData[mid].age == targetAge) return mid;
        if (userData[mid].age < targetAge) low = mid + 1;
        else high = mid - 1;
    }
    return -1; // Not found
}
