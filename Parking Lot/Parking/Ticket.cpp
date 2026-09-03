#include "Ticket.h"

Ticket::Ticket(int id, string vehicleNumber, VehicleType type, int floorId, int slotId)
{
    this->id = id;
    this->vehicleNumber = vehicleNumber;
    this->vehicleType = type;
    this->floorId = floorId;
    this->slotId = slotId;
    this->entryTime = time(nullptr);
    this->exitTime = 0;
    this->feeCharged = 0;
}

Ticket::Ticket(int id, string vehicleNumber, VehicleType type, int floorId, int slotId, time_t entryTime)
{
    this->id = id;
    this->vehicleNumber = vehicleNumber;
    this->vehicleType = type;
    this->floorId = floorId;
    this->slotId = slotId;
    this->entryTime = entryTime;
    this->exitTime = 0;
    this->feeCharged = 0;
}

int Ticket::getID()
{
    return id;
}

string Ticket::getVehicleNumber()
{
    return vehicleNumber;
}

int Ticket::getFloorID()
{
    return floorId;
}

VehicleType Ticket::getVehicleType()
{
    return vehicleType;
}

int Ticket::getSlotID()
{
    return slotId;
}

time_t Ticket::getEntryTime()
{
    return entryTime;
}

time_t Ticket::getExitTime()
{
    return exitTime;
}

int Ticket::getFeeCharged()
{
    return feeCharged;
}

void Ticket::setExit(time_t exitTime, int feeCharged)
{
    this->exitTime = exitTime;
    this->feeCharged = feeCharged;
}
