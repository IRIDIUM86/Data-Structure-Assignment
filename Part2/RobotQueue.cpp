#include "RobotQueue.h"
#include <iomanip>
#include <sstream>
#include <cstring>

// Coordinate mapping for all locations
struct LocationCoord
{
    string name;
    int x, y;
};

LocationCoord locationMap[] = {
    {"a1", 2, 5}, {"a2", 3, 5}, {"a3", 4, 5}, {"a4", 5, 5}, {"a5", 6, 5},
    {"b1", 2, 3}, {"b2", 3, 3}, {"b3", 4, 3}, {"b4", 5, 3}, {"b5", 6, 3},
    {"c1", 2, 1}, {"c2", 3, 1}, {"c3", 4, 1}, {"c4", 5, 1}, {"c5", 6, 1},
    {"s",  3, 7}
};

RobotQueue::RobotQueue()
{
    front = NULL;
    rear  = NULL;
    loadMapFromCSV();
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
         << setw(20) << "Assigned Location"
         << "\n";
    cout << "============================================================\n";

    RobotNode* current = front;

    while (current != NULL)
    {
        cout << left
             << setw(15) << current->data.robotID
             << setw(15) << current->data.status
             << setw(20) << current->data.assignedLocation
             << "\n";
        current = current->next;
    }

    cout << "============================================================\n";
    cout << "Available Robots: " << countRobots() << "\n";
}

bool RobotQueue::loadMapFromCSV()
{
    ifstream file("map.csv");
    if (!file.is_open())
    {
        cout << "Error: Could not open map.csv\n";
        return false;
    }

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            file >> grid[i][j];
        }
    }

    file.close();
    return true;
}

void RobotQueue::printWarehouseMap()
{
    cout << "\n=====================================================\n";
    cout << "WAREHOUSE MAP (Coordinates: X=Column, Y=Row)\n";
    cout << "=====================================================\n";
    cout << "Starting Position (S): X=3, Y=7\n";
    cout << "Shelves:\n";
    cout << "  Zone A (Y=5): a1(X=2), a2(X=3), a3(X=4), a4(X=5), a5(X=6)\n";
    cout << "  Zone B (Y=3): b1(X=2), b2(X=3), b3(X=4), b4(X=5), b5(X=6)\n";
    cout << "  Zone C (Y=1): c1(X=2), c2(X=3), c3(X=4), c4(X=5), c5(X=6)\n";
    cout << "Wall (1): Robot cannot pass\n";
    cout << "=====================================================\n";
    
    cout << "\nGrid Visualization:\n";
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            cout << left << setw(6) << grid[i][j];
        }
        cout << "\n";
    }
    cout << "=====================================================\n";
}

bool RobotQueue::getCoordinates(string location, int& x, int& y)
{
    // Search in location map
    for (int i = 0; i < 14; i++)
    {
        if (locationMap[i].name == location)
        {
            x = locationMap[i].x;
            y = locationMap[i].y;
            return true;
        }
    }
    return false;
}

string RobotQueue::parseLocationFormat(string zone, string shelf)
{
    // Convert "Zone-A" + "Shelf-3" → "a3"
    char zoneLetter = tolower(zone[zone.length() - 1]);
    
    string shelfNum = "";
    for (char c : shelf)
    {
        if (isdigit(c))
            shelfNum += c;
    }
    
    return string(1, zoneLetter) + shelfNum;
}

bool RobotQueue::isWall(int x, int y)
{
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE)
        return true;
    return grid[y][x] == "1";
}

bool RobotQueue::bfsPathfinding(int startX, int startY, int targetX, int targetY, Robot& robot)
{
    // Array-based BFS without STL queue or vector
    struct PathNode
    {
        int x, y;
        int path[100]; // Store path commands
        int pathLen;
    };
    
    PathNode queue[GRID_SIZE * GRID_SIZE];
    int queueStart = 0, queueEnd = 0;
    bool visited[GRID_SIZE][GRID_SIZE];
    
    // Initialize visited
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            visited[i][j] = false;
    
    // Add starting position to queue
    queue[queueEnd].x = startX;
    queue[queueEnd].y = startY;
    queue[queueEnd].pathLen = 0;
    queueEnd++;
    visited[startY][startX] = true;
    
    // Directions: 1=UP, 2=DOWN, 3=LEFT, 4=RIGHT
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    int dir[] = {1, 2, 3, 4};
    
    while (queueStart < queueEnd)
    {
        PathNode current = queue[queueStart];
        queueStart++;
        
        if (current.x == targetX && current.y == targetY)
        {
            // Found path, push to stack (reverse order for LIFO)
            for (int i = current.pathLen - 1; i >= 0; i--)
                robot.push(current.path[i]);
            return true;
        }
        
        // Explore neighbors
        for (int i = 0; i < 4; i++)
        {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];
            
            if (!isWall(newX, newY) && !visited[newY][newX])
            {
                visited[newY][newX] = true;
                
                // Create new path node
                queue[queueEnd].x = newX;
                queue[queueEnd].y = newY;
                queue[queueEnd].pathLen = current.pathLen + 1;
                
                // Copy path and add new direction
                for (int j = 0; j < current.pathLen; j++)
                    queue[queueEnd].path[j] = current.path[j];
                queue[queueEnd].path[current.pathLen] = dir[i];
                
                queueEnd++;
            }
        }
    }
    
    return false;
}

bool RobotQueue::generatePathForRobot(Robot& robot, Order& order)
{
    string location = parseLocationFormat(order.zone, order.shelf);
    int targetX, targetY;
    
    if (!getCoordinates(location, targetX, targetY))
    {
        cout << "Error: Location " << location << " not found!\n";
        return false;
    }
    
    int startX = 3, startY = 7; // Starting at 's'
    
    robot.setCurrentPos({startX, startY});
    robot.setTargetPos({targetX, targetY});
    robot.assignedLocation = location;
    
    if (!bfsPathfinding(startX, startY, targetX, targetY, robot))
    {
        cout << "Error: Could not find path to " << location << "\n";
        return false;
    }
    
    cout << "\n" << robot.robotID << " - Path calculated successfully!\n";
    cout << "From (X=" << startX << ", Y=" << startY << ") → (X=" << targetX 
         << ", Y=" << targetY << ")\n";
    
    return true;
}

void RobotQueue::executeRobotMovement(Robot& robot, Order& order)
{
    int startX = 3, startY = 7;
    int currentX = startX, currentY = startY;
    
    cout << "\n=====================================================\n";
    cout << "EXECUTION LOG - " << robot.robotID << " (Order: " << order.orderID << ")\n";
    cout << "=====================================================\n";
    
    // Execute path to target
    while (!robot.isEmpty())
    {
        int cmd = robot.pop();
        
        switch (cmd)
        {
            case 1: // UP
                currentY--;
                cout << robot.robotID << " goes up\n";
                break;
            case 2: // DOWN
                currentY++;
                cout << robot.robotID << " goes down\n";
                break;
            case 3: // LEFT
                currentX--;
                cout << robot.robotID << " goes left\n";
                break;
            case 4: // RIGHT
                currentX++;
                cout << robot.robotID << " goes right\n";
                break;
        }
    }
    
    // At target location
    cout << robot.robotID << " put the item\n";
    
    // Generate return path
    int targetX = currentX, targetY = currentY;
    Robot returnRobot = Robot(robot.robotID);
    returnRobot.status = robot.status;
    returnRobot.assignedLocation = robot.assignedLocation;
    
    if (bfsPathfinding(targetX, targetY, startX, startY, returnRobot))
    {
        while (!returnRobot.isEmpty())
        {
            int cmd = returnRobot.pop();
            
            switch (cmd)
            {
                case 1: // UP
                    currentY--;
                    cout << robot.robotID << " goes up\n";
                    break;
                case 2: // DOWN
                    currentY++;
                    cout << robot.robotID << " goes down\n";
                    break;
                case 3: // LEFT
                    currentX--;
                    cout << robot.robotID << " goes left\n";
                    break;
                case 4: // RIGHT
                    currentX++;
                    cout << robot.robotID << " goes right\n";
                    break;
            }
        }
    }
    
    cout << robot.robotID << " is now free\n";
    cout << "=====================================================\n";
    
    order.status = "Completed";
    robot.status = "Available";
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
    assigned.status = "Busy";

    cout << "\n=====================================================\n";
    cout << "ROBOT ASSIGNED TO ORDER\n";
    cout << "=====================================================\n";
    cout << "Order ID    : " << order.orderID  << "\n";
    cout << "Item        : " << order.itemName << "\n";
    cout << "Robot       : " << assigned.robotID << "\n";
    cout << "Location    : " << order.zone << " > " << order.aisle 
         << " > " << order.shelf << "\n";
    cout << "Quantity    : " << order.quantity << "\n";
    cout << "=====================================================\n";

    if (generatePathForRobot(assigned, order))
    {
        executeRobotMovement(assigned, order);
        enqueue(assigned);
    }

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
    printWarehouseMap();
}
