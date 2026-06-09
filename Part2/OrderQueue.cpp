#include "OrderQueue.h"
#include <fstream>
#include <sstream>
#include <iomanip>

OrderQueue::OrderQueue()
{
    front = NULL;
    rear = NULL;
}

bool OrderQueue::isEmpty()
{
    return front == NULL;
}

void OrderQueue::enqueue(Order order)
{
    Node* newNode = new Node;

    newNode->data = order;
    newNode->next = NULL;

    if(front == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

Order OrderQueue::dequeue()
{
    Order order = front->data;

    Node* temp = front;

    front = front->next;

    if(front == NULL)
    {
        rear = NULL;
    }

    delete temp;

    return order;
}

Order OrderQueue::peek()
{
    return front->data;
}

void OrderQueue::displayOrders()
{
    if(isEmpty())
    {
        cout << "No orders available.\n";
        return;
    }

    Node* current = front;

    cout << "\n============================================================================\n";
    cout << left
         << setw(12) << "Order ID"
         << setw(25) << "Item Name"
         << setw(10) << "Qty"
         << setw(15) << "Status"
         << endl;

    cout << "============================================================================\n";

    while(current != NULL)
    {
        cout << left
             << setw(12) << current->data.orderID
             << setw(25) << current->data.itemName
             << setw(10) << current->data.quantity
             << setw(15) << current->data.status
             << endl;

        current = current->next;
    }

    cout << "============================================================================\n";
}

int OrderQueue::countOrders()
{
    int count = 0;

    Node* current = front;

    while(current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

bool OrderQueue::searchOrder(string orderID)
{
    Node* current = front;

    while(current != NULL)
    {
        if(current->data.orderID == orderID)
        {
            cout << "\n=====================================================\n";
            cout << "ORDER DETAILS\n";
            cout << "=====================================================\n";

            cout << "Order ID : " << current->data.orderID << endl;
            cout << "Item ID  : " << current->data.itemID << endl;
            cout << "Item     : " << current->data.itemName << endl;
            cout << "Category : " << current->data.category << endl;
            cout << "Quantity : " << current->data.quantity << endl;
            cout << "Status   : " << current->data.status << endl;

            cout << "=====================================================\n";

            return true;
        }

        current = current->next;
    }

    return false;
}

void loadCSV(OrderQueue& queue)
{
    ifstream file("warehouse_data.csv");

    if(!file)
    {
        cout << "CSV file not found!\n";
        return;
    }

    string line;

    getline(file, line);

    while(getline(file, line))
    {
        stringstream ss(line);

        Order order;
        string quantity;

        getline(ss, order.orderID, ',');
        getline(ss, order.itemID, ',');
        getline(ss, order.itemName, ',');
        getline(ss, order.category, ',');

        getline(ss, quantity, ',');
        order.quantity = stoi(quantity);

        getline(ss, order.zone, ',');
        getline(ss, order.aisle, ',');
        getline(ss, order.shelf, ',');
        getline(ss, order.robotID, ',');
        getline(ss, order.status, ',');

        queue.enqueue(order);
    }

    file.close();
}