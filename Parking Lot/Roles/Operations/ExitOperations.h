#pragma once

#include "../../Parking/Vehicle.h"
#include <string>

class ExitOperations
{
public:
    virtual int exitVehicle(string vehicleNumber) = 0;
    virtual ~ExitOperations() = default;
};