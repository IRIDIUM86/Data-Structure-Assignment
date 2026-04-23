#include <string>
#include "nodeHelper.hpp"

Residents* addResidents(Residents* head, std::string id, int age, std::string transport, int distance, float emissionFactor, int days, std::string ageGroup) {

    // Allocate memory for new nodes
    Residents* newNode = new Residents(id, age, transport,distance,emissionFactor,days,ageGroup);

    // Set the next node as head
    newNode -> next = head;

    head = newNode;

    // return the newly made node
    return newNode;
}

std::string ageGrouping(int age) {
    if (age >= 0 && age <= 17) {
        return "Children & Teenagers";
    } else if (age >= 18 && age <= 25) {
        return "University Students / Young Adults";
    } else if (age >= 26 && age <= 45) {
        return "Working Adults (Early Career) ";
    } else if (age >= 46 && age <= 60) {
        return "Working Adults (Late Career)";
    } else if (age > 61 && age <= 100) {
        return "Senior Citizens";
    }
    else {
        return "Invalid Age";
    }
}

