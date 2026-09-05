#include "TicketManager.h"

TicketManager::TicketManager()
{
    counter = 0;
}

Ticket *TicketManager::createTicket(string vehicleNumber, VehicleType type, int floorId, int slotId)
{
    tickets[vehicleNumber] = make_unique<Ticket>(counter++, vehicleNumber, type, floorId, slotId);
    return tickets[vehicleNumber].get();
}

Ticket *TicketManager::getTicket(string vehicleNumber)
{
    auto it = tickets.find(vehicleNumber);
    if (it != tickets.end())
    {
        return it->second.get();
    }
    return nullptr;
}

bool TicketManager::removeTicket(string vehicleNumber)
{
    return tickets.erase(vehicleNumber) > 0;
}

void TicketManager::addTicket(unique_ptr<Ticket> ticket)
{
    string key = ticket->getVehicleNumber();
    tickets[key] = move(ticket);
}

void TicketManager::setCounter(int val)
{
    counter = val;
}

int TicketManager::getCounter()
{
    return counter;
}
