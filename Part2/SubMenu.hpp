#ifndef SUBMENU_HPP
#define SUBMENU_HPP

#include <iostream>
#include <string>
#include "OrderQueue.h"
#include "RobotQueue.h"
#include "ItemBST.h"

void menuOrderManagement(OrderQueue& orders, RobotQueue& robots);
void menuRobotManagement(RobotQueue& robots);
void menuRobotControl(RobotQueue& robots);
void menuItemManagement(ItemBST& items);

#endif
