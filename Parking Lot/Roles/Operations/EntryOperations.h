#pragma once

#include "../../Parking/Vehicle.h"

class EntryOperations
{
public:
    virtual bool enterVehicle(Vehicle *vehicle) = 0;
    virtual ~EntryOperations() = default;
};