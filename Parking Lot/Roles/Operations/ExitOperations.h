#pragma once

#include "../../Parking/VehicleType.h"
#include "../../Parking/OpResult.h"
#include <string>

class ExitOperations
{
public:
    virtual OpResult exitVehicle(string vehicleNumber) = 0;
    virtual ~ExitOperations() = default;
};