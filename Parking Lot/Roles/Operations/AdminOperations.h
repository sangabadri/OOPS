#pragma once

#include "../../Parking/VehicleType.h"
#include "../../Parking/OpResult.h"

class AdminOperations
{
public:
    virtual OpResult addFloor() = 0;
    virtual OpResult removeFloor(int id) = 0;
    virtual OpResult viewFloors() = 0;
    virtual OpResult viewSlots(int floorId) = 0;
    virtual OpResult viewFreeSlots(int floorId) = 0;
    virtual OpResult amountCollected() = 0;
    virtual OpResult addSlots(int floorId, VehicleType type, int count) = 0;
    virtual OpResult removeSlot(int floorId, VehicleType, int slotId) = 0;
    virtual OpResult viewRates() = 0;
    virtual OpResult setRate(VehicleType type, int firstHourFee, int halfHourBlockFee) = 0;
    virtual ~AdminOperations() = default;
};