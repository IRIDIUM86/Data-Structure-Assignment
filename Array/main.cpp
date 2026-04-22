#include <iostream>
#include <string>
#include "fileHandler.hpp"
#include "arrayHandler.hpp"

int main(){
    loadDataSet("../Datasets/dataset1-cityA.csv");
    loadDataSet("../Datasets/dataset2-cityB.csv");
    loadDataSet("../Datasets/dataset3-cityC.csv");

    displayData();
    std::cout << "\nTotal Emission: " << totalEmission() << " kg CO2" << std::endl;
    emissionByTransport();

    analyzeAgeGroup(6, 17, "6-17 (Children & Teenagers)");
    analyzeAgeGroup(18, 25, "18-25 (University Students / Young Adults)");
    analyzeAgeGroup(26, 45, "26-45 (Working Adults - Early Career)");
    analyzeAgeGroup(46, 60, "46-60 (Working Adults - Late Career)");
    analyzeAgeGroup(61, 100, "61-100 (Senior Citizens / Retirees)");

    return 0;
}