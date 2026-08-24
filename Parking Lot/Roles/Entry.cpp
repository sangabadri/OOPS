#include "Entry.h"

Entry::Entry(EntryOperations &operations) : operations(operations) {}

bool Entry::enterVehicle(Vehicle *vehicle)
{
    return operations.enterVehicle(vehicle);
}