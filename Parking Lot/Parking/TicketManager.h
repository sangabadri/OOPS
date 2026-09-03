#pragma once

#include "Ticket.h"
#include <memory>
#include <vector>

class TicketManager
{
private:
    int counter;
    vector<unique_ptr<Ticket>> tickets;

public:
    TicketManager();
    Ticket *createTicket(string vehicleNumber, VehicleType type, int floorId, int slotId);
    Ticket *getTicket(string vehicleNumber);
    bool removeTicket(string vehicleNumber);
    void addTicket(unique_ptr<Ticket> ticket);
    void setCounter(int val);
    int getCounter();
};