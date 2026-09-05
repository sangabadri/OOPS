#pragma once

#include "Ticket.h"
#include <memory>
#include <unordered_map>

class TicketManager
{
private:
    int counter;
    unordered_map<string, unique_ptr<Ticket>> tickets;

public:
    TicketManager();
    Ticket *createTicket(string vehicleNumber, VehicleType type, int floorId, int slotId);
    Ticket *getTicket(string vehicleNumber);
    bool removeTicket(string vehicleNumber);
    void addTicket(unique_ptr<Ticket> ticket);
    void setCounter(int val);
    int getCounter();
};