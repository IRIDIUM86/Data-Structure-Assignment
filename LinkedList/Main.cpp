#include <iostream>
#include "nodeHelper.hpp"
#include "fileHandler.hpp"
#include "generalFunctions.hpp"

int main() {

    Residents* head = nullptr;

    head = loadDataSet("../Datasets/dataset1-cityA.csv", head);
    head = loadDataSet("../Datasets/dataset2-cityB.csv", head);
    head = loadDataSet("../Datasets/dataset3-cityC.csv", head);

    // 3. Simple verification
    std::cout << "\n--- VERIFYING LINKED LIST DATA ---" << std::endl;
        Residents* temp = head;
        int count = 0;

        while (temp != nullptr) {
            count++;
            std::cout << "Node [" << count << "] ID: " << temp->residentID 
                      << " | Age: " << temp->age 
                      << " | Transport: " << temp->modeOfTransport
                      << " | Age Group: " << temp->ageGroup << std::endl;
            
            temp = temp->next; // Move to the next node
        }
    std::cout << "--- END OF LIST (Total: " << count << " nodes) ---" << std::endl;

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
        else if (choice == 5) {
            exitProgram = true;
        }
         else {
            std::cout << "Option not implemented yet. Please select another option." << std::endl;
         }
    }

    return 0;
}