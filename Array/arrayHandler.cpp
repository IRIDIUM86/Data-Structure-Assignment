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
        currentRow++;
    } else {
        std::cerr << "Error: Maximum row limit reached!" << std::endl;
    }
}

void displayData() {
    std::cout << "\n========================================================" << std::endl;
    std::cout << "ID\tAge\tTransport\tDistance\tFactor\tDays" << std::endl;
    std::cout << "========================================================" << std::endl;

    for (int i = 0; i < currentRow; i++) {
        std::cout << dataTable[i].id << "\t"
                  << dataTable[i].age << "\t"
                  << dataTable[i].transport << "\t\t"
                  << dataTable[i].distance << "\t\t"
                  << dataTable[i].emissionFactor << "\t"
                  << dataTable[i].days << std::endl;
    }

    if (currentRow == 0) {
        std::cout << "No data found in the array." << std::endl;
    }
    std::cout << "Total Rows: " << currentRow << std::endl;
}