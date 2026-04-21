#include "AgeGroupCategorized.hpp"
#include <iostream>
#include <iomanip>

void categorizeByAge(UserData data[], int size, AgeGroupStats groups[]) {
   
    groups[0].groupName = "6-17 (Children/Teens)";
    groups[1].groupName = "18-25 (Uni/Young Adults)";
    groups[2].groupName = "26-45 (Working Early)";
    groups[3].groupName = "46-60 (Working Late)";
    groups[4].groupName = "61-100 (Seniors)";

    for (int i = 0; i < size; i++) {
        int age = data[i].age;
        int idx = -1;

        
        if (age >= 6 && age <= 17) idx = 0;
        else if (age >= 18 && age <= 25) idx = 1;
        else if (age >= 26 && age <= 45) idx = 2;
        else if (age >= 46 && age <= 60) idx = 3;
        else if (age >= 61 && age <= 100) idx = 4;

        if (idx != -1) {
            groups[idx].count++;
            
           
            double emission = data[i].distance * data[i].emissionFactor * data[i].days;
            groups[idx].totalEmission += emission;

           
            if (data[i].transport == "Car") groups[idx].carCount++;
            else if (data[i].transport == "Bus") groups[idx].busCount++;
            else if (data[i].transport == "Bicycle") groups[idx].bikeCount++;
            else if (data[i].transport == "Walking") groups[idx].walkCount++;
            else if (data[i].transport == "School Bus") groups[idx].schoolBusCount++;
            else if (data[i].transport == "Carpool") groups[idx].carpoolCount++;
        }
    }
}

void displayResults(AgeGroupStats groups[]) {
    std::cout << std::string(80, '-') << std::endl;
    std::cout << std::left << std::setw(25) << "Age Group" 
              << std::setw(10) << "Count" 
              << std::setw(20) << "Total Emission" 
              << "Avg per Resident" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (int i = 0; i < 5; i++) {
      
        double avg = (groups[i].count > 0) ? (groups[i].totalEmission / groups[i].count) : 0;
        
        std::cout << std::left << std::setw(25) << groups[i].groupName 
                  << std::setw(10) << groups[i].count 
                  << std::setw(20) << groups[i].totalEmission 
                  << std::fixed << std::setprecision(2) << avg << " kg CO2" << std::endl;
    }
}