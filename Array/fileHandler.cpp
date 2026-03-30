#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "arrayHandler.hpp"

int loadDataSet(std::string fileName) {
    // 1. Use std:: prefix and the actual variable name
    std::ifstream readingFile(fileName); 

    // 2. Always check if the file actually opened
    if (!readingFile.is_open()) {
        std::cout << "File is missing or not found, please check the file directory!" << std::endl;
        return 1;
    }

    std::string line;
    // 3. Skip the CSV Header row (ID, Age, etc.)
    std::getline(readingFile, line);

    while (std::getline(readingFile, line)) {
            std::stringstream ss(line);
            std::string id, ageStr, mode, distStr, factorStr, daysStr;

            // Extract each column using the comma as a delimiter
            std::getline(ss, id, ',');
            std::getline(ss, ageStr, ',');
            std::getline(ss, mode, ',');
            std::getline(ss, distStr, ',');
            std::getline(ss, factorStr, ',');
            std::getline(ss, daysStr, ',');

            // Convert strings to the required data types
            // stoi = string to int | stof = string to float
            int age = std::stoi(ageStr);
            int dist = std::stoi(distStr); // Use stof if your CSV has decimals
            float factor = std::stof(factorStr);
            int days = std::stoi(daysStr);

            addArray(id, age, mode, dist, factor, days);
    }
    readingFile.close();
    return 0;
};