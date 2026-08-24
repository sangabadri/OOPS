#include "Admin.h"

Admin::Admin(AdminOperations &operations) : operations(operations) {}

void Admin::addFloor()
{
    operations.addFloor();
}

void Admin::removeFloor(int id)
{
    operations.removeFloor(id);
}

void Admin::addSlots(int floorId, VehicleType type, int count)
{
    operations.addSlots(floorId, type, count);
}

void Admin::removeSlot(int floorId, VehicleType type, int slotId)
{
    operations.removeSlot(floorId, type, slotId);
}
