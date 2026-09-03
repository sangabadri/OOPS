#include "Exit.h"

Exit::Exit(ExitOperations &operations) : operations(operations) {}

int Exit::exitVehicle(string vehicleNumber)
{
    return operations.exitVehicle(vehicleNumber);
}