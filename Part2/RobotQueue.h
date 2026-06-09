#ifndef ROBOTQUEUE_H
#define ROBOTQUEUE_H

#include "Robot.h"
#include "OrderQueue.h"
#include <fstream>
#include <cctype>

#define GRID_SIZE 9

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
    string grid[GRID_SIZE][GRID_SIZE];
    
    // Private helper methods
    bool loadMapFromCSV();
    bool getCoordinates(string location, int& x, int& y);
    string parseLocationFormat(string zone, string shelf);
    bool isWall(int x, int y);
    bool bfsPathfinding(int startX, int startY, int targetX, int targetY, Robot& robot);
    void printWarehouseMap();

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
    bool   generatePathForRobot(Robot& robot, Order& order);
    void   executeRobotMovement(Robot& robot, Order& order);
};

#endif
