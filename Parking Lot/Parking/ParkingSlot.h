#pragma once

#include "Vehicle.h"
#include <iostream>

class ParkingSlot
{
private:
    int id;
    VehicleType allowedVehicleType;
    Vehicle *vehicle;

public:
    ParkingSlot(int id, VehicleType type);
    bool addVehicle(Vehicle *vehicle);
    bool removeVehicle(Vehicle *vehicle);
    bool isOccupied();
    int getID();
    VehicleType getVehicleType();
    Vehicle *getVehicle();
};