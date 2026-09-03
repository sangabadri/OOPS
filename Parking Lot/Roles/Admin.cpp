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

void Admin::viewFloors()
{
    operations.viewFloors();
}

void Admin::viewSlots(int floorId)
{
    operations.viewSlots(floorId);
}

void Admin::viewFreeSlots(int floorId)
{
    operations.viewFreeSlots(floorId);
}

void Admin::amountCollected()
{
    operations.amountCollected();
}

void Admin::viewRates()
{
    operations.viewRates();
}

void Admin::setRate(VehicleType type, int firstHourFee, int halfHourBlockFee)
{
    operations.setRate(type, firstHourFee, halfHourBlockFee);
}
