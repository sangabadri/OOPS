#include "Exit.h"

Exit::Exit(ExitOperations &operations) : operations(operations) {}

OpResult Exit::exitVehicle(string vehicleNumber)
{
    OpResult r = operations.exitVehicle(vehicleNumber);
    cout << r.message << "\n";
    return r;
}