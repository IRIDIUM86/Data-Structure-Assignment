#include "OrderQueue.h"
#include "RobotQueue.h"
#include "ItemBST.h"
#include "SubMenu.hpp"

// ============================================================
// MAIN
// ============================================================
int main()
{
    // --- Load data ---
    OrderQueue pendingOrders;
    loadCSV(pendingOrders);

    RobotQueue robotPool;
    robotPool.initializeRobots(3);

    ItemBST itemTree;
    loadItemsFromCSV(itemTree, "warehouse_data.csv");

    int choice;

    do
    {
        cout << "\n=====================================================\n";
        cout << "     WAREHOUSE ROBOT MANAGEMENT SYSTEM\n";
        cout << "=====================================================\n";
        cout << "Pending Orders  : " << pendingOrders.countOrders() << "\n";
        cout << "Available Robots: " << robotPool.countRobots()     << "\n";
        cout << "Items in DB     : " << itemTree.count()             << "\n";
        cout << "=====================================================\n";
        cout << "1. Order Management\n";
        cout << "2. Robot Queue Management\n";
        cout << "3. Robot Movement Control\n";
        cout << "4. Item Search & Management\n";
        cout << "5. Exit\n";
        cout << "\nEnter Choice: ";
        cin  >> choice;

        switch (choice)
        {
            case 1:
                menuOrderManagement(pendingOrders, robotPool);
                break;

            case 2:
                menuRobotManagement(robotPool);
                break;

            case 3:
                menuRobotControl(robotPool);
                break;

            case 4:
                menuItemManagement(itemTree);
                break;

            case 5:
                cout << "\nThank you for using the Warehouse Robot System.\n";
                break;

            default:
                cout << "\nInvalid choice. Please enter 1-5.\n";
        }

    } while (choice != 5);

    return 0;
}