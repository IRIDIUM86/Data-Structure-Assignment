#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <string>
#define MAX 100

using namespace std;

struct Position
{
    int x, y;
};

class Robot
{
private:
    int top;
    int stack[MAX];
    Position currentPos;
    Position targetPos;

public:
    string robotID;
    string status;
    string assignedLocation;

    Robot();
    Robot(string id);

    bool push(int x);
    int  pop();
    int  peek();
    bool isEmpty();
    void displayStack();
    
    void setCurrentPos(Position pos);
    void setTargetPos(Position pos);
    Position getCurrentPos();
    Position getTargetPos();
};

#endif
