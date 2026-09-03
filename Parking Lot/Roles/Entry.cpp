#include "Entry.h"

Entry::Entry(EntryOperations &operations) : operations(operations) {}

int Entry::enterVehicle(string vehicleNumber, VehicleType type)
{
    return operations.enterVehicle(vehicleNumber, type);
}