#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <string>
#define MAX 100

using namespace std;

class Robot
{
private:
    int top;
    int stack[MAX];

public:
    string robotID;
    string status; // "Available" or "Busy"

    Robot();
    Robot(string id);

    bool push(int x);
    int  pop();
    int  peek();
    bool isEmpty();
    void displayStack();
};

#endif
