#include <iostream>
#include <string>
#include "generalFunctions.hpp"

AgeGroupStats group[5];

std::string modes[6] = {"Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};

void displaySummary(Residents* head){
    std::cout << "\n --- DATA SUMMARY ---" << std::endl;
    std::cout << "Most preferred mode of transport: " << std::endl;
    // Reset group
    for(int i=0; i<5; i++) {
        group[i].residentCount = 0;
        group[i].totalEmissions = 0.0;
        for(int j=0; j<6; j++) group[i].transportCounts[j] = 0;
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
            std::string id = temp->ageGroup;
            group[idx].residentCount++;
            group[idx].totalEmissions += temp->dailyDistance * temp->carbonEmissionFactor;

        if (temp->modeOfTransport == "Car") group[idx].transportCounts[0]++;
                    else if (temp->modeOfTransport == "Bus") group[idx].transportCounts[1]++;
                    else if (temp->modeOfTransport == "Bicycle") group[idx].transportCounts[2]++;
                    else if (temp->modeOfTransport == "Walking") group[idx].transportCounts[3]++;
                    else if (temp->modeOfTransport == "School Bus") group[idx].transportCounts[4]++;
                    else if (temp->modeOfTransport == "Carpool") group[idx].transportCounts[5]++;
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
        if (i == 0) groupName = "---Children & Teenagers---";
        else if (i == 1) groupName = "---University Students / Young Adults---";
        else if (i == 2) groupName = "---Working Adults (Early Career)---";
        else if (i == 3) groupName = "---Working Adults (Late Career)---";
        else groupName = "---Senior Citizens---";

        summary += "\n" + groupName + ":\n";
        if (preferredMode != -1) {
            summary += "  Most preferred mode of transport: " + modes[preferredMode] + "\n";
        } else {
            summary += "  Most preferred mode of transport: No data\n";
        }
        summary += "  Total carbon emissions: " + std::to_string(group[i].totalEmissions) + " kg CO2\n";
        if (group[i].residentCount > 0) {
            double avgEmission = group[i].totalEmissions / group[i].residentCount;
            summary += "  Average emission per resident: " + std::to_string(avgEmission) + " kg CO2\n";
        } else {
            summary += "  Average emission per resident: N/A\n";
        }
    }
    
    return summary;
}