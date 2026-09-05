#include "ParkingLot.h"

ParkingLot::ParkingLot()
{
    counter = 0;
    amount = 0;
    rates[BIKE] = {20, 10};
    rates[CAR] = {40, 20};
    rates[TRUCK] = {60, 30};
    ensureDataDirs();
    loadRates();
    loadRevenue();
    loadFromDisk();
}

void ParkingLot::ensureDataDirs()
{
    // NOTE: Data/ is resolved relative to CWD. Running from outside "Parking Lot/" creates Data/ elsewhere.
    namespace fs = filesystem;
    fs::create_directories("Data/Floors");
    fs::create_directories("Data/Slots");
    fs::create_directories("Data/Tickets/open");
    fs::create_directories("Data/Tickets/closed");
    fs::create_directories("Data/Tickets/active_index");
    fs::create_directories("Data/Rates");
    fs::create_directories("Data/Revenue");
    fs::create_directories("Data/Users/Admin");
}

void ParkingLot::loadRates()
{
    ifstream file("Data/Rates/rates.txt");
    if (file.is_open())
    {
        string typeName;
        int first, half;
        while (file >> typeName >> first >> half)
        {
            rates[stringToVehicleType(typeName)] = {first, half};
        }
        file.close();
    }
    else
    {
        saveRates();
    }
}

void ParkingLot::saveRates()
{
    ofstream file("Data/Rates/rates.txt");
    if (file.is_open())
    {
        for (int t = 0; t < 3; t++)
        {
            VehicleType vt = static_cast<VehicleType>(t);
            file << vehicleTypeToString(vt) << " " << rates[vt].first << " " << rates[vt].second << "\n";
        }
        file.close();
    }
}

void ParkingLot::loadRevenue()
{
    ifstream file("Data/Revenue/amount.txt");
    if (file.is_open())
    {
        file >> amount;
        file.close();
    }
}

void ParkingLot::saveRevenue()
{
    // NOTE: not safe for concurrent processes writing to this file — no locking yet.
    ofstream file("Data/Revenue/amount.txt");
    if (file.is_open())
    {
        file << amount;
        file.close();
    }
}

void ParkingLot::loadFromDisk()
{
    namespace fs = filesystem;

    // Load floor counter
    {
        ifstream file("Data/Floors/id_counter.txt");
        if (file.is_open())
        {
            file >> counter;
            file.close();
        }
    }

    // Load floors
    for (int fid = 0; fid < counter; fid++)
    {
        string floorFile = "Data/Floors/floor_" + to_string(fid) + ".txt";
        if (!fs::exists(floorFile))
            continue;

        auto floor = make_unique<Floor>(fid);

        // Load slots for this floor
        for (int t = 0; t < 3; t++)
        {
            VehicleType vt = static_cast<VehicleType>(t);
            string slotDir = "Data/Slots/floor_" + to_string(fid) + "/" + vehicleTypeToString(vt);

            // Load slot counter
            string counterFile = slotDir + "/counter.txt";
            if (fs::exists(counterFile))
            {
                ifstream cf(counterFile);
                int cnt;
                cf >> cnt;
                cf.close();
                floor->setCounter(vt, cnt);
            }

            // Load individual slot files
            if (!fs::exists(slotDir) || !fs::is_directory(slotDir))
                continue;

            // Collect slot IDs first, then sort
            vector<int> slotIds;
            for (auto &entry : fs::directory_iterator(slotDir))
            {
                string fname = entry.path().filename().string();
                if (fname.rfind("slot_", 0) == 0 && fname.size() > 9)
                {
                    string idStr = fname.substr(5, fname.size() - 9);
                    try { slotIds.push_back(stoi(idStr)); } catch (...) {}
                }
            }
            sort(slotIds.begin(), slotIds.end());

            for (int slotId : slotIds)
            {
                string slotFile = slotDir + "/slot_" + to_string(slotId) + ".txt";
                ifstream sf(slotFile);
                if (sf.is_open())
                {
                    string line1, line2, line3;
                    getline(sf, line1);
                    getline(sf, line2);
                    getline(sf, line3);
                    sf.close();

                    bool occupied = (line1 == "1");
                    string vehNum = line2;
                    int tktId = -1;
                    if (!line3.empty())
                    {
                        try { tktId = stoi(line3); } catch (...) {}
                    }
                    floor->loadSlot(vt, slotId, occupied, vehNum, tktId);
                }
            }
        }

        floors.push_back(move(floor));
    }

    // Load ticket counter
    {
        ifstream file("Data/Tickets/id_counter.txt");
        if (file.is_open())
        {
            int tc;
            file >> tc;
            file.close();
            ticketManager.setCounter(tc);
        }
    }

    // Load open tickets
    string openDir = "Data/Tickets/open";
    if (fs::exists(openDir) && fs::is_directory(openDir))
    {
        for (auto &entry : fs::directory_iterator(openDir))
        {
            string fname = entry.path().filename().string();
            if (fname.rfind("ticket_", 0) == 0)
            {
                ifstream tf(entry.path().string());
                if (tf.is_open())
                {
                    string vehNum, typeName, floorStr, slotStr, entryStr;
                    getline(tf, vehNum);
                    getline(tf, typeName);
                    getline(tf, floorStr);
                    getline(tf, slotStr);
                    getline(tf, entryStr);
                    tf.close();

                    string idStr = fname.substr(7, fname.size() - 11);
                    try
                    {
                        int ticketId = stoi(idStr);
                        VehicleType vt = stringToVehicleType(typeName);
                        int fid = stoi(floorStr);
                        int sid = stoi(slotStr);
                        time_t et = static_cast<time_t>(stoll(entryStr));

                        auto ticket = make_unique<Ticket>(ticketId, vehNum, vt, fid, sid, et);
                        ticketManager.addTicket(move(ticket));
                    }
                    catch (...) {}
                }
            }
        }
    }
}

void ParkingLot::saveSlotFile(int floorId, VehicleType type, int slotId, bool occupied, string vehicleNumber, int ticketId)
{
    namespace fs = filesystem;
    string dir = "Data/Slots/floor_" + to_string(floorId) + "/" + vehicleTypeToString(type);
    fs::create_directories(dir);
    string path = dir + "/slot_" + to_string(slotId) + ".txt";
    ofstream file(path);
    if (file.is_open())
    {
        file << (occupied ? "1" : "0") << "\n";
        file << vehicleNumber << "\n";
        if (ticketId >= 0)
            file << ticketId;
        file.close();
    }
}

void ParkingLot::deleteSlotFile(int floorId, VehicleType type, int slotId)
{
    string path = "Data/Slots/floor_" + to_string(floorId) + "/" + vehicleTypeToString(type) + "/slot_" + to_string(slotId) + ".txt";
    remove(path.c_str());
}

void ParkingLot::saveOpenTicket(Ticket *ticket)
{
    string path = "Data/Tickets/open/ticket_" + to_string(ticket->getID()) + ".txt";
    ofstream file(path);
    if (file.is_open())
    {
        file << ticket->getVehicleNumber() << "\n";
        file << vehicleTypeToString(ticket->getVehicleType()) << "\n";
        file << ticket->getFloorID() << "\n";
        file << ticket->getSlotID() << "\n";
        file << ticket->getEntryTime();
        file.close();
    }

    // NOTE: not safe for concurrent processes writing to this file — no locking yet.
    ofstream cf("Data/Tickets/id_counter.txt");
    if (cf.is_open())
    {
        cf << ticketManager.getCounter();
        cf.close();
    }
}

void ParkingLot::moveTicketToClosed(Ticket *ticket, time_t exitTime, int fee)
{
    string openPath = "Data/Tickets/open/ticket_" + to_string(ticket->getID()) + ".txt";
    remove(openPath.c_str());

    string closedPath = "Data/Tickets/closed/ticket_" + to_string(ticket->getID()) + ".txt";
    ofstream file(closedPath);
    if (file.is_open())
    {
        file << ticket->getVehicleNumber() << "\n";
        file << vehicleTypeToString(ticket->getVehicleType()) << "\n";
        file << ticket->getFloorID() << "\n";
        file << ticket->getSlotID() << "\n";
        file << ticket->getEntryTime() << "\n";
        file << exitTime << "\n";
        file << fee;
        file.close();
    }
}

void ParkingLot::writeActiveIndex(string vehicleNumber, int ticketId)
{
    string path = "Data/Tickets/active_index/" + vehicleNumber + ".txt";
    ofstream file(path);
    if (file.is_open())
    {
        file << ticketId;
        file.close();
    }
}

void ParkingLot::deleteActiveIndex(string vehicleNumber)
{
    string path = "Data/Tickets/active_index/" + vehicleNumber + ".txt";
    remove(path.c_str());
}

OpResult ParkingLot::addFloor()
{
    namespace fs = filesystem;
    floors.push_back(make_unique<Floor>(counter));

    string floorFile = "Data/Floors/floor_" + to_string(counter) + ".txt";
    ofstream ff(floorFile);
    if (ff.is_open())
    {
        ff << counter;
        ff.close();
    }

    for (int t = 0; t < 3; t++)
    {
        VehicleType vt = static_cast<VehicleType>(t);
        string dir = "Data/Slots/floor_" + to_string(counter) + "/" + vehicleTypeToString(vt);
        fs::create_directories(dir);
        // NOTE: not safe for concurrent processes writing to this file — no locking yet.
        ofstream cf(dir + "/counter.txt");
        if (cf.is_open())
        {
            cf << 0;
            cf.close();
        }
    }

    int newFloorId = counter;
    counter++;

    // NOTE: not safe for concurrent processes writing to this file — no locking yet.
    ofstream cf("Data/Floors/id_counter.txt");
    if (cf.is_open())
    {
        cf << counter;
        cf.close();
    }

    return {true, "Floor " + to_string(newFloorId) + " added successfully.", newFloorId};
}

OpResult ParkingLot::removeFloor(int id)
{
    namespace fs = filesystem;
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == id)
        {
            if (floors[i]->containsVehicles())
            {
                return {false, "Floor " + to_string(id) + " contains vehicles. Cannot be removed."};
            }

            string floorFile = "Data/Floors/floor_" + to_string(id) + ".txt";
            remove(floorFile.c_str());

            string slotDir = "Data/Slots/floor_" + to_string(id);
            if (fs::exists(slotDir))
            {
                fs::remove_all(slotDir);
            }

            floors.erase(floors.begin() + i);
            return {true, "Floor " + to_string(id) + " removed successfully."};
        }
    }
    return {false, "Floor " + to_string(id) + " doesn't exist."};
}

OpResult ParkingLot::viewFloors()
{
    if (floors.empty())
    {
        return {true, "No floors available."};
    }
    ostringstream out;
    out << "\n===== Available Floors =====\n";
    for (size_t i = 0; i < floors.size(); i++)
    {
        out << "Floor ID: " << floors[i]->getID() << "\n";
    }
    return {true, out.str()};
}

OpResult ParkingLot::viewSlots(int floorId)
{
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == floorId)
        {
            string header = "\n===== Floor Slot Details =====\n";
            return {true, header + floors[i]->displaySlots()};
        }
    }
    return {false, "Floor " + to_string(floorId) + " doesn't exist."};
}

OpResult ParkingLot::viewFreeSlots(int floorId)
{
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == floorId)
        {
            string header = "\n===== Floor Slot Details =====\n";
            return {true, header + floors[i]->displayFreeSlots()};
        }
    }
    return {false, "Floor " + to_string(floorId) + " doesn't exist."};
}

OpResult ParkingLot::amountCollected()
{
    return {true, "Total revenue collected: " + to_string(amount)};
}

OpResult ParkingLot::addSlots(int floorId, VehicleType type, int count)
{
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == floorId)
        {
            int startId = floors[i]->getCounter(type);
            floors[i]->addSlots(type, count);

            for (int s = startId; s < startId + count; s++)
            {
                saveSlotFile(floorId, type, s, false, "", -1);
            }

            // NOTE: not safe for concurrent processes writing to this file — no locking yet.
            string dir = "Data/Slots/floor_" + to_string(floorId) + "/" + vehicleTypeToString(type);
            filesystem::create_directories(dir);
            ofstream cf(dir + "/counter.txt");
            if (cf.is_open())
            {
                cf << floors[i]->getCounter(type);
                cf.close();
            }

            return {true, to_string(count) + " " + vehicleTypeToString(type) + " slots added to Floor " + to_string(floorId) + "."};
        }
    }
    return {false, "Floor " + to_string(floorId) + " doesn't exist."};
}

OpResult ParkingLot::removeSlot(int floorId, VehicleType type, int slotId)
{
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == floorId)
        {
            int prevCount = floors[i]->getSlotCount(type);
            OpResult r = floors[i]->removeSlot(type, slotId);
            if (r.success && floors[i]->getSlotCount(type) < prevCount)
            {
                deleteSlotFile(floorId, type, slotId);
            }
            return r;
        }
    }
    return {false, "Floor " + to_string(floorId) + " doesn't exist."};
}

OpResult ParkingLot::viewRates()
{
    ostringstream out;
    out << "\n===== Parking Rates =====\n";
    for (int t = 0; t < 3; t++)
    {
        VehicleType vt = static_cast<VehicleType>(t);
        out << vehicleTypeToString(vt) << ": First Hour = " << rates[vt].first << ", Per 30min Block = " << rates[vt].second << "\n";
    }
    return {true, out.str()};
}

OpResult ParkingLot::setRate(VehicleType type, int firstHourFee, int halfHourBlockFee)
{
    rates[type] = {firstHourFee, halfHourBlockFee};
    saveRates();
    return {true, "Rate updated for " + vehicleTypeToString(type) + "."};
}

OpResult ParkingLot::enterVehicle(string vehicleNumber, VehicleType type)
{
    if (vehicleNumber.empty())
    {
        return {false, "Invalid vehicle number."};
    }
    if (ticketManager.getTicket(vehicleNumber) != nullptr)
    {
        return {false, "Vehicle " + vehicleNumber + " is already parked."};
    }
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->slotAvailable(type))
        {
            int slotId = floors[i]->getSlotId(type);
            if (slotId == -1)
                continue;

            Ticket *ticket = ticketManager.createTicket(vehicleNumber, type, floors[i]->getID(), slotId);

            OpResult fillResult = floors[i]->fillSlot(vehicleNumber, type, ticket->getID());
            if (!fillResult.success)
            {
                ticketManager.removeTicket(vehicleNumber);
                continue;
            }

            int filledSlotId = fillResult.value;

            saveOpenTicket(ticket);
            writeActiveIndex(vehicleNumber, ticket->getID());
            saveSlotFile(floors[i]->getID(), type, filledSlotId, true, vehicleNumber, ticket->getID());

            return {true, "Vehicle " + vehicleNumber + " parked. Ticket ID: " + to_string(ticket->getID()), ticket->getID()};
        }
    }
    return {false, "No parking slot available for vehicle " + vehicleNumber + "."};
}

OpResult ParkingLot::exitVehicle(string vehicleNumber)
{
    if (vehicleNumber.empty())
    {
        return {false, "Invalid vehicle number."};
    }

    Ticket *ticket = ticketManager.getTicket(vehicleNumber);
    if (ticket == nullptr)
    {
        return {false, "Vehicle " + vehicleNumber + " is not parked in the lot."};
    }

    time_t exitTime = time(nullptr);
    double secondsElapsed = difftime(exitTime, ticket->getEntryTime());
    double minutesElapsed = secondsElapsed / 60.0;

    VehicleType type = ticket->getVehicleType();
    int firstHourFee = rates[type].first;
    int halfHourBlockFee = rates[type].second;

    int fee = firstHourFee;
    if (minutesElapsed > 60)
    {
        fee += (int)ceil((minutesElapsed - 60) / 30.0) * halfHourBlockFee;
    }

    int floorId = ticket->getFloorID();
    int slotId = ticket->getSlotID();
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == floorId)
        {
            floors[i]->emptySlot(vehicleNumber, type);
            saveSlotFile(floorId, type, slotId, false, "", -1);
            break;
        }
    }

    ticket->setExit(exitTime, fee);
    moveTicketToClosed(ticket, exitTime, fee);
    deleteActiveIndex(vehicleNumber);

    // NOTE: not safe for concurrent processes writing to this file — no locking yet.
    amount += fee;
    saveRevenue();

    ticketManager.removeTicket(vehicleNumber);

    return {true, "Vehicle " + vehicleNumber + " exited. Fee charged: " + to_string(fee), fee};
}