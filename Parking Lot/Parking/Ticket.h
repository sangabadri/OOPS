#pragma once

#include "Vehicle.h"
#include <ctime>

class Ticket
{
private:
    int id;
    string vehicleNumber;
    VehicleType vehicleType;
    int floorId;
    int slotId;
    time_t entryTime;
    time_t exitTime;
    int feeCharged;

public:
    Ticket(int id, string vehicleNumber, VehicleType type, int floorId, int slotId);
    Ticket(int id, string vehicleNumber, VehicleType type, int floorId, int slotId, time_t entryTime);

    int getID();
    string getVehicleNumber();
    int getFloorID();
    VehicleType getVehicleType();
    int getSlotID();
    time_t getEntryTime();
    time_t getExitTime();
    int getFeeCharged();
    void setExit(time_t exitTime, int feeCharged);
};