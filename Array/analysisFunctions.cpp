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
    
    // Create 2D array: [3 datasets][5 age groups]
    AgeGroupStats datasetAgeStats[3][5];
    
    // Initialize all stats
    for (int d = 0; d < 3; d++) {
        for (int a = 0; a < 5; a++) {
            datasetAgeStats[d][a].residentCount = 0;
            datasetAgeStats[d][a].totalEmissions = 0.0;
            for (int j = 0; j < 6; j++) {
                datasetAgeStats[d][a].transportCounts[j] = 0;
                datasetAgeStats[d][a].emissionCounts[j] = 0.0;
            }
        }
    }
    
    // Collect and organize data by dataset and age group
    for (int i = 0; i < size; i++) {
        int ageIdx = getGroupIndex(userData[i].age);
        int datasetId = userData[i].datasetId;
        
        if (ageIdx != -1 && datasetId >= 0 && datasetId < 3) {
            double emissions = userData[i].distance * userData[i].emissionFactor * userData[i].days;
            datasetAgeStats[datasetId][ageIdx].residentCount++;
            datasetAgeStats[datasetId][ageIdx].totalEmissions += emissions;
            
            // Track transport modes
            int transportIdx = -1;
            if (userData[i].transport == "Car") transportIdx = 0;
            else if (userData[i].transport == "Bus") transportIdx = 1;
            else if (userData[i].transport == "Bicycle") transportIdx = 2;
            else if (userData[i].transport == "Walking") transportIdx = 3;
            else if (userData[i].transport == "School Bus") transportIdx = 4;
            else if (userData[i].transport == "Carpool") transportIdx = 5;
            
            if (transportIdx != -1) {
                datasetAgeStats[datasetId][ageIdx].transportCounts[transportIdx]++;
                datasetAgeStats[datasetId][ageIdx].emissionCounts[transportIdx] += emissions;
            }
        }
    }
    
    std::string datasetNames[3] = {"CityA (Dataset 1)", "CityB (Dataset 2)", "CityC (Dataset 3)"};
    std::string datasetShortNames[3] = {"CityA", "CityB", "CityC"};
    std::string ageGroupNames[5] = {
        "0-17 (Children & Teenagers)",
        "18-25 (University Students)",
        "26-45 (Early Career)",
        "46-60 (Late Career)",
        "61+ (Senior Citizens)"
    };
    
    std::cout << "\n========== DATASET COMPARISON: CARBON EMISSIONS & MODE PREFERENCES ==========" << std::endl;
    
    // TABLE 1: Total Emissions by Dataset and Age Group
    std::cout << "\n--- TABLE 1: TOTAL CARBON EMISSIONS (kg CO2) BY DATASET AND AGE GROUP ---" << std::endl;
    std::cout << std::string(110, '-') << std::endl;
    std::cout << "Age Group                            | CityA Dataset1 | CityB Dataset2 | CityC Dataset3 | Highest Contributor" << std::endl;
    std::cout << std::string(110, '-') << std::endl;
    
    for (int age = 0; age < 5; age++) {
        double cityAEmissions = datasetAgeStats[0][age].totalEmissions;
        double cityBEmissions = datasetAgeStats[1][age].totalEmissions;
        double cityCEmissions = datasetAgeStats[2][age].totalEmissions;
        
        // Find highest contributor
        std::string highestCity = "CityA";
        double maxEmissions = cityAEmissions;
        if (cityBEmissions > maxEmissions) {
            highestCity = "CityB";
            maxEmissions = cityBEmissions;
        }
        if (cityCEmissions > maxEmissions) {
            highestCity = "CityC";
            maxEmissions = cityCEmissions;
        }
        
        std::string datasetSuffix = "";
        if (highestCity == "CityA") datasetSuffix = " (Dataset 1)";
        else if (highestCity == "CityB") datasetSuffix = " (Dataset 2)";
        else datasetSuffix = " (Dataset 3)";
        
        char buffer[150];
        std::sprintf(buffer, "%-35s | %14.1f | %14.1f | %14.1f | %s (%.1f kg CO2)\n",
            ageGroupNames[age].c_str(),
            cityAEmissions,
            cityBEmissions,
            cityCEmissions,
            (highestCity + datasetSuffix).c_str(),
            maxEmissions);
        std::cout << buffer;
    }
    std::cout << std::string(110, '-') << std::endl;
    
    // TABLE 2: Transport Mode Preferences by Dataset and Age Group
    std::cout << "\n--- TABLE 2: TRANSPORT MODE PREFERENCES BY DATASET AND AGE GROUP ---" << std::endl;
    std::cout << "(Count of residents using each transport mode)" << std::endl;
    std::cout << std::string(110, '-') << std::endl;
    
    for (int age = 0; age < 5; age++) {
        std::cout << "\nAge Group: " << ageGroupNames[age] << std::endl;
        std::cout << std::string(110, '-') << std::endl;
        std::cout << "Transport Mode      | CityA | CityB | CityC | Total | Most Preferred" << std::endl;
        std::cout << std::string(110, '-') << std::endl;
        
        for (int mode = 0; mode < 6; mode++) {
            int cityACount = datasetAgeStats[0][age].transportCounts[mode];
            int cityBCount = datasetAgeStats[1][age].transportCounts[mode];
            int cityCCount = datasetAgeStats[2][age].transportCounts[mode];
            int totalCount = cityACount + cityBCount + cityCCount;
            
            // Find most preferred dataset for this transport mode
            std::string mostPreferred = "N/A";
            if (totalCount > 0) {
                if (cityACount >= cityBCount && cityACount >= cityCCount && cityACount > 0) {
                    mostPreferred = "CityA (Dataset 1)";
                } else if (cityBCount >= cityACount && cityBCount >= cityCCount && cityBCount > 0) {
                    mostPreferred = "CityB (Dataset 2)";
                } else if (cityCCount > 0) {
                    mostPreferred = "CityC (Dataset 3)";
                }
            }
            
            char buffer[150];
            std::sprintf(buffer, "%-20s | %5d | %5d | %5d | %5d | %s\n",
                modes[mode].c_str(),
                cityACount,
                cityBCount,
                cityCCount,
                totalCount,
                mostPreferred.c_str());
            std::cout << buffer;
        }
        std::cout << std::string(110, '-') << std::endl;
    }
    
    // TABLE 3: Bicycle vs Car Preferences by Age Group
    std::cout << "\n--- TABLE 3: BICYCLE VS CAR PREFERENCES BY AGE GROUP ---" << std::endl;
    std::cout << std::string(110, '-') << std::endl;
    std::cout << "Age Group                       | Bicycles (A) | Bicycles (B) | Bicycles (C) | Cars (A) | Cars (B) | Cars (C) | Key Insight" << std::endl;
    std::cout << std::string(110, '-') << std::endl;
    
    for (int age = 0; age < 5; age++) {
        int bicyclesA = datasetAgeStats[0][age].transportCounts[2];
        int bicyclesB = datasetAgeStats[1][age].transportCounts[2];
        int bicyclesC = datasetAgeStats[2][age].transportCounts[2];
        int carsA = datasetAgeStats[0][age].transportCounts[0];
        int carsB = datasetAgeStats[1][age].transportCounts[0];
        int carsC = datasetAgeStats[2][age].transportCounts[0];
        
        int totalBicycles = bicyclesA + bicyclesB + bicyclesC;
        int totalCars = carsA + carsB + carsC;
        
        std::string insight = "";
        if (totalBicycles > 0 || totalCars > 0) {
            if (totalBicycles > totalCars) {
                insight = "Prefers Bicycles";
            } else if (totalCars > totalBicycles) {
                insight = "Prefers Cars";
            } else {
                insight = "Balanced";
            }
        } else {
            insight = "Balanced";
        }
        
        char buffer[180];
        std::sprintf(buffer, "%-31s | %12d | %12d | %12d | %8d | %8d | %8d | %s\n",
            ageGroupNames[age].c_str(),
            bicyclesA, bicyclesB, bicyclesC,
            carsA, carsB, carsC,
            insight.c_str());
        std::cout << buffer;
    }
    std::cout << std::string(110, '-') << std::endl;
    
    // ANALYSIS SUMMARY
    std::cout << "\n--- ANALYSIS SUMMARY ---" << std::endl;
    
    std::cout << "\n1. HIGHEST EMISSION CONTRIBUTORS BY AGE GROUP:" << std::endl;
    for (int age = 0; age < 5; age++) {
        double maxEmissions = datasetAgeStats[0][age].totalEmissions;
        std::string maxDataset = "CityA (Dataset 1)";
        
        for (int d = 1; d < 3; d++) {
            if (datasetAgeStats[d][age].totalEmissions > maxEmissions) {
                maxEmissions = datasetAgeStats[d][age].totalEmissions;
                maxDataset = datasetNames[d];
            }
        }
        
        char buffer[150];
        std::sprintf(buffer, "   Age %s: %s with %.2f kg CO2\n",
            ageGroupNames[age].c_str(),
            maxDataset.c_str(),
            maxEmissions);
        std::cout << buffer;
    }
    
    std::cout << "\n2. BICYCLE PREFERENCE BY AGE GROUP:" << std::endl;
    for (int age = 0; age < 5; age++) {
        int maxBicycles = 0;
        std::string maxDataset = "CityA";
        
        for (int d = 0; d < 3; d++) {
            if (datasetAgeStats[d][age].transportCounts[2] > maxBicycles) {
                maxBicycles = datasetAgeStats[d][age].transportCounts[2];
                maxDataset = datasetNames[d];
            }
        }
        
        char buffer[150];
        std::sprintf(buffer, "   Age %s: Most cyclists in %s (%d cyclists)\n",
            ageGroupNames[age].c_str(),
            maxDataset.c_str(),
            maxBicycles);
        std::cout << buffer;
    }
    
    std::cout << "\n3. CAR USAGE BY AGE GROUP:" << std::endl;
    for (int age = 0; age < 5; age++) {
        int maxCars = 0;
        std::string maxDataset = "CityA";
        
        for (int d = 0; d < 3; d++) {
            if (datasetAgeStats[d][age].transportCounts[0] > maxCars) {
                maxCars = datasetAgeStats[d][age].transportCounts[0];
                maxDataset = datasetNames[d];
            }
        }
        
        char buffer[150];
        std::sprintf(buffer, "   Age %s: Most car users in %s (%d car users)\n",
            ageGroupNames[age].c_str(),
            maxDataset.c_str(),
            maxCars);
        std::cout << buffer;
    }
    
    std::cout << "\n4. OVERALL DATASET STATISTICS:" << std::endl;
    for (int d = 0; d < 3; d++) {
        int totalResidents = 0;
        double totalEmissions = 0.0;
        
        for (int age = 0; age < 5; age++) {
            totalResidents += datasetAgeStats[d][age].residentCount;
            totalEmissions += datasetAgeStats[d][age].totalEmissions;
        }
        
        double avgPerResident = (totalResidents > 0) ? totalEmissions / totalResidents : 0;
        
        char buffer[150];
        std::sprintf(buffer, "   %s: %d residents, Total Emissions: %.2f kg CO2, Avg: %.4f kg CO2/resident\n",
            datasetNames[d].c_str(),
            totalResidents,
            totalEmissions,
            avgPerResident);
        std::cout << buffer;
    }
    
    std::cout << "\n" << std::string(110, '=') << std::endl;
}
