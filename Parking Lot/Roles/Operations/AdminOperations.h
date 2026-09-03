#pragma once

#include "../../Parking/Vehicle.h"

class AdminOperations
{
public:
    virtual void addFloor() = 0;
    virtual void removeFloor(int id) = 0;
    virtual void viewFloors() = 0;
    virtual void viewSlots(int floorId) = 0;
    virtual void viewFreeSlots(int floorId) = 0;
    virtual void amountCollected() = 0;
    virtual void addSlots(int floorId, VehicleType type, int count) = 0;
    virtual void removeSlot(int floorId, VehicleType, int slotId) = 0;
    virtual void viewRates() = 0;
    virtual void setRate(VehicleType type, int firstHourFee, int halfHourBlockFee) = 0;
    virtual ~AdminOperations() = default;
};