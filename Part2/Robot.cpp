#include "Robot.h"
#include <iomanip>

Robot::Robot()
{
    top    = -1;
    robotID = "Unassigned";
    status  = "Available";
    currentPos = {3, 7};
    targetPos = {-1, -1};
    assignedLocation = "";
}

Robot::Robot(string id)
{
    top     = -1;
    robotID = id;
    status  = "Available";
    currentPos = {3, 7};
    targetPos = {-1, -1};
    assignedLocation = "";
}

bool Robot::push(int x)
{
    if (top >= (MAX - 1))
    {
        return false;
    }
    stack[++top] = x;
    return true;
}

int Robot::pop()
{
    if (top < 0)
    {
        return -1;
    }
    return stack[top--];
}

int Robot::peek()
{
    if (top < 0)
    {
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
    cout << "Legend: 1=UP, 2=DOWN, 3=LEFT, 4=RIGHT\n";
    cout << "-----------------------------------------------------\n";

    for (int i = top; i >= 0; i--)
    {
        string direction;
        switch(stack[i])
        {
            case 1: direction = "UP"; break;
            case 2: direction = "DOWN"; break;
            case 3: direction = "LEFT"; break;
            case 4: direction = "RIGHT"; break;
            default: direction = "UNKNOWN"; break;
        }
        cout << "  [" << i << "] Command: " << stack[i] << " (" << direction << ")\n";
    }

    cout << "=====================================================\n";
}

void Robot::setCurrentPos(Position pos)
{
    currentPos = pos;
}

void Robot::setTargetPos(Position pos)
{
    targetPos = pos;
}

Position Robot::getCurrentPos()
{
    return currentPos;
}

Position Robot::getTargetPos()
{
    return targetPos;
}
