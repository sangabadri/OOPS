#pragma once

#include "Floor.h"
#include "TicketManager.h"
#include "../Roles/Operations/AdminOperations.h"
#include "../Roles/Operations/EntryOperations.h"
#include "../Roles/Operations/ExitOperations.h"

class ParkingLot : public AdminOperations, public EntryOperations, public ExitOperations
{
private:
    int counter;
    vector<unique_ptr<Floor>> floors;
    TicketManager ticketManager;
    int amount;

public:
    ParkingLot();
    void addFloor() override;
    void removeFloor(int id) override;
    void viewFloors() override;
    void viewSlots(int floorId) override;
    void viewFreeSlots(int floorId) override;
    void amountCollected() override;
    void addSlots(int floorId, VehicleType type, int count) override;
    void removeSlot(int floorId, VehicleType, int slotId) override;
    bool enterVehicle(Vehicle *vehicle) override;
    bool exitVehicle(Vehicle *vehicle) override;
};