#pragma once

#include "Operations/ExitOperations.h"

class Exit
{
private:
    ExitOperations &operations;

public:
    Exit(ExitOperations &operations);

    bool exitVehicle(Vehicle *vehicle);
};