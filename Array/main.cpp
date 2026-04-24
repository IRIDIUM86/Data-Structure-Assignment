#include <iostream>
#include <string>
#include <chrono>
#include "fileHandler.hpp"
#include "arrayHandler.hpp"
#include "analysisFunctions.hpp"

int main() {
    int size = 0;

    // 1. Load all datasets
    size += loadDataSet("../Datasets/dataset1-cityA.csv");
    size += loadDataSet("../Datasets/dataset2-cityB.csv");
    size += loadDataSet("../Datasets/dataset3-cityC.csv");

    // 2. Verification - Display loaded array data
    std::cout << "\n--- VERIFYING ARRAY DATA ---" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << "Row [" << i + 1 << "] ID: " << userData[i].id
                  << " | Age: " << userData[i].age
                  << " | Transport: " << userData[i].transport
                  << " | Distance: " << userData[i].distance
                  << " | Emission Factor: " << userData[i].emissionFactor << std::endl;
    }
    std::cout << "--- END OF ARRAY (Total: " << size << " rows) ---" << std::endl;

    bool exitProgram = false;

    while (exitProgram == false) {
        std::cout << "\n Action menu:" << std::endl;
        std::cout << "\t 1. Show data summary" << std::endl;
        std::cout << "\t 2. Sort residents" << std::endl;
        std::cout << "\t 3. Search for a resident" << std::endl;
        std::cout << "\t 4. Dataset insight" << std::endl;
        std::cout << "\t 5. Exit" << std::endl;
        std::cout << "Please select an option: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            displaySummary(size);
        }
        else if (choice == 2) {
            displaySortMenu(size);
        }
        else if (choice == 3) {
            std::cout << "\n--- SEARCH OPTIONS ---" << std::endl;
            std::cout << "\t 1. Search by Transport Mode" << std::endl;
            std::cout << "\t 2. Search by Distance Threshold" << std::endl;
            std::cout << "\t 3. Binary Search by Age" << std::endl;
            std::cout << "\t 4. Return to Main Menu" << std::endl;
            std::cout << "Selection: ";
            int searchChoice;
            std::cin >> searchChoice;
            std::cin.ignore(); // Clear input buffer

            if (searchChoice == 1) {
                std::cout << "Enter transport mode (Car/Bus/Bicycle/Walking/School Bus/Carpool): ";
                std::string mode;
                std::getline(std::cin, mode);
                searchByTransport(mode);
            }
            else if (searchChoice == 2) {
                std::cout << "Enter distance threshold (km): ";
                int threshold;
                std::cin >> threshold;
                searchByDistance(threshold);
            }
            else if (searchChoice == 3) {
                std::cout << "Enter target age: ";
                int age;
                std::cin >> age;
                binarySearchAge(age);
            }
        }
        else if (choice == 4) {
            displayDetailedInsight(size);
        }
        else if (choice == 5) {
            exitProgram = true;
            std::cout << "Exiting program. Goodbye!" << std::endl;
        }
        else {
            std::cout << "Option not implemented yet. Please select another option." << std::endl;
        }
    }

    return 0;
}