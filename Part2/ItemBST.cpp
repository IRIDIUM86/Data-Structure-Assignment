#include "ItemBST.h"
#include <iomanip>

ItemBST::ItemBST()
{
    root = NULL;
}

ItemBST::~ItemBST()
{
    destroyTree(root);
}

void ItemBST::destroyTree(BSTNode* node)
{
    if (node == NULL)
        return;

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

bool ItemBST::isEmpty()
{
    return root == NULL;
}

int ItemBST::count()
{
    return countNodes(root);
}

int ItemBST::countNodes(BSTNode* node)
{
    if (node == NULL)
        return 0;

    return 1 + countNodes(node->left) + countNodes(node->right);
}

void ItemBST::insert(Item item)
{
    root = insert(root, item);
}

BSTNode* ItemBST::insert(BSTNode* node, Item item)
{
    
    if (node == NULL)
    {
        BSTNode* newNode = new BSTNode;
        newNode->data  = item;
        newNode->left  = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (item.itemID < node->data.itemID)
        node->left = insert(node->left, item);
    else if (item.itemID > node->data.itemID)
        node->right = insert(node->right, item);
    else
        cout << "Item " << item.itemID << " already exists.\n";

    return node;
}

void ItemBST::deleteItem(string itemID)
{
    if (isEmpty())
    {
        cout << "\nItem database is empty.\n";
        return;
    }

    BSTNode* found = searchByID(root, itemID);

    if (found == NULL)
    {
        cout << "\nItem " << itemID << " not found in the system.\n";
        return;
    }

    root = deleteNode(root, itemID);
    cout << "\nItem " << itemID << " has been removed from the database.\n";
}

BSTNode* ItemBST::findMin(BSTNode* node)
{
    while (node->left != NULL)
        node = node->left;

    return node;
}

BSTNode* ItemBST::deleteNode(BSTNode* node, string itemID)
{
    if (node == NULL)
        return NULL;

    if (itemID < node->data.itemID)
        node->left = deleteNode(node->left, itemID);
    else if (itemID > node->data.itemID)
        node->right = deleteNode(node->right, itemID);
    else
    {
        if (node->left == NULL && node->right == NULL)
        {
            delete node;
            return NULL;
        }
        else if (node->left == NULL)
        {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL)
        {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }
        else
        {
            BSTNode* successor  = findMin(node->right);
            node->data          = successor->data;
            node->right         = deleteNode(node->right, successor->data.itemID);
        }
    }

    return node;
}

void ItemBST::searchByID(string itemID)
{
    BSTNode* result = searchByID(root, itemID);

    cout << "\n=====================================================\n";

    if (result != NULL)
    {
        cout << "ITEM FOUND\n";
        cout << "=====================================================\n";
        cout << left;
        cout << setw(12) << "Item ID"   << ": " << result->data.itemID   << "\n";
        cout << setw(12) << "Item Name" << ": " << result->data.itemName << "\n";
        cout << setw(12) << "Category"  << ": " << result->data.category << "\n";
        cout << setw(12) << "Location"  << ": "
             << result->data.zone  << " > "
             << result->data.aisle << " > "
             << result->data.shelf << "\n";
        cout << setw(12) << "Quantity"  << ": " << result->data.quantity << "\n";
    }
    else
    {
        cout << "Item " << itemID << " not found.\n";
    }

    cout << "=====================================================\n";
}

BSTNode* ItemBST::searchByID(BSTNode* node, string itemID)
{
    if (node == NULL || node->data.itemID == itemID)
        return node;

    if (itemID < node->data.itemID)
        return searchByID(node->left, itemID);
    else
        return searchByID(node->right, itemID);
}

void ItemBST::searchByName(string name)
{
    if (isEmpty())
    {
        cout << "\nItem database is empty.\n";
        return;
    }

    bool found = false;

    cout << "\n=====================================================\n";
    cout << "SEARCH RESULTS FOR: \"" << name << "\"\n";
    cout << "=====================================================\n";
    cout << left
         << setw(10) << "Item ID"
         << setw(25) << "Item Name"
         << setw(14) << "Category"
         << setw(10) << "Zone"
         << setw(10) << "Aisle"
         << setw(10) << "Shelf"
         << setw(8)  << "Qty"
         << "\n";
    cout << "-----------------------------------------------------"
         << "------------------------------\n";

    searchByName(root, name, found);

    if (!found)
        cout << "No items matched \"" << name << "\".\n";

    cout << "=====================================================\n";
}

void ItemBST::searchByName(BSTNode* node, string name, bool& found)
{
    if (node == NULL)
        return;

    searchByName(node->left, name, found);

    if (node->data.itemName.find(name) != string::npos)
    {
        cout << left
             << setw(10) << node->data.itemID
             << setw(25) << node->data.itemName
             << setw(14) << node->data.category
             << setw(10) << node->data.zone
             << setw(10) << node->data.aisle
             << setw(10) << node->data.shelf
             << setw(8)  << node->data.quantity
             << "\n";
        found = true;
    }

    searchByName(node->right, name, found);
}

void ItemBST::searchByCategory(string category)
{
    if (isEmpty())
    {
        cout << "\nItem database is empty.\n";
        return;
    }

    bool found = false;

    cout << "\n=====================================================\n";
    cout << "CATEGORY: " << category << "\n";
    cout << "=====================================================\n";
    cout << left
         << setw(10) << "Item ID"
         << setw(25) << "Item Name"
         << setw(10) << "Zone"
         << setw(10) << "Aisle"
         << setw(10) << "Shelf"
         << setw(8)  << "Qty"
         << "\n";
    cout << "-----------------------------------------------------"
         << "--------------------\n";

    searchByCategory(root, category, found);

    if (!found)
        cout << "No items found in category \"" << category << "\".\n";

    cout << "=====================================================\n";
}

void ItemBST::searchByCategory(BSTNode* node, string category, bool& found)
{
    if (node == NULL)
        return;

    searchByCategory(node->left, category, found);

    if (node->data.category == category)
    {
        cout << left
             << setw(10) << node->data.itemID
             << setw(25) << node->data.itemName
             << setw(10) << node->data.zone
             << setw(10) << node->data.aisle
             << setw(10) << node->data.shelf
             << setw(8)  << node->data.quantity
             << "\n";
        found = true;
    }

    searchByCategory(node->right, category, found);
}

void ItemBST::displayAll()
{
    if (isEmpty())
    {
        cout << "\nItem database is empty.\n";
        return;
    }

    cout << "\n=======================================================================\n";
    cout << "ALL ITEMS (Sorted by Item ID)\n";
    cout << "=======================================================================\n";
    cout << left
         << setw(10) << "Item ID"
         << setw(25) << "Item Name"
         << setw(14) << "Category"
         << setw(10) << "Zone"
         << setw(10) << "Aisle"
         << setw(10) << "Shelf"
         << setw(8)  << "Qty"
         << "\n";
    cout << "-----------------------------------------------------------------------\n";

    inOrder(root);

    cout << "=======================================================================\n";
    cout << "Total Items: " << count() << "\n";
}

void ItemBST::inOrder(BSTNode* node)
{
    if (node == NULL)
        return;

    inOrder(node->left);

    cout << left
         << setw(10) << node->data.itemID
         << setw(25) << node->data.itemName
         << setw(14) << node->data.category
         << setw(10) << node->data.zone
         << setw(10) << node->data.aisle
         << setw(10) << node->data.shelf
         << setw(8)  << node->data.quantity
         << "\n";

    inOrder(node->right);
}

void ItemBST::displayTree()
{
    if (isEmpty())
    {
        cout << "\nTree is empty.\n";
        return;
    }

    cout << "\n===========================================\n";
    cout << "BST STRUCTURE (ordered by Item ID)\n";
    cout << "===========================================\n";
    displayTree(root, "", false);
    cout << "===========================================\n";
}

void ItemBST::displayTree(BSTNode* node, string prefix, bool isLeft)
{
    if (node == NULL)
        return;

    cout << prefix;
    cout << (isLeft ? "+-- " : "\\-- ");
    cout << node->data.itemID << " (" << node->data.itemName << ")\n";

    displayTree(node->left,  prefix + (isLeft ? "|   " : "    "), true);
    displayTree(node->right, prefix + (isLeft ? "|   " : "    "), false);
}

void ItemBST::updateQuantity(string itemID, int newQty)
{
    BSTNode* result = searchByID(root, itemID);

    if (result == NULL)
    {
        cout << "\nItem " << itemID << " not found.\n";
        return;
    }

    int oldQty = result->data.quantity;
    result->data.quantity = newQty;

    cout << "\n=====================================================\n";
    cout << "QUANTITY UPDATED\n";
    cout << "=====================================================\n";
    cout << "Item ID   : " << result->data.itemID   << "\n";
    cout << "Item Name : " << result->data.itemName << "\n";
    cout << "Old Qty   : " << oldQty                << "\n";
    cout << "New Qty   : " << newQty                << "\n";
    cout << "=====================================================\n";
}

void loadItemsFromCSV(ItemBST& tree, const string& filename)
{
    ifstream file(filename);

    if (!file)
    {
        cout << "Error: Cannot open " << filename << "\n";
        return;
    }

    string line;

    getline(file, line);

    int loaded = 0;

    while (getline(file, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        stringstream ss(line);
        Item item;
        string quantityStr;
        string robotID;   
        string status;    

        getline(ss, item.itemID,    ','); 

        string orderID = item.itemID;    

        getline(ss, item.itemID,    ',');
        getline(ss, item.itemName,  ','); 
        getline(ss, item.category,  ','); 
        getline(ss, quantityStr,    ','); 
        getline(ss, item.zone,      ','); 
        getline(ss, item.aisle,     ','); 
        getline(ss, item.shelf,     ','); 
        getline(ss, robotID,        ','); 
        getline(ss, status,         ','); 

        item.quantity = stoi(quantityStr);

        tree.insert(item);
        loaded++;
    }

    file.close();
    cout << loaded << " item records loaded from " << filename << ".\n";
}
