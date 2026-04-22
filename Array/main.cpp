#include <iostream>
#include <string>
#include "fileHandler.hpp"
#include "arrayHandler.hpp"
#include "AgeGroupCategorized.hpp"

extern UserData dataTable[maxRows]; 
extern int currentRow;

const int AGE_GROUP_COUNT = 5;

int main(){
    loadDataSet("../Datasets/dataset1-cityA.csv");
    loadDataSet("../Datasets/dataset2-cityB.csv");
    loadDataSet("../Datasets/dataset3-cityC.csv");
    displayData();

    AgeGroupStats groups[AGE_GROUP_COUNT];
    categorizeByAge(dataTable, currentRow, groups);
    std::cout << "\n--- CARBON EMISSION ANALYSIS BY AGE GROUP ---\n";
    displayResults(groups);

    return 0;
};