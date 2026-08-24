#include "Vehicle.h"

Vehicle::Vehicle(string vehicleNumber, VehicleType type) : vehicleNumber(vehicleNumber), type(type) {}

VehicleType Vehicle::getType()
{
    return type;
}

string Vehicle::getVehicleNumber()
{
    return vehicleNumber;
}