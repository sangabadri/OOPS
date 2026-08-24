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
    Ticket *createTicket(Vehicle *vehicle, int floorId, int slotId);
    Ticket *getTicket(Vehicle *vehicle);
    bool removeTicket(Vehicle *vehicle);
};