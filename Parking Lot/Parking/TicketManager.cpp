#include "TicketManager.h"

TicketManager::TicketManager()
{
    counter = 0;
}

Ticket *TicketManager::createTicket(Vehicle *vehicle, int floorId, int slotId)
{
    tickets.push_back(make_unique<Ticket>(counter++, vehicle, floorId, vehicle->getType(), slotId));
    return tickets[tickets.size() - 1].get();
}

Ticket *TicketManager::getTicket(Vehicle *vehicle)
{
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets[i]->getVehicle()->getVehicleNumber() == vehicle->getVehicleNumber())
        {
            return tickets[i].get();
        }
    }
    return nullptr;
}

bool TicketManager::removeTicket(Vehicle *vehicle)
{
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets[i]->getVehicle() == vehicle)
        {
            tickets.erase(tickets.begin() + i);
            return true;
        }
    }
    return false;
}
