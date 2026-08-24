#pragma once

#include "Operations/EntryOperations.h"

class Entry
{
private:
    EntryOperations &operations;

public:
    Entry(EntryOperations &operations);
    bool enterVehicle(Vehicle *vehicle);
};