#include <iostream>
#include <string>
#include "fileHandler.hpp"
#include "arrayHandler.hpp"

int main(){
    loadDataSet("../Datasets/dataset1-cityA.csv");
    loadDataSet("../Datasets/dataset2-cityB.csv");
    loadDataSet("../Datasets/dataset3-cityC.csv");
    displayData();
    return -1;
};