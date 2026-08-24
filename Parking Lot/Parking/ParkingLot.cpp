#include "ParkingLot.h"

ParkingLot::ParkingLot()
{
    counter = 0;
}

void ParkingLot::addFloor()
{
    floors.push_back(make_unique<Floor>(counter));
    counter++;
}

void ParkingLot::removeFloor(int id)
{
    for (int i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == id)
        {
            if (floors[i]->containsVehicles())
            {
                cout << "Floor " << id << " contains vehicles. Cannot be removed.\n";
                return;
            }
            floors.erase(floors.begin() + i);
            cout << "Floor " << id << " removed successfully.\n";
            return;
        }
    }
    cout << "Floor " << id << " doesn't exist.\n";
}

void ParkingLot::viewFloors()
{
    if (floors.empty())
    {
        cout << "No floors available.\n";
        return;
    }
    cout << "\n===== Available Floors =====\n";
    for (size_t i = 0; i < floors.size(); i++)
    {
        cout << "Floor ID: " << floors[i]->getID() << "\n";
    }
}

void ParkingLot::viewSlots(int floorId)
{
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == floorId)
        {
            cout << "\n===== Floor Slot Details =====\n";
            floors[i]->displaySlots();
            return;
        }
    }
    cout << "Floor " << floorId << " doesn't exist.\n";
}

void ParkingLot::viewFreeSlots(int floorId)
{
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == floorId)
        {
            cout << "\n===== Floor Slot Details =====\n";
            floors[i]->displayFreeSlots();
            return;
        }
    }
    cout << "Floor " << floorId << " doesn't exist.\n";
}

void ParkingLot::amountCollected()
{
    cout << "Amount collected: " << amount << endl;
}

void ParkingLot::addSlots(int floorId, VehicleType type, int count)
{
    for (int i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == floorId)
        {
            floors[i]->addSlots(type, count);
            return;
        }
    }
    cout << "Floor " << floorId << " doesn't exist.\n";
}

void ParkingLot::removeSlot(int floorId, VehicleType type, int slotId)
{
    for (int i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == floorId)
        {
            floors[i]->removeSlot(type, slotId);
            return;
        }
    }
    cout << "Floor " << floorId << " doesn't exist.\n";
}

bool ParkingLot::enterVehicle(Vehicle *vehicle)
{
    if (vehicle == nullptr)
    {
        cout << "Invalid vehicle.\n";
        return false;
    }
    if (ticketManager.getTicket(vehicle) != nullptr)
    {
        cout << "Vehicle " << vehicle->getVehicleNumber() << " is already parked.\n";
        return false;
    }
    for (int i = 0; i < floors.size(); i++)
    {
        if (floors[i]->slotAvailable(vehicle->getType()))
        {
            int slotId = floors[i]->fillSlot(vehicle);
            if (slotId == -1)
                continue;
            ticketManager.createTicket(vehicle, floors[i]->getID(), slotId);
            return true;
        }
    }
    cout << "No parking slot available for vehicle " << vehicle->getVehicleNumber() << ".\n";
    return false;
}

bool ParkingLot::exitVehicle(Vehicle *vehicle)
{
    if (vehicle == nullptr)
    {
        cout << "Invalid vehicle.\n";
        return false;
    }
    if (ticketManager.getTicket(vehicle) == nullptr)
    {
        cout << "Vehicle " << vehicle->getVehicleNumber() << " is not parked in the lot.\n";
        return false;
    }
    for (int i = 0; i < floors.size(); i++)
    {
        if (floors[i]->emptySlot(vehicle))
        {
            ticketManager.removeTicket(vehicle);
            return true;
        }
    }
    cout << "Vehicle " << vehicle->getVehicleNumber() << " is not parked in the lot.\n";
    return false;
}