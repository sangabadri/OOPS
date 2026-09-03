#pragma once

#include "Operations/EntryOperations.h"

class Entry
{
private:
    EntryOperations &operations;

public:
    Entry(EntryOperations &operations);
    int enterVehicle(string vehicleNumber, VehicleType type);
};