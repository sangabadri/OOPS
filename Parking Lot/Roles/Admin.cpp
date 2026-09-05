#include "Admin.h"

Admin::Admin(AdminOperations &operations) : operations(operations) {}

void Admin::addFloor()
{
    OpResult r = operations.addFloor();
    cout << r.message << "\n";
}

void Admin::removeFloor(int id)
{
    OpResult r = operations.removeFloor(id);
    cout << r.message << "\n";
}

void Admin::addSlots(int floorId, VehicleType type, int count)
{
    OpResult r = operations.addSlots(floorId, type, count);
    cout << r.message << "\n";
}

void Admin::removeSlot(int floorId, VehicleType type, int slotId)
{
    OpResult r = operations.removeSlot(floorId, type, slotId);
    cout << r.message << "\n";
}

void Admin::viewFloors()
{
    OpResult r = operations.viewFloors();
    cout << r.message << "\n";
}

void Admin::viewSlots(int floorId)
{
    OpResult r = operations.viewSlots(floorId);
    cout << r.message << "\n";
}

void Admin::viewFreeSlots(int floorId)
{
    OpResult r = operations.viewFreeSlots(floorId);
    cout << r.message << "\n";
}

void Admin::amountCollected()
{
    OpResult r = operations.amountCollected();
    cout << r.message << "\n";
}

void Admin::viewRates()
{
    OpResult r = operations.viewRates();
    cout << r.message << "\n";
}

void Admin::setRate(VehicleType type, int firstHourFee, int halfHourBlockFee)
{
    OpResult r = operations.setRate(type, firstHourFee, halfHourBlockFee);
    cout << r.message << "\n";
}
