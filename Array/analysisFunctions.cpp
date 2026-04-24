#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include "analysisFunctions.hpp"

AgeGroupStats group[5];

std::string modes[6] = {"Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};

void displaySummary(int size) {
    std::cout << "\n --- DATA SUMMARY ---" << std::endl;
    // Reset group
    for (int i = 0; i < 5; i++) {
        group[i].residentCount = 0;
        group[i].totalEmissions = 0.0;
        for (int j = 0; j < 6; j++) {
            group[i].transportCounts[j] = 0;
            group[i].emissionCounts[j] = 0.0;
        }
    }
    std::string summary = getSummaryData(size, group);
    std::cout << summary;
}

int getGroupIndex(int age) {
    if (age >= 0 && age <= 17) return 0;     // Children & Teenagers
    if (age >= 18 && age <= 25) return 1;    // University Students / Young Adults
    if (age >= 26 && age <= 45) return 2;    // Working Adults (Early Career)
    if (age >= 46 && age <= 60) return 3;    // Working Adults (Late Career)
    if (age >= 61) return 4;                 // Senior Citizens
    return -1; // Error case
}

std::string getSummaryData(int size, AgeGroupStats group[]) {
    for (int i = 0; i < size; i++) {
        int idx = getGroupIndex(userData[i].age);

        if (idx != -1) { // Only process if age group is valid
            double emissions = userData[i].distance * userData[i].emissionFactor * userData[i].days;
            group[idx].residentCount++;
            group[idx].totalEmissions += emissions;

            if (userData[i].transport == "Car") {
                group[idx].transportCounts[0]++;
                group[idx].emissionCounts[0] += emissions;
            } else if (userData[i].transport == "Bus") {
                group[idx].transportCounts[1]++;
                group[idx].emissionCounts[1] += emissions;
            } else if (userData[i].transport == "Bicycle") {
                group[idx].transportCounts[2]++;
                group[idx].emissionCounts[2] += emissions;
            } else if (userData[i].transport == "Walking") {
                group[idx].transportCounts[3]++;
                group[idx].emissionCounts[3] += emissions;
            } else if (userData[i].transport == "School Bus") {
                group[idx].transportCounts[4]++;
                group[idx].emissionCounts[4] += emissions;
            } else if (userData[i].transport == "Carpool") {
                group[idx].transportCounts[5]++;
                group[idx].emissionCounts[5] += emissions;
            }
        }
    }

    std::string summary = "";

    for (int i = 0; i < 5; i++) {
        // Find the most preferred mode of transport for each age group
        int maxCount = 0;
        int preferredMode = -1;
        for (int j = 0; j < 6; j++) {
            if (group[i].transportCounts[j] > maxCount) {
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

int partition(int low, int high, std::string target) {
    int pivot = low;
    int i = low;
    int j = high;

    while (i < j) {
        // Move i forward based on comparison criteria
        while (i <= high) {
            bool condition = false;
            if (target == "emissions") {
                condition = (userData[i].emissionFactor <= userData[pivot].emissionFactor);
            } else if (target == "age") {
                condition = (userData[i].age <= userData[pivot].age);
            } else if (target == "distance") {
                condition = (userData[i].distance <= userData[pivot].distance);
            }
            if (!condition) break;
            i++;
        }

        // Move j backward based on comparison criteria
        while (j >= low) {
            bool condition = false;
            if (target == "emissions") {
                condition = (userData[j].emissionFactor > userData[pivot].emissionFactor);
            } else if (target == "age") {
                condition = (userData[j].age > userData[pivot].age);
            } else if (target == "distance") {
                condition = (userData[j].distance > userData[pivot].distance);
            }
            if (!condition) break;
            j--;
        }

        if (i < j) {
            std::swap(userData[i], userData[j]);
        }
    }

    std::swap(userData[pivot], userData[j]);
    return j;
}

void quickSort(int low, int high, std::string target) {
    if (low < high) {
        int pi = partition(low, high, target);
        quickSort(low, pi - 1, target);
        quickSort(pi + 1, high, target);
    }
}

void displaySortMenu(int& size) {
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

        quickSort(0, size - 1, target);
        std::cout << "\n--- ARRAY SORTED BY " << target << " ---" << std::endl;
        std::cout << "ID \t| Age \t| Transport \t| Distance \t| Emission Factor \t| Days" << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << userData[i].id << " \t| " << userData[i].age << " \t| "
                      << userData[i].transport << " \t| " << userData[i].distance << " \t| "
                      << userData[i].emissionFactor << " \t| " << userData[i].days << std::endl;
        }
        retry = false; // Exit after sorting
    }
}
