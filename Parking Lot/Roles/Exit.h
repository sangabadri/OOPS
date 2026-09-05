#pragma once

#include "Operations/ExitOperations.h"
#include <iostream>

class Exit
{
private:
    ExitOperations &operations;

public:
    Exit(ExitOperations &operations);
    OpResult exitVehicle(string vehicleNumber);
};