#include <iostream>
#include <string>
#include <cstdio>
#include "generalFunctions.hpp"

AgeGroupStats group[5];

std::string modes[6] = {"Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};

void displaySummary(Residents* head){
    std::cout << "\n --- DATA SUMMARY ---" << std::endl;
    // Reset group
    for(int i=0; i<5; i++) {
        group[i].residentCount = 0;
        group[i].totalEmissions = 0.0;
        for(int j=0; j<6; j++) {
            group[i].transportCounts[j] = 0;
            group[i].emissionCounts[j] = 0.0;
        }
    }
    std::string summary = getSummaryData(head, group);
    std::cout << summary;
};

int getGroupIndex(std::string category) {
    if (category == "Children & Teenagers") return 0;
    if (category == "University Students / Young Adults") return 1;
    if (category == "Working Adults (Early Career) ") return 2;
    if (category == "Working Adults (Late Career)") return 3;
    if (category == "Senior Citizens") return 4;
    return -1; // Error case
}

std::string getSummaryData (Residents* head, AgeGroupStats group[]) {
    Residents* temp = head;

    while (temp != nullptr) {

        int idx = getGroupIndex(temp->ageGroup);

        if (idx != -1) {  // Only process if age group is valid
            double emissions = temp->dailyDistance * temp->carbonEmissionFactor;
            group[idx].residentCount++;
            group[idx].totalEmissions += emissions;

        if (temp->modeOfTransport == "Car") {
            group[idx].transportCounts[0]++;
            group[idx].emissionCounts[0] += emissions;
        } else if (temp->modeOfTransport == "Bus") {
            group[idx].transportCounts[1]++;
            group[idx].emissionCounts[1] += emissions;
        } else if (temp->modeOfTransport == "Bicycle") {
            group[idx].transportCounts[2]++;
            group[idx].emissionCounts[2] += emissions;
        } else if (temp->modeOfTransport == "Walking") {
            group[idx].transportCounts[3]++;
            group[idx].emissionCounts[3] += emissions;
        } else if (temp->modeOfTransport == "School Bus") {
            group[idx].transportCounts[4]++;
            group[idx].emissionCounts[4] += emissions;
        } else if (temp->modeOfTransport == "Carpool") {
            group[idx].transportCounts[5]++;
            group[idx].emissionCounts[5] += emissions;
        }
        }
        temp = temp->next;
    }

    std::string summary = "";

    for (int i = 0; i < 5; i++)
    {
        // Find the most preferred mode of transport for each age group
        int maxCount = 0;
        int preferredMode = -1;
        for (int j = 0; j < 6; j++)
        {
            if (group[i].transportCounts[j] > maxCount)
            {
                maxCount = group[i].transportCounts[j];
                preferredMode = j;
            }
        }
        std::string groupName;
        if (i == 0) groupName = "Age Group: 0-17 (Children & Teenagers)";
        else if (i == 1) groupName = "Age Group: 18-25 (University Students / Young Adults)";
        else if (i == 2) groupName = "Age Group: 26-45 (Working Adults (Early Career))";
        else if (i == 3) groupName = "Age Group: 46-60 (Working Adults (Late Career))";
        else groupName = "Age Group: 61+ (Senior Citizens)";

        summary += "\n" + groupName + "\n";
        summary += "-------------------------------------------\n";
        summary += "Mode of Transport         Count   Total Emission (kg CO2)   Average per Resident\n";
        
        for (int j = 0; j < 6; j++) {
            if (group[i].transportCounts[j] > 0) {
                double avgPerResident = group[i].emissionCounts[j] / group[i].transportCounts[j];
                char buffer[100];
                std::sprintf(buffer, "%-25s %-7d %-23.1f %.1f\n", 
                    modes[j].c_str(), 
                    group[i].transportCounts[j], 
                    group[i].emissionCounts[j], 
                    avgPerResident);
                summary += buffer;
            }
        }
        summary += "-------------------------------------------\n";
        summary += "Total Emission for Age Group: " + std::to_string(group[i].totalEmissions) + " kg CO2\n";
    }
    
    return summary;
}
Residents* getMiddle(Residents* head) {
    if (head == nullptr) return head;
    Residents* slow = head;
    Residents* fast = head->next; // Offset fast by one to get the node BEFORE the split

    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

// --- FIX 2: Matched target strings to lowercase and fixed pointer logic ---
Residents* sortedMerge(Residents* a, Residents* b, std::string target) {
    Residents* result = nullptr;

    if (a == nullptr) return b;
    if (b == nullptr) return a;

    bool condition = false;
    // CRITICAL: Strings here must match exactly what you pass in displaySortMenu
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

void mergeSort(Residents** headRef, std::string target) {
    Residents* head = *headRef;

    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Residents* mid = getMiddle(head);
    Residents* left = head;
    Residents* right = mid->next;
    mid->next = nullptr;

    mergeSort(&left, target);
    mergeSort(&right, target);

    *headRef = sortedMerge(left, right, target);
    
}

void displaySortMenu(Residents** headRef) { 
    bool retry = true;
    while (retry) {
        std::cout << "\n--- SORTING OPTIONS ---" << std::endl;
        std::cout << "\t 1. Sort by Age (Ascending)" << std::endl;
        std::cout << "\t 2. Sort by Carbon Emissions (Ascending)" << std::endl;
        std::cout << "\t 3. Sort by Daily Distance (Ascending)" << std::endl;
        std::cout << "\t 4. Return to Main Menu" << std::endl;
        std::cout << "Selection: ";
        
        int choiceSort;
        if (!(std::cin >> choiceSort)) return; // Input safety

        std::string target = "";
        if (choiceSort == 1) {
            target = "age";
        } else if (choiceSort == 2) {
            target = "emissions";
        } else if (choiceSort == 3) {
            target = "distance";
        } else {
            return;
            std::cout << "Invalid choice, returning to main menu." << std::endl;
        }

        mergeSort(headRef, target);
        std::cout << "\n--- LIST SORTED BY " << target << " ---" << std::endl;
        std::cout << "ID | Age | Transport | Distance | Emission Factor | Age Group" << std::endl;
        Residents* temp = *headRef;
        while (temp != nullptr) {
            std::cout << temp->residentID << " | " 
                      << temp->age << " | "
                      << temp->modeOfTransport << " | "
                      << temp->dailyDistance << " | "
                      << temp->carbonEmissionFactor << " | "
                      << temp->ageGroup << std::endl;
            temp = temp->next;
        }
        
        std::cout << "Data sorted successfully!" << std::endl;
    }
}