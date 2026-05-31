#include "RobotQueue.h"
#include <iomanip>
#include <sstream>

RobotQueue::RobotQueue()
{
    front = NULL;
    rear  = NULL;
}

bool RobotQueue::isEmpty()
{
    return front == NULL;
}

void RobotQueue::enqueue(Robot robot)
{
    RobotNode* newNode = new RobotNode;
    newNode->data = robot;
    newNode->next = NULL;

    if (front == NULL)
        front = rear = newNode;
    else
    {
        rear->next = newNode;
        rear       = newNode;
    }
}

Robot RobotQueue::dequeue()
{
    Robot robot   = front->data;
    RobotNode* temp = front;
    front         = front->next;

    if (front == NULL)
        rear = NULL;

    delete temp;
    return robot;
}

Robot RobotQueue::peek()
{
    return front->data;
}

int RobotQueue::countRobots()
{
    int count = 0;
    RobotNode* current = front;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

void RobotQueue::displayRobots()
{
    if (isEmpty())
    {
        cout << "No robots available.\n";
        return;
    }

    cout << "\n============================================================\n";
    cout << left
         << setw(15) << "Robot ID"
         << setw(15) << "Status"
         << "\n";
    cout << "============================================================\n";

    RobotNode* current = front;

    while (current != NULL)
    {
        cout << left
             << setw(15) << current->data.robotID
             << setw(15) << current->data.status
             << "\n";
        current = current->next;
    }

    cout << "============================================================\n";
    cout << "Available Robots: " << countRobots() << "\n";
}

bool RobotQueue::assignToOrder(Order& order)
{
    if (isEmpty())
    {
        cout << "\nNo robots available to assign!\n";
        return false;
    }

    Robot assigned  = dequeue();
    order.robotID   = assigned.robotID;
    order.status    = "Assigned";

    cout << "\n=====================================================\n";
    cout << "ROBOT ASSIGNED\n";
    cout << "=====================================================\n";
    cout << "Order ID : " << order.orderID  << "\n";
    cout << "Item     : " << order.itemName << "\n";
    cout << "Robot    : " << assigned.robotID << "\n";
    cout << "Location : " << order.zone << " > "
         << order.aisle << " > " << order.shelf << "\n";
    cout << "=====================================================\n";

    return true;
}

void RobotQueue::initializeRobots(int count)
{
    for (int i = 1; i <= count; i++)
    {
        ostringstream oss;
        oss << "Robot-" << i;
        Robot r(oss.str());
        enqueue(r);
    }

    cout << count << " robots initialized and ready.\n";
}
