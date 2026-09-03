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
        file << "BIKE " << rates[BIKE].first << " " << rates[BIKE].second << "\n";
        file << "CAR " << rates[CAR].first << " " << rates[CAR].second << "\n";
        file << "TRUCK " << rates[TRUCK].first << " " << rates[TRUCK].second << "\n";
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
        vector<string> typeNames = {"BIKE", "CAR", "TRUCK"};
        for (int t = 0; t < 3; t++)
        {
            VehicleType vt = static_cast<VehicleType>(t);
            string slotDir = "Data/Slots/floor_" + to_string(fid) + "/" + typeNames[t];

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

    // Update ticket counter
    ofstream cf("Data/Tickets/id_counter.txt");
    if (cf.is_open())
    {
        cf << ticketManager.getCounter();
        cf.close();
    }
}

void ParkingLot::moveTicketToClosed(Ticket *ticket, time_t exitTime, int fee)
{
    // Delete from open
    string openPath = "Data/Tickets/open/ticket_" + to_string(ticket->getID()) + ".txt";
    remove(openPath.c_str());

    // Write to closed
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

void ParkingLot::addFloor()
{
    namespace fs = filesystem;
    floors.push_back(make_unique<Floor>(counter));

    // Persist floor marker
    string floorFile = "Data/Floors/floor_" + to_string(counter) + ".txt";
    ofstream ff(floorFile);
    if (ff.is_open())
    {
        ff << counter;
        ff.close();
    }

    // Create slot subdirectories
    vector<string> typeNames = {"BIKE", "CAR", "TRUCK"};
    for (auto &tn : typeNames)
    {
        string dir = "Data/Slots/floor_" + to_string(counter) + "/" + tn;
        fs::create_directories(dir);
        // Initialize counter
        ofstream cf(dir + "/counter.txt");
        if (cf.is_open())
        {
            cf << 0;
            cf.close();
        }
    }

    counter++;

    // Update floor counter
    ofstream cf("Data/Floors/id_counter.txt");
    if (cf.is_open())
    {
        cf << counter;
        cf.close();
    }

    cout << "Floor " << (counter - 1) << " added successfully.\n";
}

void ParkingLot::removeFloor(int id)
{
    namespace fs = filesystem;
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == id)
        {
            if (floors[i]->containsVehicles())
            {
                cout << "Floor " << id << " contains vehicles. Cannot be removed.\n";
                return;
            }

            // Delete floor marker
            string floorFile = "Data/Floors/floor_" + to_string(id) + ".txt";
            remove(floorFile.c_str());

            // Delete slot directory
            string slotDir = "Data/Slots/floor_" + to_string(id);
            if (fs::exists(slotDir))
            {
                fs::remove_all(slotDir);
            }

            floors.erase(floors.begin() + i);
            cout << "Floor " << id << " removed successfully.\n";
            return;
        }
    }
    cout << "Floor " << id << " doesn't exist.\n";
}

void ParkingLot::viewFloors()
{
    if (floors.empty())
    {
        cout << "No floors available.\n";
        return;
    }
    cout << "\n===== Available Floors =====\n";
    for (size_t i = 0; i < floors.size(); i++)
    {
        cout << "Floor ID: " << floors[i]->getID() << "\n";
    }
}

void ParkingLot::viewSlots(int floorId)
{
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == floorId)
        {
            cout << "\n===== Floor Slot Details =====\n";
            floors[i]->displaySlots();
            return;
        }
    }
    cout << "Floor " << floorId << " doesn't exist.\n";
}

void ParkingLot::viewFreeSlots(int floorId)
{
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == floorId)
        {
            cout << "\n===== Floor Slot Details =====\n";
            floors[i]->displayFreeSlots();
            return;
        }
    }
    cout << "Floor " << floorId << " doesn't exist.\n";
}

void ParkingLot::amountCollected()
{
    cout << "Total revenue collected: " << amount << "\n";
}

void ParkingLot::addSlots(int floorId, VehicleType type, int count)
{
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == floorId)
        {
            int startId = floors[i]->getCounter(type);
            floors[i]->addSlots(type, count);

            // Persist each new slot
            for (int s = startId; s < startId + count; s++)
            {
                saveSlotFile(floorId, type, s, false, "", -1);
            }

            // Update slot counter file
            string dir = "Data/Slots/floor_" + to_string(floorId) + "/" + vehicleTypeToString(type);
            filesystem::create_directories(dir);
            ofstream cf(dir + "/counter.txt");
            if (cf.is_open())
            {
                cf << floors[i]->getCounter(type);
                cf.close();
            }

            cout << count << " " << vehicleTypeToString(type) << " slots added to Floor " << floorId << ".\n";
            return;
        }
    }
    cout << "Floor " << floorId << " doesn't exist.\n";
}

void ParkingLot::removeSlot(int floorId, VehicleType type, int slotId)
{
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->getID() == floorId)
        {
            int prevCount = floors[i]->getSlotCount(type);
            floors[i]->removeSlot(type, slotId);
            if (floors[i]->getSlotCount(type) < prevCount)
            {
                deleteSlotFile(floorId, type, slotId);
            }
            return;
        }
    }
    cout << "Floor " << floorId << " doesn't exist.\n";
}

void ParkingLot::viewRates()
{
    cout << "\n===== Parking Rates =====\n";
    vector<string> typeNames = {"BIKE", "CAR", "TRUCK"};
    for (int t = 0; t < 3; t++)
    {
        VehicleType vt = static_cast<VehicleType>(t);
        cout << typeNames[t] << ": First Hour = " << rates[vt].first << ", Per 30min Block = " << rates[vt].second << "\n";
    }
}

void ParkingLot::setRate(VehicleType type, int firstHourFee, int halfHourBlockFee)
{
    rates[type] = {firstHourFee, halfHourBlockFee};
    saveRates();
    cout << "Rate updated for " << vehicleTypeToString(type) << ".\n";
}

int ParkingLot::enterVehicle(string vehicleNumber, VehicleType type)
{
    if (vehicleNumber.empty())
    {
        cout << "Invalid vehicle.\n";
        return -1;
    }
    if (ticketManager.getTicket(vehicleNumber) != nullptr)
    {
        cout << "Vehicle " << vehicleNumber << " is already parked.\n";
        return -1;
    }
    for (size_t i = 0; i < floors.size(); i++)
    {
        if (floors[i]->slotAvailable(type))
        {
            // Find the slot ID first
            int slotId = floors[i]->getSlotId(type);
            if (slotId == -1)
                continue;

            // Create ticket with correct slot ID
            Ticket *ticket = ticketManager.createTicket(vehicleNumber, type, floors[i]->getID(), slotId);

            // Fill the slot
            int filledSlotId = floors[i]->fillSlot(vehicleNumber, type, ticket->getID());
            if (filledSlotId == -1)
            {
                ticketManager.removeTicket(vehicleNumber);
                continue;
            }

            // Persist
            saveOpenTicket(ticket);
            writeActiveIndex(vehicleNumber, ticket->getID());
            saveSlotFile(floors[i]->getID(), type, filledSlotId, true, vehicleNumber, ticket->getID());

            cout << "Vehicle " << vehicleNumber << " parked. Ticket ID: " << ticket->getID() << "\n";
            return ticket->getID();
        }
    }
    cout << "No parking slot available for vehicle " << vehicleNumber << ".\n";
    return -1;
}

int ParkingLot::exitVehicle(string vehicleNumber)
{
    if (vehicleNumber.empty())
    {
        cout << "Invalid vehicle.\n";
        return 0;
    }

    Ticket *ticket = ticketManager.getTicket(vehicleNumber);
    if (ticket == nullptr)
    {
        cout << "Vehicle " << vehicleNumber << " is not parked in the lot.\n";
        return 0;
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

    // Free the slot
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

    // Move ticket to closed
    ticket->setExit(exitTime, fee);
    moveTicketToClosed(ticket, exitTime, fee);
    deleteActiveIndex(vehicleNumber);

    // Update revenue
    amount += fee;
    saveRevenue();

    // Remove from in-memory ticket manager
    ticketManager.removeTicket(vehicleNumber);

    return fee;
}