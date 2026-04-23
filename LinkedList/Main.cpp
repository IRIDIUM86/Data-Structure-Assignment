#include <iostream>
#include <chrono>
#include "nodeHelper.hpp"
#include "fileHandler.hpp"
#include "generalFunctions.hpp"

int main() {

    Residents* head = nullptr;

    std::cout << "--- LOADING DATASETS ---" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    head = loadDataSet("../Datasets/dataset1-cityA.csv", head);
    head = loadDataSet("../Datasets/dataset2-cityB.csv", head);
    head = loadDataSet("../Datasets/dataset3-cityC.csv", head);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start; 
    std::cout << "Execution Time: " << duration.count() << " ms" << std::endl;

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
            displaySummary(head);
        }
        else if (choice == 2){
            displaySortMenu(&head);
        }
        else if (choice == 3) {
            searchMenu(head);
        }
        else if (choice == 5) {
            exitProgram = true;
        }
         else {
            std::cout << "Option not implemented yet. Please select another option." << std::endl;
         }
    }

    return 0;
}