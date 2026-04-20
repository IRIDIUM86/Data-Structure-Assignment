#include <iostream>
#include "nodeHelper.hpp"
#include "fileHandler.hpp"

int main() {
    // 1. Initialize your head pointer
    Residents* head = nullptr;

    // 2. Load the data (Make sure the CSV filenames are correct)
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
                      << " | Transport: " << temp->modeOfTransport << std::endl;
            
            temp = temp->next; // Move to the next node
        }
    std::cout << "--- END OF LIST (Total: " << count << " nodes) ---" << std::endl;

    std::cout << "Action menu:" << std::endl;
    std::cout << "\t 1. Add a new resident" << std::endl;
    std::cout << "\t 2. Remove a resident" << std::endl;
    std::cout << "\t 3. Search for a resident" << std::endl;
    std::cout << "\t 4. Display all residents" << std::endl;
    std::cout << "\t 5. Exit" << std::endl;
    std::cout << "Please select an option: " << std::endl;
    int choice;
    std::cin >> choice;

    return 0;
}