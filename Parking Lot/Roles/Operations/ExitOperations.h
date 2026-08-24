#pragma once

#include "../../Parking/Vehicle.h"

class ExitOperations
{
public:
    virtual bool exitVehicle(Vehicle *vehicle) = 0;
    virtual ~ExitOperations() = default;
};