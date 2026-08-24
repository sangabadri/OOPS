#pragma once

#include "Operations/AdminOperations.h"

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
};