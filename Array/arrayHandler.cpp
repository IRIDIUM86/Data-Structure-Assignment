#include <iostream>
#include <string>
#include "arrayHandler.hpp"

// Define the variables here
UserData dataTable[maxRows];
int currentRow = 0;

void addArray(std::string id, int age, std::string transport, int distance, float emissionFactor, int days){
    if (currentRow < maxRows) {
        dataTable[currentRow].id = id;
        dataTable[currentRow].age = age;
        dataTable[currentRow].transport = transport;
        dataTable[currentRow].distance = distance;
        dataTable[currentRow].emissionFactor = emissionFactor;
        dataTable[currentRow].days = days;
        dataTable[currentRow].emission = distance * emissionFactor * days;
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
        std::cout << dataTable[i].id << "\t"
                  << dataTable[i].age << "\t"
                  << dataTable[i].transport << "\t\t"
                  << dataTable[i].distance << "\t\t"
                  << dataTable[i].emissionFactor << "\t"
                  << dataTable[i].days << "\t"
                  << dataTable[i].emission
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
        total += dataTable[i].emission;
    }
    return total;
}

void emissionByTransport() {
    float car = 0, bus = 0, bicycle = 0, walking = 0, carpool = 0, schoolBus = 0;

    for (int i = 0; i < currentRow; i++) {
        if (dataTable[i].transport == "Car")
            car += dataTable[i].emission;
        else if (dataTable[i].transport == "Bus")
            bus += dataTable[i].emission;
        else if (dataTable[i].transport == "Bicycle")
            bicycle += dataTable[i].emission;
        else if (dataTable[i].transport == "Walking")
            walking += dataTable[i].emission;
        else if (dataTable[i].transport == "Carpool")
            carpool += dataTable[i].emission;
        else if (dataTable[i].transport == "School Bus")
            schoolBus += dataTable[i].emission;
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
        if (dataTable[i].age >= minAge && dataTable[i].age <= maxAge) {
            if (dataTable[i].transport == "Bicycle") {
                bicycleCount++;
                bicycleEmission += dataTable[i].emission;
            }
            else if (dataTable[i].transport == "Walking") {
                walkingCount++;
                walkingEmission += dataTable[i].emission;
            }
            else if (dataTable[i].transport == "Bus") {
                busCount++;
                busEmission += dataTable[i].emission;
            }
            else if (dataTable[i].transport == "Car") {
                carCount++;
                carEmission += dataTable[i].emission;
            }
            else if (dataTable[i].transport == "Carpool") {
                carpoolCount++;
                carpoolEmission += dataTable[i].emission;
            }
            else if (dataTable[i].transport == "School Bus") {
                schoolBusCount++;
                schoolBusEmission += dataTable[i].emission;
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