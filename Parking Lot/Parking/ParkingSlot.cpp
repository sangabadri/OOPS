#include "ParkingSlot.h"

ParkingSlot::ParkingSlot(int id, VehicleType type) : id(id), allowedVehicleType(type), vehicleNumber(""), ticketId(-1) {}

OpResult ParkingSlot::addVehicle(string vehNumber, VehicleType type, int tId)
{
    if (isOccupied())
    {
        return {false, "Slot " + to_string(id) + " is currently occupied."};
    }
    if (type != allowedVehicleType)
    {
        return {false, "Slot " + to_string(id) + " does not accept this vehicle type."};
    }
    this->vehicleNumber = vehNumber;
    this->ticketId = tId;
    return {true, ""};
}

OpResult ParkingSlot::removeVehicle(string vehNumber)
{
    if (vehicleNumber == vehNumber)
    {
        vehicleNumber = "";
        ticketId = -1;
        return {true, ""};
    }
    return {false, "Vehicle " + vehNumber + " is not in this slot."};
}

bool ParkingSlot::isOccupied()
{
    return !vehicleNumber.empty();
}

int ParkingSlot::getID()
{
    return id;
}

VehicleType ParkingSlot::getVehicleType()
{
    return allowedVehicleType;
}

string ParkingSlot::getVehicleNumber()
{
    return vehicleNumber;
}

int ParkingSlot::getTicketId()
{
    return ticketId;
}

void ParkingSlot::setOccupied(string vehNumber, int tId)
{
    vehicleNumber = vehNumber;
    ticketId = tId;
}