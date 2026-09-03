#pragma once

#include "Vehicle.h"
#include <iostream>

class ParkingSlot
{
private:
    int id;
    VehicleType allowedVehicleType;
    Vehicle *vehicle;
    string vehicleNumber;
    int ticketId;

public:
    ParkingSlot(int id, VehicleType type);
    bool addVehicle(string vehNumber, VehicleType type, int ticketId);
    bool removeVehicle(string vehNumber);
    bool isOccupied();
    int getID();
    VehicleType getVehicleType();
    Vehicle *getVehicle();
    string getVehicleNumber();
    int getTicketId();
    void setOccupied(string vehNumber, int ticketId);
};