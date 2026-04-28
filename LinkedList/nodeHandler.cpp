#include <string>
#include <iostream>
#include <chrono>
#include <limits>
#include "nodeHelper.hpp"
#include "generalFunctions.hpp"

Residents* addResidents(Residents* head, std::string id, int age, std::string transport, int distance, float emissionFactor, int days, std::string ageGroup) {

    // Allocate memory for new nodes
    Residents* newNode = new Residents(id, age, transport,distance,emissionFactor,days,ageGroup);

    // Set the next node as head
    newNode -> next = head;

    head = newNode;

    // return the newly made node
    return newNode;
}

std::string ageGrouping(int age) {
    if (age >= 0 && age <= 17) {
        return "Children & Teenagers";
    } else if (age >= 18 && age <= 25) {
        return "University Students / Young Adults";
    } else if (age >= 26 && age <= 45) {
        return "Working Adults (Early Career)";
    } else if (age >= 46 && age <= 60) {
        return "Working Adults (Late Career)";
    } else if (age > 61 && age <= 100) {
        return "Senior Citizens";
    }
    else {
        return "Invalid Age";
    }
}

int currentMaxStackDepth = 0;

int countResidents(Residents* head) {
    int count = 0;
    Residents* temp = head;
    while(temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

Residents* getMiddle(Residents* head) {
    if (head == nullptr) return head;
    Residents* slow = head;
    Residents* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

Residents* sortedMerge(Residents* a, Residents* b, std::string target) {
    Residents* result = nullptr;

    if (a == nullptr) return b;
    if (b == nullptr) return a;

    bool condition = false;
    if (target == "emissions") {
        condition = (a->carbonEmissionFactor <= b->carbonEmissionFactor);
    } else if (target == "age") {
        condition = (a->age <= b->age); 
    } else if (target == "distance") {
        condition = (a->dailyDistance <= b->dailyDistance);
    }

    if (condition) {
        result = a;
        result->next = sortedMerge(a->next, b, target);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next, target);
    }
    return result;
}

void mergeSort(Residents** headRef, std::string target, int currentDepth) {
    if (currentDepth > currentMaxStackDepth) {
        currentMaxStackDepth = currentDepth;
    }

    Residents* head = *headRef;

    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Residents* mid = getMiddle(head);
    Residents* left = head;
    Residents* right = mid->next;
    mid->next = nullptr;

    mergeSort(&left, target, currentDepth + 1);
    mergeSort(&right, target, currentDepth + 1);

    *headRef = sortedMerge(left, right, target);
}

Residents* searchMenu(Residents* head) {
    int totalNodes = countResidents(head);

    std::cout << "\n--- SEARCH OPTIONS ---" << std::endl;
    std::cout << "\t 1. Search by Resident ID" << std::endl;
    std::cout << "\t 2. Search by Mode of transport" << std::endl;
    std::cout << "\t 3. Search by Age Group" << std::endl;
    std::cout << "\t 4. Search by Carbon Emission" << std::endl;
    std::cout << "\t 5. Search by Daily Distance" << std::endl;
    std::cout << "\t 6. Return to Main Menu" << std::endl;
    std::cout << "Selection: ";
    
    int choiceSearch;
    std::cin >> choiceSearch;

    if (choiceSearch == 1) {
        std::string id;
        std::cout << "Enter Resident ID: ";
        std::cin >> id;
        
        Residents* temp = head;

        auto start = std::chrono::high_resolution_clock::now();
        bool found = false;
        while (temp != nullptr) {
            if (temp->residentID == id) {
                std::cout << "Resident Found: " << temp->residentID << " | Age: " << temp->age 
                          << " | Transport: " << temp->modeOfTransport 
                          << " | Distance: " << temp->dailyDistance 
                          << " | Emission Factor: " << temp->carbonEmissionFactor 
                          << " | Age Group: " << temp->ageGroup << std::endl;
                found = true;
                break;
            }
            temp = temp->next;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "\nExecution Time: " << duration.count() << " ms" << std::endl;
        printTransparencyReport(totalNodes, 1, "Linear Search by ID");
        
        if (!found) {
            std::cout << "Resident with ID '" << id << "' not found." << std::endl;
        }
    } else if (choiceSearch == 2) {
        std::string transport;
        std::cout << "Enter Mode of Transport (Car, Bus, Bicycle, Walking, School Bus, Carpool): ";
        std::cin >> transport;

        Residents* temp = head;
        bool found = false;
        auto start = std::chrono::high_resolution_clock::now();
        while (temp != nullptr) {
            if (temp->modeOfTransport == transport) {
                std::cout << "Resident Found: " << temp->residentID << " | Age: " << temp->age 
                          << " | Transport: " << temp->modeOfTransport 
                          << " | Distance: " << temp->dailyDistance 
                          << " | Emission Factor: " << temp->carbonEmissionFactor 
                          << " | Age Group: " << temp->ageGroup << std::endl;
                found = true;
            }
            temp = temp->next;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "\nExecution Time: " << duration.count() << " ms" << std::endl;
        printTransparencyReport(totalNodes, 1, "Linear Search by Transport Mode");

        if (!found) {
            std::cout << "No residents found using '" << transport << "'." << std::endl;
        }
    } else if (choiceSearch == 3) {
        std::string ageGroup;
        std::cout << "Enter Age Group: " << std::endl;
        std::cout << "\t 1. 0-17 (Children & Teenagers)" << std::endl;
        std::cout << "\t 2. 18-25 (University Students / Young Adults)" << std::endl;
        std::cout << "\t 3. 26-45 (Working Adults (Early Career))" << std::endl;
        std::cout << "\t 4. 46-60 (Working Adults (Late Career))" << std::endl;
        std::cout << "\t 5. 61+ (Senior Citizens)" << std::endl;
        std::cout << "Selection: ";
        std::cin.ignore();
        std::cin >> ageGroup;

        if (ageGroup == "1") ageGroup = "Children & Teenagers";
        else if (ageGroup == "2") ageGroup = "University Students / Young Adults";
        else if (ageGroup == "3") ageGroup = "Working Adults (Early Career)";
        else if (ageGroup == "4") ageGroup = "Working Adults (Late Career)";
        else if (ageGroup == "5") ageGroup = "Senior Citizens";
        else {
            std::cout << "Invalid choice, returning to main menu." << std::endl;
            return head;
        }

        Residents* temp = head;
        bool found = false;
        auto start = std::chrono::high_resolution_clock::now();
        while (temp != nullptr) {
            if (temp->ageGroup == ageGroup) {
                std::cout << "Resident Found: " << temp->residentID << " | Age: " << temp->age 
                          << " | Transport: " << temp->modeOfTransport 
                          << " | Distance: " << temp->dailyDistance 
                          << " | Emission Factor: " << temp->carbonEmissionFactor 
                          << " | Age Group: " << temp->ageGroup << std::endl;
                found = true;
            }
            temp = temp->next;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "\nExecution Time: " << duration.count() << " ms" << std::endl;
        printTransparencyReport(totalNodes, 1, "Linear Search by Age Group");

        if (!found) {
            std::cout << "No residents found in age group '" << ageGroup << "'." << std::endl;
        }
    } else if (choiceSearch == 4) {
        std::cout << "Enter Carbon Emission Factor (kg CO2 per km): ";
        float emissionFactor;
        if (!(std::cin >> emissionFactor)) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input for carbon emission factor. Please enter a numeric value." << std::endl;
             return head;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        Residents* temp = head;
        bool found = false;
        auto start = std::chrono::high_resolution_clock::now();
        while (temp != nullptr) {
            if (temp->carbonEmissionFactor == emissionFactor) {
                std::cout << "Resident Found: " << temp->residentID << " | Age: " << temp->age 
                          << " | Transport: " << temp->modeOfTransport 
                          << " | Distance: " << temp->dailyDistance 
                          << " | Emission Factor: " << temp->carbonEmissionFactor 
                          << " | Age Group: " << temp->ageGroup << std::endl;
                found = true;
            }
            temp = temp->next;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "\nExecution Time: " << duration.count() << " ms" << std::endl;
        printTransparencyReport(totalNodes, 1, "Linear Search by Carbon Emission");

        if (!found) {
            std::cout << "No residents found with carbon emission factor '" << emissionFactor << "'." << std::endl;
        }
    } else if (choiceSearch == 5) {
        try {
            std::cout << "Enter Daily Distance (km): ";
            float dailyDistance;
                if (!(std::cin >> dailyDistance)) {
                    std::cin.clear(); 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input for daily distance. Please enter a numeric value." << std::endl;
                    return head;
                } else {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

            Residents* temp = head;
            bool found = false;
            auto start = std::chrono::high_resolution_clock::now();
            while (temp != nullptr) {
                if (temp->dailyDistance == dailyDistance) {
                    std::cout << "Resident Found: " << temp->residentID << " | Age: " << temp->age 
                            << " | Transport: " << temp->modeOfTransport 
                            << " | Distance: " << temp->dailyDistance 
                            << " | Emission Factor: " << temp->carbonEmissionFactor 
                            << " | Age Group: " << temp->ageGroup << std::endl;
                    found = true;
                }
                temp = temp->next;
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << "\nExecution Time: " << duration.count() << " ms" << std::endl;
            printTransparencyReport(totalNodes, 1, "Linear Search by Daily Distance");

            if (!found) {
                std::cout << "No residents found with daily distance '" << dailyDistance << "'." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Invalid input for daily distance. Please enter a numeric value." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } 
    else if (choiceSearch == 6) {
        return head;
    } else {
        std::cout << "Invalid choice, please enter a valid option." << std::endl;
    }
    return head;
}

