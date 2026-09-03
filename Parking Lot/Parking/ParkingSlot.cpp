#include "ParkingSlot.h"

ParkingSlot::ParkingSlot(int id, VehicleType type) : id(id), allowedVehicleType(type), vehicle(nullptr), vehicleNumber(""), ticketId(-1) {}

bool ParkingSlot::addVehicle(string vehNumber, VehicleType type, int tId)
{
    if (isOccupied())
    {
        cout << "ParkingSlot " << id << " is currently occupied.\n";
        cout << "Please use a another slot as per your vehicle type.\n";
        return false;
    }
    if (type != allowedVehicleType)
    {
        cout << "ParkingSlot " << id << " allowed vehicle type doesn't match with this vehicle.\n";
        cout << "Please use a another slot as per your vehicle type.\n";
        return false;
    }
    this->vehicleNumber = vehNumber;
    this->ticketId = tId;
    return true;
}

bool ParkingSlot::removeVehicle(string vehNumber)
{
    if (vehicleNumber == vehNumber)
    {
        vehicleNumber = "";
        ticketId = -1;
        vehicle = nullptr;
        return true;
    }
    cout << "The specified vehicle is not in this slot.\n";
    return false;
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

Vehicle *ParkingSlot::getVehicle()
{
    return vehicle;
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