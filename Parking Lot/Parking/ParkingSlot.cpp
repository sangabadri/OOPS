#include "ParkingSlot.h"

ParkingSlot::ParkingSlot(int id, VehicleType type) : id(id), allowedVehicleType(type), vehicle(nullptr) {}

bool ParkingSlot::addVehicle(Vehicle *vehicle)
{
    if (isOccupied())
    {
        cout << "ParkingSlot " << id << " is currently occupied.\n";
        cout << "Please use a another slot as per your vehicle type.\n";
        return false;
    }
    if (vehicle->getType() != allowedVehicleType)
    {
        cout << "ParkingSlot " << id << " allowed vehicle type doesn't match with this vehicle.\n";
        cout << "Please use a another slot as per your vehicle type.\n";
        return false;
    }
    this->vehicle = vehicle;
    return true;
}

bool ParkingSlot::removeVehicle(Vehicle *vehicle)
{
    if (vehicle == this->vehicle)
    {
        this->vehicle = nullptr;
        return true;
    }
    cout << "The specified vehicle is not in this slot.\n";
    return false;
}

bool ParkingSlot::isOccupied()
{
    return vehicle;
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