#include "Exit.h"

Exit::Exit(ExitOperations &operations) : operations(operations) {}

bool Exit::exitVehicle(Vehicle *vehicle)
{
    return operations.exitVehicle(vehicle);
}