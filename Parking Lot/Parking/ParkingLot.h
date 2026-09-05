#pragma once

#include "Floor.h"
#include "TicketManager.h"
#include "../Roles/Operations/AdminOperations.h"
#include "../Roles/Operations/EntryOperations.h"
#include "../Roles/Operations/ExitOperations.h"
#include <map>
#include <ctime>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <algorithm>

class ParkingLot : public AdminOperations, public EntryOperations, public ExitOperations
{
private:
    int counter;
    vector<unique_ptr<Floor>> floors;
    TicketManager ticketManager;
    int amount;
    map<VehicleType, pair<int, int>> rates;

    void ensureDataDirs();
    void loadFromDisk();
    void loadRates();
    void saveRates();
    void loadRevenue();
    void saveRevenue();
    void saveSlotFile(int floorId, VehicleType type, int slotId, bool occupied, string vehicleNumber, int ticketId);
    void deleteSlotFile(int floorId, VehicleType type, int slotId);
    void saveOpenTicket(Ticket *ticket);
    void moveTicketToClosed(Ticket *ticket, time_t exitTime, int fee);
    void writeActiveIndex(string vehicleNumber, int ticketId);
    void deleteActiveIndex(string vehicleNumber);

public:
    ParkingLot();
    OpResult addFloor() override;
    OpResult removeFloor(int id) override;
    OpResult viewFloors() override;
    OpResult viewSlots(int floorId) override;
    OpResult viewFreeSlots(int floorId) override;
    OpResult amountCollected() override;
    OpResult addSlots(int floorId, VehicleType type, int count) override;
    OpResult removeSlot(int floorId, VehicleType, int slotId) override;
    OpResult viewRates() override;
    OpResult setRate(VehicleType type, int firstHourFee, int halfHourBlockFee) override;
    OpResult enterVehicle(string vehicleNumber, VehicleType type) override;
    OpResult exitVehicle(string vehicleNumber) override;
};