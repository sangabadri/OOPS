#pragma once

#include "../../Parking/VehicleType.h"
#include "../../Parking/OpResult.h"
#include <string>

class EntryOperations
{
public:
    virtual OpResult enterVehicle(string vehicleNumber, VehicleType type) = 0;
    virtual ~EntryOperations() = default;
};