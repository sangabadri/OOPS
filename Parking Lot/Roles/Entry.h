#pragma once

#include "Operations/EntryOperations.h"
#include <iostream>

class Entry
{
private:
    EntryOperations &operations;

public:
    Entry(EntryOperations &operations);
    OpResult enterVehicle(string vehicleNumber, VehicleType type);
};