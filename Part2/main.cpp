#include "OrderQueue.h"
#include "RobotQueue.h"
#include "ItemBST.h"

// ============================================================
// Forward declarations for sub-menus
// ============================================================
void menuOrderManagement(OrderQueue& orders, RobotQueue& robots);
void menuRobotManagement(RobotQueue& robots);
void menuRobotControl(RobotQueue& robots);
void menuItemManagement(ItemBST& items);

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

// ============================================================
// Task 1 — Order Management (OrderQueue)
// ============================================================
void menuOrderManagement(OrderQueue& orders, RobotQueue& robots)
{
    int choice;

    do
    {
        cout << "\n=====================================================\n";
        cout << "         ORDER MANAGEMENT\n";
        cout << "=====================================================\n";
        cout << "Orders Waiting  : " << orders.countOrders() << "\n";

        if (!orders.isEmpty())
            cout << "Current Order   : " << orders.peek().orderID << "\n";
        else
            cout << "Current Order   : None\n";

        cout << "=====================================================\n";
        cout << "1. View All Pending Orders\n";
        cout << "2. View Current Order\n";
        cout << "3. Assign Current Order to Robot\n";
        cout << "4. Search Order by ID\n";
        cout << "5. Back to Main Menu\n";
        cout << "\nEnter Choice: ";
        cin  >> choice;

        switch (choice)
        {
            case 1:
                orders.displayOrders();
                break;

            case 2:
            {
                if (orders.isEmpty())
                {
                    cout << "\nNo pending orders.\n";
                    break;
                }
                Order cur = orders.peek();
                cout << "\n=====================================================\n";
                cout << "CURRENT ORDER\n";
                cout << "=====================================================\n";
                cout << "Order ID : " << cur.orderID  << "\n";
                cout << "Item ID  : " << cur.itemID   << "\n";
                cout << "Item     : " << cur.itemName << "\n";
                cout << "Category : " << cur.category << "\n";
                cout << "Quantity : " << cur.quantity << "\n";
                cout << "Location : " << cur.zone << " > "
                                      << cur.aisle << " > "
                                      << cur.shelf << "\n";
                cout << "Status   : " << cur.status   << "\n";
                cout << "=====================================================\n";
                break;
            }

            case 3:
            {
                if (orders.isEmpty())
                {
                    cout << "\nNo pending orders to assign.\n";
                    break;
                }
                Order next = orders.dequeue();
                robots.assignToOrder(next);
                break;
            }

            case 4:
            {
                string id;
                cout << "\nEnter Order ID: ";
                cin  >> id;
                if (!orders.searchOrder(id))
                    cout << "Order " << id << " not found.\n";
                break;
            }

            case 5:
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    } while (choice != 5);
}

// ============================================================
// Task 2 — Robot Queue Management (RobotQueue)
// ============================================================
void menuRobotManagement(RobotQueue& robots)
{
    int choice;

    do
    {
        cout << "\n=====================================================\n";
        cout << "         ROBOT QUEUE MANAGEMENT\n";
        cout << "=====================================================\n";
        cout << "Available Robots: " << robots.countRobots() << "\n";
        cout << "=====================================================\n";
        cout << "1. View All Available Robots\n";
        cout << "2. Add Robot to Queue\n";
        cout << "3. Remove Next Robot from Queue\n";
        cout << "4. Back to Main Menu\n";
        cout << "\nEnter Choice: ";
        cin  >> choice;

        switch (choice)
        {
            case 1:
                robots.displayRobots();
                break;

            case 2:
            {
                string id;
                cout << "\nEnter Robot ID: ";
                cin  >> id;
                Robot r(id);
                robots.enqueue(r);
                cout << id << " added to queue.\n";
                break;
            }

            case 3:
            {
                if (robots.isEmpty())
                {
                    cout << "\nNo robots in queue.\n";
                    break;
                }
                Robot r = robots.dequeue();
                cout << "\n" << r.robotID << " removed from queue.\n";
                break;
            }

            case 4:
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    } while (choice != 4);
}

// ============================================================
// Task 3 — Robot Movement Control (Robot Stack)
// ============================================================
void menuRobotControl(RobotQueue& robots)
{
    if (robots.isEmpty())
    {
        cout << "\nNo robots available for movement control.\n";
        return;
    }

    // Work with a copy of the front robot
    Robot r = robots.peek();

    int choice;

    do
    {
        cout << "\n=====================================================\n";
        cout << "         ROBOT MOVEMENT CONTROL\n";
        cout << "=====================================================\n";
        cout << "Selected Robot : " << r.robotID << "\n";
        cout << "=====================================================\n";
        cout << "1. Push Movement Command\n";
        cout << "2. Execute Next Command (Pop)\n";
        cout << "3. Peek Next Command\n";
        cout << "4. View All Commands\n";
        cout << "5. Back to Main Menu\n";
        cout << "\nEnter Choice: ";
        cin  >> choice;

        switch (choice)
        {
            case 1:
            {
                int cmd;
                cout << "\nEnter Movement Command (integer): ";
                cin  >> cmd;
                r.push(cmd);
                break;
            }

            case 2:
            {
                int cmd = r.pop();
                if (cmd != -1)
                    cout << "\nExecuting command: " << cmd << "\n";
                break;
            }

            case 3:
            {
                int cmd = r.peek();
                if (cmd != -1)
                    cout << "\nNext command: " << cmd << "\n";
                break;
            }

            case 4:
                r.displayStack();
                break;

            case 5:
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    } while (choice != 5);
}

// ============================================================
// Task 4 — Item Search & Management (ItemBST)
// ============================================================
void menuItemManagement(ItemBST& items)
{
    int choice;

    do
    {
        cout << "\n=====================================================\n";
        cout << "       ITEM SEARCH AND MANAGEMENT\n";
        cout << "=====================================================\n";
        cout << "Total Items in Database: " << items.count() << "\n";
        cout << "=====================================================\n";
        cout << "1. Display All Items (Sorted by ID)\n";
        cout << "2. Search Item by ID\n";
        cout << "3. Search Item by Name\n";
        cout << "4. Search Item by Category\n";
        cout << "5. Add New Item\n";
        cout << "6. Update Item Quantity\n";
        cout << "7. Delete Item\n";
        cout << "8. View BST Structure\n";
        cout << "9. Back to Main Menu\n";
        cout << "\nEnter Choice: ";
        cin  >> choice;

        switch (choice)
        {
            case 1:
                items.displayAll();
                break;

            case 2:
            {
                string id;
                cout << "\nEnter Item ID: ";
                cin  >> id;
                items.searchByID(id);
                break;
            }

            case 3:
            {
                string name;
                cout << "\nEnter Item Name (or keyword): ";
                cin.ignore();
                getline(cin, name);
                items.searchByName(name);
                break;
            }

            case 4:
            {
                string category;
                cout << "\nEnter Category (Electronics / Accessories): ";
                cin.ignore();
                getline(cin, category);
                items.searchByCategory(category);
                break;
            }

            case 5:
            {
                Item newItem;
                cout << "\n=====================================================\n";
                cout << "ADD NEW ITEM\n";
                cout << "=====================================================\n";
                cout << "Item ID    : "; cin  >> newItem.itemID;
                cout << "Item Name  : "; cin.ignore(); getline(cin, newItem.itemName);
                cout << "Category   : "; getline(cin, newItem.category);
                cout << "Zone       : "; cin  >> newItem.zone;
                cout << "Aisle      : "; cin  >> newItem.aisle;
                cout << "Shelf      : "; cin  >> newItem.shelf;
                cout << "Quantity   : "; cin  >> newItem.quantity;

                items.insert(newItem);
                cout << "\nItem " << newItem.itemID << " added successfully.\n";
                break;
            }

            case 6:
            {
                string id;
                int    qty;
                cout << "\nEnter Item ID     : "; cin >> id;
                cout << "Enter New Quantity: "; cin >> qty;

                if (qty < 0)
                    cout << "\nQuantity cannot be negative.\n";
                else
                    items.updateQuantity(id, qty);
                break;
            }

            case 7:
            {
                string id;
                cout << "\nEnter Item ID to Delete: ";
                cin  >> id;
                items.deleteItem(id);
                break;
            }

            case 8:
                items.displayTree();
                break;

            case 9:
                break;

            default:
                cout << "\nInvalid choice. Please enter 1-9.\n";
        }

    } while (choice != 9);
}
