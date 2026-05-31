#ifndef ROBOTQUEUE_H
#define ROBOTQUEUE_H

#include "Robot.h"
#include "OrderQueue.h"

struct RobotNode
{
    Robot      data;
    RobotNode* next;
};

class RobotQueue
{
private:
    RobotNode* front;
    RobotNode* rear;

public:
    RobotQueue();

    bool   isEmpty();
    void   enqueue(Robot robot);
    Robot  dequeue();
    Robot  peek();
    int    countRobots();
    void   displayRobots();
    bool   assignToOrder(Order& order);
    void   initializeRobots(int count);
};

#endif
