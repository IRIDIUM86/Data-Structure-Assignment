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

void displayDetailedInsight(int size) {
    
    AgeGroupStats ageStats[5]; // [ageGroup]
    
    // Initialize age stats
    for (int i = 0; i < 5; i++) {
        ageStats[i].residentCount = 0;
        ageStats[i].totalEmissions = 0.0;
        for (int j = 0; j < 6; j++) {
            ageStats[i].transportCounts[j] = 0;
            ageStats[i].emissionCounts[j] = 0.0;
        }
    }
    
    // Collect data
    for (int i = 0; i < size; i++) {
        int ageIdx = getGroupIndex(userData[i].age);
        
        if (ageIdx != -1) {
            double emissions = userData[i].distance * userData[i].emissionFactor * userData[i].days;
            ageStats[ageIdx].residentCount++;
            ageStats[ageIdx].totalEmissions += emissions;
            
            // Track transport modes
            if (userData[i].transport == "Car") {
                ageStats[ageIdx].transportCounts[0]++;
                ageStats[ageIdx].emissionCounts[0] += emissions;
            } else if (userData[i].transport == "Bus") {
                ageStats[ageIdx].transportCounts[1]++;
                ageStats[ageIdx].emissionCounts[1] += emissions;
            } else if (userData[i].transport == "Bicycle") {
                ageStats[ageIdx].transportCounts[2]++;
                ageStats[ageIdx].emissionCounts[2] += emissions;
            } else if (userData[i].transport == "Walking") {
                ageStats[ageIdx].transportCounts[3]++;
                ageStats[ageIdx].emissionCounts[3] += emissions;
            } else if (userData[i].transport == "School Bus") {
                ageStats[ageIdx].transportCounts[4]++;
                ageStats[ageIdx].emissionCounts[4] += emissions;
            } else if (userData[i].transport == "Carpool") {
                ageStats[ageIdx].transportCounts[5]++;
                ageStats[ageIdx].emissionCounts[5] += emissions;
            }
        }
    }
    
    // Display comparison table
    std::cout << "\n========== COMPREHENSIVE EMISSIONS & TRANSPORT MODE ANALYSIS ==========" << std::endl;
    
    std::string ageGroupNames[5] = {
        "0-17 (Children & Teenagers)",
        "18-25 (University Students)",
        "26-45 (Early Career)",
        "46-60 (Late Career)",
        "61+ (Senior Citizens)"
    };
    
    // Table 1: Total Emissions by Age Group
    std::cout << "\n--- TABLE 1: TOTAL CARBON EMISSIONS (kg CO2) BY AGE GROUP ---" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    std::cout << "Age Group                          | Total Emissions | Resident Count | Avg per Resident" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (int age = 0; age < 5; age++) {
        double avgPerResident = (ageStats[age].residentCount > 0) ? 
            ageStats[age].totalEmissions / ageStats[age].residentCount : 0;
        
        char buffer[120];
        std::sprintf(buffer, "%-35s | %15.1f | %14d | %16.1f\n",
            ageGroupNames[age].c_str(),
            ageStats[age].totalEmissions,
            ageStats[age].residentCount,
            avgPerResident);
        std::cout << buffer;
    }
    std::cout << std::string(80, '-') << std::endl;
    
    // Table 2: Transport Mode Preferences by Age Group
    std::cout << "\n--- TABLE 2: TRANSPORT MODE PREFERENCES BY AGE GROUP ---" << std::endl;
    std::cout << "(Count of residents using each transport mode)" << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    
    for (int age = 0; age < 5; age++) {
        std::cout << "\nAge Group: " << ageGroupNames[age] << std::endl;
        std::cout << std::string(100, '-') << std::endl;
        std::cout << "Transport Mode      | Count | Emissions (kg CO2) | Avg Emission/Person | Preference" << std::endl;
        std::cout << std::string(100, '-') << std::endl;
        
        for (int mode = 0; mode < 6; mode++) {
            int count = ageStats[age].transportCounts[mode];
            double totalEmissions = ageStats[age].emissionCounts[mode];
            double avgEmissionsPerPerson = (count > 0) ? totalEmissions / count : 0;
            
            // Determine if this is the most preferred mode
            int maxCount = 0;
            for (int m = 0; m < 6; m++) {
                if (ageStats[age].transportCounts[m] > maxCount) {
                    maxCount = ageStats[age].transportCounts[m];
                }
            }
            std::string preferenceMarker = (count == maxCount && count > 0) ? "★ MOST USED" : "";
            
            char buffer[120];
            std::sprintf(buffer, "%-20s | %5d | %18.1f | %19.1f | %s\n",
                modes[mode].c_str(),
                count,
                totalEmissions,
                avgEmissionsPerPerson,
                preferenceMarker.c_str());
            std::cout << buffer;
        }
        std::cout << std::string(100, '-') << std::endl;
    }
    
    // Table 3: Bicycle vs Car Preference Analysis
    std::cout << "\n--- TABLE 3: BICYCLE VS CAR PREFERENCES BY AGE GROUP ---" << std::endl;
    std::cout << std::string(110, '-') << std::endl;
    std::cout << "Age Group                          | Bicycles | Cars | Preference | Car Emissions | Bicycle Emissions" << std::endl;
    std::cout << std::string(110, '-') << std::endl;
    
    for (int age = 0; age < 5; age++) {
        int bicycles = ageStats[age].transportCounts[2];
        int cars = ageStats[age].transportCounts[0];
        double carEmissions = ageStats[age].emissionCounts[0];
        double bicycleEmissions = ageStats[age].emissionCounts[2];
        
        std::string preference = "";
        if (bicycles > cars) {
            preference = "Prefers Bicycles";
        } else if (cars > bicycles) {
            preference = "Prefers Cars";
        } else if (bicycles > 0 || cars > 0) {
            preference = "Balanced";
        } else {
            preference = "No Data";
        }
        
        char buffer[150];
        std::sprintf(buffer, "%-35s | %8d | %5d | %-10s | %13.1f | %17.1f\n",
            ageGroupNames[age].c_str(),
            bicycles, cars,
            preference.c_str(),
            carEmissions,
            bicycleEmissions);
        std::cout << buffer;
    }
    std::cout << std::string(110, '-') << std::endl;
    
    // Table 4: Distance vs Emissions Correlation
    std::cout << "\n--- TABLE 4: DISTANCE ANALYSIS BY AGE GROUP ---" << std::endl;
    std::cout << std::string(90, '-') << std::endl;
    std::cout << "Age Group                          | Avg Distance (km) | Total Distance (km)" << std::endl;
    std::cout << std::string(90, '-') << std::endl;
    
    for (int age = 0; age < 5; age++) {
        int totalDistance = 0;
        int count = 0;
        
        for (int i = 0; i < size; i++) {
            if (getGroupIndex(userData[i].age) == age) {
                totalDistance += userData[i].distance;
                count++;
            }
        }
        
        double avgDistance = (count > 0) ? (double)totalDistance / count : 0;
        
        char buffer[120];
        std::sprintf(buffer, "%-35s | %17.1f | %19d\n",
            ageGroupNames[age].c_str(),
            avgDistance,
            totalDistance);
        std::cout << buffer;
    }
    std::cout << std::string(90, '-') << std::endl;
    
    // Summary Analysis
    std::cout << "\n--- ANALYSIS SUMMARY ---" << std::endl;
    
    double totalEmissionsOverall = 0.0;
    int totalResidentsOverall = 0;
    for (int age = 0; age < 5; age++) {
        totalEmissionsOverall += ageStats[age].totalEmissions;
        totalResidentsOverall += ageStats[age].residentCount;
    }
    
    std::cout << "\n1. HIGHEST EMISSION CONTRIBUTORS BY AGE GROUP:" << std::endl;
    for (int age = 0; age < 5; age++) {
        int maxModeIdx = 0;
        double maxEmissions = ageStats[age].emissionCounts[0];
        for (int m = 1; m < 6; m++) {
            if (ageStats[age].emissionCounts[m] > maxEmissions) {
                maxEmissions = ageStats[age].emissionCounts[m];
                maxModeIdx = m;
            }
        }
        std::cout << "   Age " << ageGroupNames[age] << ": " 
                  << modes[maxModeIdx] << " with " << maxEmissions << " kg CO2" << std::endl;
    }
    
    std::cout << "\n2. BICYCLE PREFERENCE BY AGE GROUP:" << std::endl;
    for (int age = 0; age < 5; age++) {
        int bicycles = ageStats[age].transportCounts[2];
        std::cout << "   Age " << ageGroupNames[age] << ": " 
                  << bicycles << " cyclists" << std::endl;
    }
    
    std::cout << "\n3. CAR USAGE BY AGE GROUP:" << std::endl;
    for (int age = 0; age < 5; age++) {
        int cars = ageStats[age].transportCounts[0];
        std::cout << "   Age " << ageGroupNames[age] << ": " 
                  << cars << " car users" << std::endl;
    }
    
    std::cout << "\n4. OVERALL DATASET STATISTICS:" << std::endl;
    double avgEmissionsPerResident = (totalResidentsOverall > 0) ? totalEmissionsOverall / totalResidentsOverall : 0;
    std::cout << "   Total Residents: " << totalResidentsOverall << std::endl;
    std::cout << "   Total Emissions: " << totalEmissionsOverall << " kg CO2" << std::endl;
    std::cout << "   Average Emissions per Resident: " << avgEmissionsPerResident << " kg CO2/resident" << std::endl;
    
    std::cout << "\n5. MOST USED TRANSPORT MODE BY AGE GROUP:" << std::endl;
    for (int age = 0; age < 5; age++) {
        int maxModeIdx = 0;
        int maxCount = ageStats[age].transportCounts[0];
        for (int m = 1; m < 6; m++) {
            if (ageStats[age].transportCounts[m] > maxCount) {
                maxCount = ageStats[age].transportCounts[m];
                maxModeIdx = m;
            }
        }
        std::cout << "   Age " << ageGroupNames[age] << ": " 
                  << modes[maxModeIdx] << " (" << maxCount << " users)" << std::endl;
    }
    
    std::cout << "\n" << std::string(110, '=') << std::endl;
}
