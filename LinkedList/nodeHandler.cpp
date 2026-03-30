#include <string>
#include "nodeHelper.hpp"

Residents* addResidents(Residents* head, std::string id, int age, std::string transport, int distance, float emissionFactor, int days){

    // Allocate memory for new nodes
    Residents* newNode = new Residents(id, age, transport,distance,emissionFactor,days);

    // Set the next node as head
    newNode -> next = head;

    head = newNode;

    // return the newly made node
    return newNode;
}