#pragma once

#include "../../Parking/Vehicle.h"
#include <string>

class EntryOperations
{
public:
    virtual int enterVehicle(string vehicleNumber, VehicleType type) = 0;
    virtual ~EntryOperations() = default;
};