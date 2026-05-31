#include "Robot.h"
#include <iomanip>

Robot::Robot()
{
    top    = -1;
    robotID = "Unassigned";
    status  = "Available";
}

Robot::Robot(string id)
{
    top     = -1;
    robotID = id;
    status  = "Available";
}

bool Robot::push(int x)
{
    if (top >= (MAX - 1))
    {
        cout << "Stack Overflow! Cannot push " << x << "\n";
        return false;
    }
    stack[++top] = x;
    cout << "Movement command " << x << " pushed to " << robotID << "\n";
    return true;
}

int Robot::pop()
{
    if (top < 0)
    {
        cout << "Stack Underflow! No commands for " << robotID << "\n";
        return -1;
    }
    return stack[top--];
}

int Robot::peek()
{
    if (top < 0)
    {
        cout << "No commands in stack for " << robotID << "\n";
        return -1;
    }
    return stack[top];
}

bool Robot::isEmpty()
{
    return top < 0;
}

void Robot::displayStack()
{
    if (top < 0)
    {
        cout << robotID << " has no movement commands.\n";
        return;
    }

    cout << "\n=====================================================\n";
    cout << "Robot : " << robotID << " | Status: " << status << "\n";
    cout << "Movement Command Stack (top to bottom):\n";
    cout << "=====================================================\n";

    for (int i = top; i >= 0; i--)
        cout << "  [" << i << "] Command: " << stack[i] << "\n";

    cout << "=====================================================\n";
}
