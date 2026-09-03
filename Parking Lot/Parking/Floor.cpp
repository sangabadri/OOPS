#include "Floor.h"

Floor::Floor(int id)
{
    this->id = id;
    counter.resize(3, 0);
    parkingSlots.resize(3);
    freeSlots.resize(3, 0);
    totalSlots = 0;
}

int Floor::getID()
{
    return id;
}

void Floor::addSlots(VehicleType type, int count)
{
    int idx = static_cast<int>(type);
    for (int i = 0; i < count; i++)
    {
        parkingSlots[idx].push_back(make_unique<ParkingSlot>(counter[idx]++, type));
    }
    freeSlots[idx] += count;
    totalSlots += count;
}

void Floor::removeSlot(VehicleType type, int id)
{
    int idx = static_cast<int>(type);
    for (size_t i = 0; i < parkingSlots[idx].size(); i++)
    {
        if (parkingSlots[idx][i]->getID() == id)
        {
            if (parkingSlots[idx][i]->isOccupied())
            {
                cout << "ParkingSlot " << id << " is currently occupied.\n";
                cout << "Cannot remove the slot.\n";
                return;
            }
            parkingSlots[idx].erase(parkingSlots[idx].begin() + i);
            freeSlots[idx]--;
            totalSlots--;
            return;
        }
    }
    cout << "ParkingSlot " << id << " doesn't exist.\n";
}

int Floor::getSlotId(VehicleType type)
{
    int idx = static_cast<int>(type);
    for (size_t i = 0; i < parkingSlots[idx].size(); i++)
    {
        if (!parkingSlots[idx][i]->isOccupied())
        {
            return parkingSlots[idx][i]->getID();
        }
    }
    return -1;
}

int Floor::fillSlot(string vehicleNumber, VehicleType type, int ticketId)
{
    int idx = static_cast<int>(type);
    for (size_t i = 0; i < parkingSlots[idx].size(); i++)
    {
        if (!parkingSlots[idx][i]->isOccupied())
        {
            if (!parkingSlots[idx][i]->addVehicle(vehicleNumber, type, ticketId))
                return -1;
            freeSlots[idx]--;
            return parkingSlots[idx][i]->getID();
        }
    }
    return -1;
}

bool Floor::emptySlot(string vehicleNumber, VehicleType type)
{
    int idx = static_cast<int>(type);
    for (size_t i = 0; i < parkingSlots[idx].size(); i++)
    {
        if (parkingSlots[idx][i]->getVehicleNumber() == vehicleNumber)
        {
            if (!parkingSlots[idx][i]->removeVehicle(vehicleNumber))
                return false;
            freeSlots[idx]++;
            return true;
        }
    }
    return false;
}

bool Floor::slotAvailable(VehicleType type)
{
    return freeSlots[static_cast<int>(type)];
}

bool Floor::containsVehicles()
{
    int occupied = 0;
    for (int i = 0; i < 3; i++)
    {
        occupied += freeSlots[i];
    }
    return totalSlots - occupied;
}

void Floor::displaySlots()
{
    vector<string> vehicleNames = {"Bike", "Car", "Truck"};
    cout << "\nFloor " << id << ":\n";
    for (int type = 0; type < 3; type++)
    {
        int total = parkingSlots[type].size();
        int freeCount = freeSlots[type];
        int occupiedCount = total - freeCount;
        cout << "\n"
             << vehicleNames[type] << " Slots\n";
        cout << "Total: " << total << " | Free: " << freeCount << " | Occupied: " << occupiedCount << "\n";
        cout << "Slot IDs:\n";
        if (parkingSlots[type].empty())
        {
            cout << "None\n";
            continue;
        }
        for (size_t i = 0; i < parkingSlots[type].size(); i++)
        {
            ParkingSlot *slot = parkingSlots[type][i].get();
            cout << "Slot " << slot->getID();
            if (slot->isOccupied())
            {
                cout << " - Occupied (" << slot->getVehicleNumber() << ")";
            }
            else
            {
                cout << " - Free";
            }
            cout << "\n";
        }
    }
}

void Floor::displayFreeSlots()
{
    vector<string> vehicleNames = {"Bike", "Car", "Truck"};
    cout << "\nFree Slots on Floor " << id << ":\n";
    for (int type = 0; type < 3; type++)
    {
        cout << "\n"
             << vehicleNames[type] << " Slots";
        cout << " (Free: " << freeSlots[type] << ")\n";
        bool found = false;
        for (size_t i = 0; i < parkingSlots[type].size(); i++)
        {
            ParkingSlot *slot = parkingSlots[type][i].get();
            if (!slot->isOccupied())
            {
                cout << "Slot " << slot->getID() << "\n";
                found = true;
            }
        }
        if (!found)
        {
            cout << "No slots available.\n";
        }
    }
}

void Floor::loadSlot(VehicleType type, int slotId, bool occupied, string vehicleNumber, int ticketId)
{
    int idx = static_cast<int>(type);
    parkingSlots[idx].push_back(make_unique<ParkingSlot>(slotId, type));
    if (occupied)
    {
        parkingSlots[idx].back()->setOccupied(vehicleNumber, ticketId);
        totalSlots++;
    }
    else
    {
        freeSlots[idx]++;
        totalSlots++;
    }
}

void Floor::setCounter(VehicleType type, int val)
{
    counter[static_cast<int>(type)] = val;
}

int Floor::getCounter(VehicleType type)
{
    return counter[static_cast<int>(type)];
}

int Floor::getSlotCount(VehicleType type)
{
    return parkingSlots[static_cast<int>(type)].size();
}