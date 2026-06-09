#ifndef ITEMBST_H
#define ITEMBST_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Item
{
    string itemID;
    string itemName;
    string category;
    string zone;
    string aisle;
    string shelf;
    int    quantity;
};

struct BSTNode
{
    Item    data;
    BSTNode* left;
    BSTNode* right;
};

class ItemBST
{
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, Item item);
    BSTNode* findMin(BSTNode* node);
    BSTNode* deleteNode(BSTNode* node, string itemID);
    BSTNode* searchByID(BSTNode* node, string itemID);
    void     searchByName(BSTNode* node, string name, bool& found);
    void     searchByCategory(BSTNode* node, string category, bool& found);
    void     inOrder(BSTNode* node);
    void     displayTree(BSTNode* node, string prefix, bool isLeft);
    void     destroyTree(BSTNode* node);
    int      countNodes(BSTNode* node);

public:
    ItemBST();
    ~ItemBST();

    void insert(Item item);
    void deleteItem(string itemID);
    void searchByID(string itemID);
    void searchByName(string name);
    void searchByCategory(string category);
    void displayAll();
    void displayTree();
    void updateQuantity(string itemID, int newQty);
    bool isEmpty();
    int  count();
};

void loadItemsFromCSV(ItemBST& tree, const string& filename);

#endif
