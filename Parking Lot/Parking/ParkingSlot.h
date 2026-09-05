#pragma once

#include "VehicleType.h"
#include "OpResult.h"

class ParkingSlot
{
private:
    int id;
    VehicleType allowedVehicleType;
    string vehicleNumber;
    int ticketId;

public:
    ParkingSlot(int id, VehicleType type);
    OpResult addVehicle(string vehNumber, VehicleType type, int ticketId);
    OpResult removeVehicle(string vehNumber);
    bool isOccupied();
    int getID();
    VehicleType getVehicleType();
    string getVehicleNumber();
    int getTicketId();
    void setOccupied(string vehNumber, int ticketId);
};