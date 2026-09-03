#include "TicketManager.h"

TicketManager::TicketManager()
{
    counter = 0;
}

Ticket *TicketManager::createTicket(string vehicleNumber, VehicleType type, int floorId, int slotId)
{
    tickets.push_back(make_unique<Ticket>(counter++, vehicleNumber, type, floorId, slotId));
    return tickets[tickets.size() - 1].get();
}

Ticket *TicketManager::getTicket(string vehicleNumber)
{
    for (size_t i = 0; i < tickets.size(); i++)
    {
        if (tickets[i]->getVehicleNumber() == vehicleNumber)
        {
            return tickets[i].get();
        }
    }
    return nullptr;
}

bool TicketManager::removeTicket(string vehicleNumber)
{
    for (size_t i = 0; i < tickets.size(); i++)
    {
        if (tickets[i]->getVehicleNumber() == vehicleNumber)
        {
            tickets.erase(tickets.begin() + i);
            return true;
        }
    }
    return false;
}

void TicketManager::addTicket(unique_ptr<Ticket> ticket)
{
    tickets.push_back(move(ticket));
}

void TicketManager::setCounter(int val)
{
    counter = val;
}

int TicketManager::getCounter()
{
    return counter;
}
