#pragma once

#include "ParkingSlot.h"
#include <vector>
#include <memory>

class Floor
{
private:
    int id;
    vector<int> counter;
    vector<vector<unique_ptr<ParkingSlot>>> parkingSlots;
    vector<int> freeSlots;
    int totalSlots;

public:
    Floor(int id);
    int getID();
    void addSlots(VehicleType type, int count);
    void removeSlot(VehicleType type, int id);
    int getSlotId(VehicleType type);
    int fillSlot(string vehicleNumber, VehicleType type, int ticketId);
    bool emptySlot(string vehicleNumber, VehicleType type);
    bool slotAvailable(VehicleType type);
    bool containsVehicles();
    void displaySlots();
    void displayFreeSlots();
    void loadSlot(VehicleType type, int slotId, bool occupied, string vehicleNumber, int ticketId);
    void setCounter(VehicleType type, int val);
    int getCounter(VehicleType type);
    int getSlotCount(VehicleType type);
};