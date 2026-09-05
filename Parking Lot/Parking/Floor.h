#pragma once

#include "ParkingSlot.h"
#include <vector>
#include <map>
#include <memory>
#include <sstream>

class Floor
{
private:
    int id;
    vector<int> counter;
    vector<map<int, unique_ptr<ParkingSlot>>> parkingSlots;
    vector<int> freeSlots;
    int totalSlots;

public:
    Floor(int id);
    int getID();
    void addSlots(VehicleType type, int count);
    OpResult removeSlot(VehicleType type, int id);
    int getSlotId(VehicleType type);
    OpResult fillSlot(string vehicleNumber, VehicleType type, int ticketId);
    OpResult emptySlot(string vehicleNumber, VehicleType type);
    bool slotAvailable(VehicleType type);
    bool containsVehicles();
    string displaySlots();
    string displayFreeSlots();
    void loadSlot(VehicleType type, int slotId, bool occupied, string vehicleNumber, int ticketId);
    void setCounter(VehicleType type, int val);
    int getCounter(VehicleType type);
    int getSlotCount(VehicleType type);
};