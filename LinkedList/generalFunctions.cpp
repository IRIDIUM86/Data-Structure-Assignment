#include <iostream>
#include <string>
#include <cstdio>
#include "generalFunctions.hpp"
#include "nodeHelper.hpp"
#include <limits>
#include <chrono>
#include <cmath>

AgeGroupStats group[5];

std::string modes[6] = {"Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};

void printTransparencyReport(int residentCount, int stackFrames, std::string algoName) {
    size_t staticMem = sizeof(Residents) * residentCount;
    size_t dynamicMem = stackFrames * 64; 

    std::cout << "\n--- TOTAL EXECUTION MEMORY (" << algoName << ") ---" << std::endl;
    std::cout << "Data Memory (Nodes):   " << staticMem << " bytes" << std::endl;
    std::cout << "Working Mem (Stack):   " << dynamicMem << " bytes" << std::endl;
    std::cout << "Total Footprint:       " << (staticMem + dynamicMem) << " bytes" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
}

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
    if (category == "Children & Teenagers") {
        return 0;
    }
    if (category == "University Students / Young Adults") {
        return 1;
    }
    if (category == "Working Adults (Early Career) ") {
        return 2;
    }
    if (category == "Working Adults (Late Career)") {
        return 3;
    }
    if (category == "Senior Citizens") {
        return 4;
    }
    return -1; // Error case
}

std::string getSummaryData (Residents* head, AgeGroupStats group[]) {
    Residents* temp = head;

    while (temp != nullptr) {

        int idx = getGroupIndex(temp->ageGroup);

        if (idx != -1) {  // Only process if age group is valid
            double emissions = temp->dailyDistance * temp->carbonEmissionFactor * temp->averageDayPerMonth; // Total weekly emissions for this resident
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
        if (i == 0) {
            groupName = "Age Group: 0-17 (Children & Teenagers)";
        }
        else if (i == 1) {
            groupName = "Age Group: 18-25 (University Students / Young Adults)";
        }
        else if (i == 2) {
            groupName = "Age Group: 26-45 (Working Adults (Early Career))";
        }
        else if (i == 3) {
            groupName = "Age Group: 46-60 (Working Adults (Late Career))";
        }
        else {
            groupName = "Age Group: 61+ (Senior Citizens)";
        }

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

        currentMaxStackDepth = 0;

        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(headRef, target);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "\nExecution Time: " << duration.count() << " ms" << std::endl;

        int totalNodes = countResidents(*headRef);
        printTransparencyReport(totalNodes, currentMaxStackDepth, "Merge Sort");

        std::cout << "\n--- LIST SORTED BY " << target << " ---" << std::endl;
        std::cout << "ID \t| Age \t| Transport \t| Distance \t| Emission Factor \t| Age Group" << std::endl;
        Residents* temp = *headRef;
        while (temp != nullptr) {
            std::cout << temp->residentID << " \t| " 
                      << temp->age << " \t| "
                      << temp->modeOfTransport << " \t| "
                      << temp->dailyDistance << " \t\t| "
                      << temp->carbonEmissionFactor << " \t| "
                      << temp->ageGroup << std::endl;
            temp = temp->next;
        }
        
        std::cout << "Data sorted successfully!" << std::endl;
    }
}

void displayInsight(Residents* head) {
    
    DatasetAgeStats datasetStats[3][5]; // [dataset][ageGroup]
    
    // Collect data
    Residents* temp = head;
    while (temp != nullptr) {
        char datasetId = temp->residentID[0]; // First letter: A, B, or C
        int dataset = (datasetId == 'A') ? 0 : (datasetId == 'B') ? 1 : 2;
        int ageIdx = getGroupIndex(temp->ageGroup);
        
        if (ageIdx != -1 && dataset >= 0 && dataset <= 2) {
            double emissions = temp->dailyDistance * temp->carbonEmissionFactor * temp->averageDayPerMonth;
            datasetStats[dataset][ageIdx].residentCount++;
            datasetStats[dataset][ageIdx].totalEmissions += emissions;
            
            // Track transport modes
            if (temp->modeOfTransport == "Car") {
                datasetStats[dataset][ageIdx].transportCounts[0]++;
                datasetStats[dataset][ageIdx].emissionCounts[0] += emissions;
            } else if (temp->modeOfTransport == "Bus") {
                datasetStats[dataset][ageIdx].transportCounts[1]++;
                datasetStats[dataset][ageIdx].emissionCounts[1] += emissions;
            } else if (temp->modeOfTransport == "Bicycle") {
                datasetStats[dataset][ageIdx].transportCounts[2]++;
                datasetStats[dataset][ageIdx].emissionCounts[2] += emissions;
            } else if (temp->modeOfTransport == "Walking") {
                datasetStats[dataset][ageIdx].transportCounts[3]++;
                datasetStats[dataset][ageIdx].emissionCounts[3] += emissions;
            } else if (temp->modeOfTransport == "School Bus") {
                datasetStats[dataset][ageIdx].transportCounts[4]++;
                datasetStats[dataset][ageIdx].emissionCounts[4] += emissions;
            } else if (temp->modeOfTransport == "Carpool") {
                datasetStats[dataset][ageIdx].transportCounts[5]++;
                datasetStats[dataset][ageIdx].emissionCounts[5] += emissions;
            }
        }
        temp = temp->next;
    }
    
    // Display comparison table
    std::cout << "\n========== DATASET COMPARISON: CARBON EMISSIONS & MODE PREFERENCES ==========" << std::endl;
    
    std::string ageGroupNames[5] = {
        "0-17 (Children & Teenagers)",
        "18-25 (University Students)",
        "26-45 (Early Career)",
        "46-60 (Late Career)",
        "61+ (Senior Citizens)"
    };
    
    std::string datasetNames[3] = {"CityA (Dataset 1)", "CityB (Dataset 2)", "CityC (Dataset 3)"};
    
    // Table 1: Total Emissions by Dataset and Age Group
    std::cout << "\n--- TABLE 1: TOTAL CARBON EMISSIONS (kg CO2) BY DATASET AND AGE GROUP ---" << std::endl;
    std::cout << std::string(110, '-') << std::endl;
    std::cout << "Age Group                          | CityA Dataset1 | CityB Dataset2 | CityC Dataset3 | Highest Contributor" << std::endl;
    std::cout << std::string(110, '-') << std::endl;
    
    for (int age = 0; age < 5; age++) {
        double emissions[3] = {
            datasetStats[0][age].totalEmissions,
            datasetStats[1][age].totalEmissions,
            datasetStats[2][age].totalEmissions
        };
        
        int maxDataset = 0;
        double maxEmissions = emissions[0];
        for (int d = 1; d < 3; d++) {
            if (emissions[d] > maxEmissions) {
                maxEmissions = emissions[d];
                maxDataset = d;
            }
        }
        
        char buffer[120];
        std::sprintf(buffer, "%-35s | %14.1f | %14.1f | %14.1f | %s (%.1f kg CO2)\n",
            ageGroupNames[age].c_str(),
            emissions[0], emissions[1], emissions[2],
            datasetNames[maxDataset].c_str(), maxEmissions);
        std::cout << buffer;
    }
    std::cout << std::string(110, '-') << std::endl;
    
    // Table 2: Transport Mode Preferences by Dataset and Age Group
    std::cout << "\n--- TABLE 2: TRANSPORT MODE PREFERENCES BY DATASET AND AGE GROUP ---" << std::endl;
    std::cout << "(Count of residents using each transport mode)" << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    
    for (int age = 0; age < 5; age++) {
        std::cout << "\nAge Group: " << ageGroupNames[age] << std::endl;
        std::cout << std::string(100, '-') << std::endl;
        std::cout << "Transport Mode      | CityA | CityB | CityC | Total | Most Preferred" << std::endl;
        std::cout << std::string(100, '-') << std::endl;
        
        for (int mode = 0; mode < 6; mode++) {
            int counts[3] = {
                datasetStats[0][age].transportCounts[mode],
                datasetStats[1][age].transportCounts[mode],
                datasetStats[2][age].transportCounts[mode]
            };
            int total = counts[0] + counts[1] + counts[2];
            
            int maxDataset = 0;
            if (counts[1] > counts[maxDataset]) maxDataset = 1;
            if (counts[2] > counts[maxDataset]) maxDataset = 2;
            
            char buffer[100];
            std::sprintf(buffer, "%-20s | %5d | %5d | %5d | %5d | %s\n",
                modes[mode].c_str(),
                counts[0], counts[1], counts[2], total,
                (total > 0) ? datasetNames[maxDataset].c_str() : "N/A");
            std::cout << buffer;
        }
        std::cout << std::string(100, '-') << std::endl;
    }
    
    // Table 3: Bicycle vs Car Preference Analysis
    std::cout << "\n--- TABLE 3: BICYCLE VS CAR PREFERENCES BY AGE GROUP ---" << std::endl;
    std::cout << std::string(110, '-') << std::endl;
    std::cout << "Age Group\t\t\t| Bicycles (A) | Bicycles (B) | Bicycles (C) | Cars (A) | Cars (B) | Cars (C) | Key Insight" << std::endl;
    std::cout << std::string(110, '-') << std::endl;
    
    for (int age = 0; age < 5; age++) {
        int bicycleA = datasetStats[0][age].transportCounts[2];
        int bicycleB = datasetStats[1][age].transportCounts[2];
        int bicycleC = datasetStats[2][age].transportCounts[2];
        int carA = datasetStats[0][age].transportCounts[0];
        int carB = datasetStats[1][age].transportCounts[0];
        int carC = datasetStats[2][age].transportCounts[0];
        
        std::string insight = "";
        if (bicycleA + bicycleB + bicycleC > carA + carB + carC) {
            insight = "Prefers Bicycles";
        } else if (carA + carB + carC > bicycleA + bicycleB + bicycleC) {
            insight = "Prefers Cars";
        } else {
            insight = "Balanced";
        }
        
        char buffer[120];
        std::sprintf(buffer, "%-35s | %12d | %12d | %12d | %8d | %8d | %8d | %s\n",
            ageGroupNames[age].c_str(),
            bicycleA, bicycleB, bicycleC,
            carA, carB, carC,
            insight.c_str());
        std::cout << buffer;
    }
    std::cout << std::string(110, '-') << std::endl;
    
    // Summary Analysis
    std::cout << "\n--- ANALYSIS SUMMARY ---" << std::endl;
    
    double totalEmissions[3] = {0.0, 0.0, 0.0};
    int totalResidents[3] = {0, 0, 0};
    for (int d = 0; d < 3; d++) {
        for (int age = 0; age < 5; age++) {
            totalEmissions[d] += datasetStats[d][age].totalEmissions;
            totalResidents[d] += datasetStats[d][age].residentCount;
        }
    }
    
    std::cout << "\n1. HIGHEST EMISSION CONTRIBUTORS BY AGE GROUP:" << std::endl;
    for (int age = 0; age < 5; age++) {
        double maxE = datasetStats[0][age].totalEmissions;
        int maxD = 0;
        for (int d = 1; d < 3; d++) {
            if (datasetStats[d][age].totalEmissions > maxE) {
                maxE = datasetStats[d][age].totalEmissions;
                maxD = d;
            }
        }
        std::cout << "   Age " << ageGroupNames[age] << ": " 
                  << datasetNames[maxD] << " with " << maxE << " kg CO2" << std::endl;
    }
    
    std::cout << "\n2. BICYCLE PREFERENCE BY AGE GROUP:" << std::endl;
    for (int age = 0; age < 5; age++) {
        int bicycles[3] = {
            datasetStats[0][age].transportCounts[2],
            datasetStats[1][age].transportCounts[2],
            datasetStats[2][age].transportCounts[2]
        };
        int maxB = bicycles[0];
        int maxD = 0;
        for (int d = 1; d < 3; d++) {
            if (bicycles[d] > maxB) {
                maxB = bicycles[d];
                maxD = d;
            }
        }
        std::cout << "   Age " << ageGroupNames[age] << ": Most cyclists in " 
                  << datasetNames[maxD] << " (" << maxB << " cyclists)" << std::endl;
    }
    
    std::cout << "\n3. CAR USAGE BY AGE GROUP:" << std::endl;
    for (int age = 0; age < 5; age++) {
        int cars[3] = {
            datasetStats[0][age].transportCounts[0],
            datasetStats[1][age].transportCounts[0],
            datasetStats[2][age].transportCounts[0]
        };
        int maxC = cars[0];
        int maxD = 0;
        for (int d = 1; d < 3; d++) {
            if (cars[d] > maxC) {
                maxC = cars[d];
                maxD = d;
            }
        }
        std::cout << "   Age " << ageGroupNames[age] << ": Most car users in " 
                  << datasetNames[maxD] << " (" << maxC << " car users)" << std::endl;
    }
    
    std::cout << "\n4. OVERALL DATASET STATISTICS:" << std::endl;
    for (int d = 0; d < 3; d++) {
        double avgEmissionsPerResident = (totalResidents[d] > 0) ? totalEmissions[d] / totalResidents[d] : 0;
        std::cout << "   " << datasetNames[d] << ": " << totalResidents[d] 
                  << " residents, Total Emissions: " << totalEmissions[d] 
                  << " kg CO2, Avg: " << avgEmissionsPerResident << " kg CO2/resident" << std::endl;
    }
    
    std::cout << "\n" << std::string(110, '=') << std::endl;
}