#pragma once

#include "Vehicle.h"

class Ticket
{
private:
    int id;
    Vehicle *vehicle;
    int floorId;
    VehicleType vehicleType;
    int slotId;

public:
    Ticket(int id, Vehicle *vehicle, int floorId, VehicleType type, int slotId);

    int getID();
    Vehicle *getVehicle();
    int getFloorID();
    VehicleType getVehicleType();
    int getSlotID();
};