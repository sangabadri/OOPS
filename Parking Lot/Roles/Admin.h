#pragma once

#include "Operations/AdminOperations.h"
#include <iostream>

class Admin
{
private:
    AdminOperations &operations;

public:
    Admin(AdminOperations &operations);
    void addFloor();
    void removeFloor(int id);
    void addSlots(int floorId, VehicleType type, int count);
    void removeSlot(int floorId, VehicleType type, int slotId);
    void viewFloors();
    void viewSlots(int floorId);
    void viewFreeSlots(int floorId);
    void amountCollected();
    void viewRates();
    void setRate(VehicleType type, int firstHourFee, int halfHourBlockFee);
};