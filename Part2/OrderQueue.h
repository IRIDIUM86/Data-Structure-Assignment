#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

#include <iostream>
#include <string>

using namespace std;

struct Order
{
    string orderID;
    string itemID;
    string itemName;
    string category;
    int quantity;
    string zone;
    string aisle;
    string shelf;
    string robotID;
    string status;
};

struct Node
{
    Order data;
    Node* next;
};

class OrderQueue
{
private:
    Node* front;
    Node* rear;

public:
    OrderQueue();

    bool isEmpty();

    void enqueue(Order order);

    Order dequeue();

    Order peek();

    void displayOrders();

    int countOrders();

    bool searchOrder(string orderID);
};

void loadCSV(OrderQueue& queue);

#endif