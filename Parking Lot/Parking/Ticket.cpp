#include "Ticket.h"

Ticket::Ticket(int id, Vehicle *vehicle, int floorId, VehicleType type, int slotId)
{
    this->id = id;
    this->vehicle = vehicle;
    this->floorId = floorId;
    this->vehicleType = type;
    this->slotId = slotId;
}

int Ticket::getID()
{
    return id;
}

Vehicle *Ticket::getVehicle()
{
    return vehicle;
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
