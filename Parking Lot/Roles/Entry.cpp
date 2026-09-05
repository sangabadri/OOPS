#include "Entry.h"

Entry::Entry(EntryOperations &operations) : operations(operations) {}

OpResult Entry::enterVehicle(string vehicleNumber, VehicleType type)
{
    OpResult r = operations.enterVehicle(vehicleNumber, type);
    cout << r.message << "\n";
    return r;
}