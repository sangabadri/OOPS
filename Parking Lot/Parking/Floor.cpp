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
        int slotId = counter[idx]++;
        parkingSlots[idx][slotId] = make_unique<ParkingSlot>(slotId, type);
    }
    freeSlots[idx] += count;
    totalSlots += count;
}

OpResult Floor::removeSlot(VehicleType type, int slotId)
{
    int idx = static_cast<int>(type);
    auto it = parkingSlots[idx].find(slotId);
    if (it == parkingSlots[idx].end())
    {
        return {false, "Slot " + to_string(slotId) + " doesn't exist."};
    }
    if (it->second->isOccupied())
    {
        return {false, "Slot " + to_string(slotId) + " is currently occupied. Cannot remove."};
    }
    parkingSlots[idx].erase(it);
    freeSlots[idx]--;
    totalSlots--;
    return {true, "Slot " + to_string(slotId) + " removed."};
}

int Floor::getSlotId(VehicleType type)
{
    int idx = static_cast<int>(type);
    for (auto &pair : parkingSlots[idx])
    {
        if (!pair.second->isOccupied())
        {
            return pair.first;
        }
    }
    return -1;
}

OpResult Floor::fillSlot(string vehicleNumber, VehicleType type, int ticketId)
{
    int idx = static_cast<int>(type);
    for (auto &pair : parkingSlots[idx])
    {
        if (!pair.second->isOccupied())
        {
            OpResult r = pair.second->addVehicle(vehicleNumber, type, ticketId);
            if (!r.success)
                return r;
            freeSlots[idx]--;
            return {true, "", pair.first};
        }
    }
    return {false, "No free slot available."};
}

OpResult Floor::emptySlot(string vehicleNumber, VehicleType type)
{
    int idx = static_cast<int>(type);
    for (auto &pair : parkingSlots[idx])
    {
        if (pair.second->getVehicleNumber() == vehicleNumber)
        {
            OpResult r = pair.second->removeVehicle(vehicleNumber);
            if (!r.success)
                return r;
            freeSlots[idx]++;
            return {true, ""};
        }
    }
    return {false, "Vehicle " + vehicleNumber + " not found on this floor."};
}

bool Floor::slotAvailable(VehicleType type)
{
    return freeSlots[static_cast<int>(type)] > 0;
}

bool Floor::containsVehicles()
{
    int free = 0;
    for (int i = 0; i < 3; i++)
    {
        free += freeSlots[i];
    }
    return (totalSlots - free) > 0;
}

string Floor::displaySlots()
{
    ostringstream out;
    out << "\nFloor " << id << ":\n";
    for (int t = 0; t < 3; t++)
    {
        VehicleType vt = static_cast<VehicleType>(t);
        int total = parkingSlots[t].size();
        int freeCount = freeSlots[t];
        int occupiedCount = total - freeCount;
        out << "\n" << vehicleTypeToString(vt) << " Slots\n";
        out << "Total: " << total << " | Free: " << freeCount << " | Occupied: " << occupiedCount << "\n";
        out << "Slot IDs:\n";
        if (parkingSlots[t].empty())
        {
            out << "None\n";
            continue;
        }
        for (auto &pair : parkingSlots[t])
        {
            ParkingSlot *slot = pair.second.get();
            out << "Slot " << slot->getID();
            if (slot->isOccupied())
            {
                out << " - Occupied (" << slot->getVehicleNumber() << ")";
            }
            else
            {
                out << " - Free";
            }
            out << "\n";
        }
    }
    return out.str();
}

string Floor::displayFreeSlots()
{
    ostringstream out;
    out << "\nFree Slots on Floor " << id << ":\n";
    for (int t = 0; t < 3; t++)
    {
        VehicleType vt = static_cast<VehicleType>(t);
        out << "\n" << vehicleTypeToString(vt) << " Slots";
        out << " (Free: " << freeSlots[t] << ")\n";
        bool found = false;
        for (auto &pair : parkingSlots[t])
        {
            ParkingSlot *slot = pair.second.get();
            if (!slot->isOccupied())
            {
                out << "Slot " << slot->getID() << "\n";
                found = true;
            }
        }
        if (!found)
        {
            out << "No slots available.\n";
        }
    }
    return out.str();
}

void Floor::loadSlot(VehicleType type, int slotId, bool occupied, string vehicleNumber, int ticketId)
{
    int idx = static_cast<int>(type);
    parkingSlots[idx][slotId] = make_unique<ParkingSlot>(slotId, type);
    if (occupied)
    {
        parkingSlots[idx][slotId]->setOccupied(vehicleNumber, ticketId);
    }
    else
    {
        freeSlots[idx]++;
    }
    totalSlots++;
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