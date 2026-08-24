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
    int getSlotId(Vehicle *vehicle);
    int fillSlot(Vehicle *Vehicle);
    bool emptySlot(Vehicle *vehicle);
    bool slotAvailable(VehicleType type);
    bool containsVehicles();
    void displaySlots();
    void displayFreeSlots();
};