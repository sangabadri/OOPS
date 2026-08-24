#include "Parking/ParkingLot.h"
#include "Roles/Admin.h"
#include "Roles/Entry.h"
#include "Roles/Exit.h"
#include <iostream>
#include <vector>

using namespace std;

void initializeLot(ParkingLot &parkingLot);
void clearParkedVehicles(vector<Vehicle *> &parkedVehicles);
int chooseRole();
void Login();
void AddFloor(Admin &admin);
void AddSlots(Admin &admin);
void ParkVehicle(Entry &entry, vector<Vehicle *> &parkedVehicles);
void RemoveVehicle(Exit &exitOperator, vector<Vehicle *> &parkedVehicles);
void AdminRoles(Admin &admin);
void EntryRoles(Entry &entry, vector<Vehicle *> &parkedVehicles);
void ExitRoles(Exit &exitOperator, vector<Vehicle *> &parkedVehicles);

int main()
{
    cout << "\nWelcome to Parking Lot Management System.\n\n";
    Login();
    cout << "\nThank you for using our Parking Lot Management System.\n\n";
    return 0;
}

void initializeLot(ParkingLot &parkingLot)
{
    parkingLot.addFloor();
    parkingLot.addSlots(0, BIKE, 3);
    parkingLot.addSlots(0, CAR, 3);
    parkingLot.addSlots(0, TRUCK, 2);
}

void clearParkedVehicles(vector<Vehicle *> &parkedVehicles)
{
    for (size_t i = 0; i < parkedVehicles.size(); i++)
    {
        delete parkedVehicles[i];
    }
    parkedVehicles.clear();
}

int chooseRole()
{
    int role;
    cout << "================================\n";
    cout << "       PARKING LOT SYSTEM\n";
    cout << "================================\n";
    cout << "1. Entry Operator\n";
    cout << "2. Exit Operator\n";
    cout << "3. Admin\n";
    cout << "4. Exit\n";
    cout << "Enter choice: ";
    cin >> role;
    return role;
}

void Login()
{
    ParkingLot parkingLot;
    Admin admin(parkingLot);
    Entry entry(parkingLot);
    Exit exitOperator(parkingLot);
    vector<Vehicle *> parkedVehicles;

    initializeLot(parkingLot);

    int role = chooseRole();
    while (role != 4)
    {
        if (role == 1)
        {
            EntryRoles(entry, parkedVehicles);
        }
        else if (role == 2)
        {
            ExitRoles(exitOperator, parkedVehicles);
        }
        else if (role == 3)
        {
            AdminRoles(admin);
        }
        else
        {
            cout << "Role not available.\n";
        }

        role = chooseRole();
    }

    clearParkedVehicles(parkedVehicles);
}

void AddFloor(Admin &admin)
{
    admin.addFloor();
}

void AddSlots(Admin &admin)
{
    int floorId;
    int typeChoice;
    int count;

    cout << "Floor ID: ";
    cin >> floorId;
    cout << "Vehicle Type (0-Bike, 1-Car, 2-Truck): ";
    cin >> typeChoice;
    cout << "Count: ";
    cin >> count;

    admin.addSlots(floorId, static_cast<VehicleType>(typeChoice), count);
}

void ParkVehicle(Entry &entry, vector<Vehicle *> &parkedVehicles)
{
    string vehicleNumber;
    int typeChoice;

    cout << "Vehicle Number: ";
    cin >> vehicleNumber;
    cout << "Vehicle Type (0-Bike, 1-Car, 2-Truck): ";
    cin >> typeChoice;

    Vehicle *vehicle = new Vehicle(vehicleNumber, static_cast<VehicleType>(typeChoice));
    if (entry.enterVehicle(vehicle))
    {
        parkedVehicles.push_back(vehicle);
    }
    else
    {
        delete vehicle;
    }
}

void RemoveVehicle(Exit &exitOperator, vector<Vehicle *> &parkedVehicles)
{
    string vehicleNumber;

    cout << "Vehicle Number: ";
    cin >> vehicleNumber;

    for (size_t i = 0; i < parkedVehicles.size(); i++)
    {
        if (parkedVehicles[i]->getVehicleNumber() == vehicleNumber)
        {
            if (exitOperator.exitVehicle(parkedVehicles[i]))
            {
                delete parkedVehicles[i];
                parkedVehicles.erase(parkedVehicles.begin() + i);
                return;
            }

            cout << "Vehicle " << vehicleNumber << " is not parked in the lot.\n";
            return;
        }
    }

    cout << "Vehicle " << vehicleNumber << " is not parked in the lot.\n";
}

void AdminRoles(Admin &admin)
{
    int choice;
    do
    {
        cout << "\n===== Admin =====\n";
        cout << "1. Add Floor\n";
        cout << "2. Add Parking Slot\n";
        cout << "3. Remove Floor\n";
        cout << "4. Remove Parking Slot\n";
        cout << "5. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            AddFloor(admin);
        }
        else if (choice == 2)
        {
            AddSlots(admin);
        }
        else if (choice == 3)
        {
            int floorId;
            cout << "Floor ID: ";
            cin >> floorId;
            admin.removeFloor(floorId);
        }
        else if (choice == 4)
        {
            int floorId;
            int typeChoice;
            int slotId;

            cout << "Floor ID: ";
            cin >> floorId;
            cout << "Vehicle Type (0-Bike, 1-Car, 2-Truck): ";
            cin >> typeChoice;
            cout << "Slot ID: ";
            cin >> slotId;

            admin.removeSlot(floorId, static_cast<VehicleType>(typeChoice), slotId);
        }
        else if (choice == 5)
        {
            cout << "Logging out...\n";
            return;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    } while (true);
}

void EntryRoles(Entry &entry, vector<Vehicle *> &parkedVehicles)
{
    int choice;
    do
    {
        cout << "\n===== Entry Operator =====\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            ParkVehicle(entry, parkedVehicles);
        }
        else if (choice == 2)
        {
            cout << "Logging out...\n";
            return;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    } while (true);
}

void ExitRoles(Exit &exitOperator, vector<Vehicle *> &parkedVehicles)
{
    int choice;
    do
    {
        cout << "\n===== Exit Operator =====\n";
        cout << "1. Process Vehicle Exit\n";
        cout << "2. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            RemoveVehicle(exitOperator, parkedVehicles);
        }
        else if (choice == 2)
        {
            cout << "Logging out...\n";
            return;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    } while (true);
}
