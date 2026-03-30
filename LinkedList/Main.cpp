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

    return 0;
}