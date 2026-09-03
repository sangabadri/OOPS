#include "Parking/ParkingLot.h"
#include "Roles/Admin.h"
#include "Roles/Entry.h"
#include "Roles/Exit.h"
#include "Roles/AdminAccount.h"
#include <iostream>
#include <string>

using namespace std;

void MainMenu();
void AdminLogin(Admin &admin);
void AdminBootstrap();
void AdminRoles(Admin &admin);
void EntryRoles(Entry &entry);
void ExitRoles(Exit &exitOperator);

int main()
{
    cout << "\nWelcome to Parking Lot Management System.\n\n";
    MainMenu();
    cout << "\nThank you for using our Parking Lot Management System.\n\n";
    return 0;
}

void MainMenu()
{
    ParkingLot parkingLot;
    Admin admin(parkingLot);
    Entry entry(parkingLot);
    Exit exitOperator(parkingLot);

    int role;
    do
    {
        cout << "================================\n";
        cout << "       PARKING LOT SYSTEM\n";
        cout << "================================\n";
        cout << "1. Entry Operator\n";
        cout << "2. Exit Operator\n";

        if (AdminAccount::anyAccountExists())
        {
            cout << "3. Admin Login\n";
        }
        else
        {
            cout << "3. Create First Admin Account\n";
        }

        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> role;

        if (role == 1)
        {
            EntryRoles(entry);
        }
        else if (role == 2)
        {
            ExitRoles(exitOperator);
        }
        else if (role == 3)
        {
            if (AdminAccount::anyAccountExists())
            {
                AdminLogin(admin);
            }
            else
            {
                AdminBootstrap();
            }
        }
        else if (role == 4)
        {
            break;
        }
        else
        {
            cout << "Role not available.\n";
        }
    } while (true);
}

void AdminBootstrap()
{
    cout << "\n===== Create First Admin Account =====\n";
    string name, pass;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> pass;
    AdminAccount acc;
    acc.newUser(name, pass);
}

void AdminLogin(Admin &admin)
{
    AdminAccount acc;
    string id;
    string pass;
    int i;

    i = 0;
    while (i < 3)
    {
        try
        {
            cout << "Enter your UserId : ";
            cin >> id;
            cout << "\n";
            stoi(id);
        }
        catch (...)
        {
            i++;
            if (i == 3)
            {
                cout << "\nInvalid input.";
            }
            else
            {
                cout << "\nInvalid input. Try again.\n\n";
            }
            continue;
        }
        if (acc.accountExists(stoi(id)))
        {
            acc.fetchData(stoi(id));
            break;
        }
        else
        {
            i++;
            if (i == 3)
            {
                cout << "\nUserId doesn't exist.";
            }
            else
            {
                cout << "\nUserId doesn't exist. Try again.\n\n";
            }
        }
    }
    if (i == 3)
    {
        cout << "\nToo many failed attempts.";
        cout << "\nSession ended.\n\n";
        return;
    }

    i = 0;
    while (i < 3)
    {
        cout << "Enter your password : ";
        cin >> pass;
        cout << "\n";
        if (acc.correctPassword(pass))
        {
            break;
        }
        else
        {
            i++;
            if (i == 3)
            {
                cout << "\nIncorrect Password.";
            }
            else
            {
                cout << "\nIncorrect Password. Try again.\n\n";
            }
        }
    }
    if (i == 3)
    {
        cout << "\nToo many failed attempts.";
        cout << "\nSession ended.\n\n";
        return;
    }

    cout << "\nYou have successfully logged into your Admin account with UserId : " << acc.getUserId() << "\n\n";
    AdminRoles(admin);
}

void AdminRoles(Admin &admin)
{
    int choice;
    do
    {
        cout << "\n===== Admin Menu =====\n";
        cout << "1. Add Floor\n";
        cout << "2. Add Parking Slots\n";
        cout << "3. Remove Floor\n";
        cout << "4. Remove Parking Slot\n";
        cout << "5. View Floors\n";
        cout << "6. View Slots\n";
        cout << "7. View Free Slots\n";
        cout << "8. View Rates\n";
        cout << "9. Edit Rates\n";
        cout << "10. View Revenue\n";
        cout << "11. Create Admin Account\n";
        cout << "12. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            admin.addFloor();
        }
        else if (choice == 2)
        {
            int floorId, typeChoice, count;
            cout << "Floor ID: ";
            cin >> floorId;
            cout << "Vehicle Type (0-Bike, 1-Car, 2-Truck): ";
            cin >> typeChoice;
            cout << "Count: ";
            cin >> count;
            admin.addSlots(floorId, static_cast<VehicleType>(typeChoice), count);
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
            int floorId, typeChoice, slotId;
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
            admin.viewFloors();
        }
        else if (choice == 6)
        {
            int floorId;
            cout << "Floor ID: ";
            cin >> floorId;
            admin.viewSlots(floorId);
        }
        else if (choice == 7)
        {
            int floorId;
            cout << "Floor ID: ";
            cin >> floorId;
            admin.viewFreeSlots(floorId);
        }
        else if (choice == 8)
        {
            admin.viewRates();
        }
        else if (choice == 9)
        {
            int typeChoice, firstHour, halfHour;
            cout << "Vehicle Type (0-Bike, 1-Car, 2-Truck): ";
            cin >> typeChoice;
            cout << "First Hour Fee: ";
            cin >> firstHour;
            cout << "Per 30-min Block Fee: ";
            cin >> halfHour;
            admin.setRate(static_cast<VehicleType>(typeChoice), firstHour, halfHour);
        }
        else if (choice == 10)
        {
            admin.amountCollected();
        }
        else if (choice == 11)
        {
            cout << "\nCreating a new Admin account.\n";
            string name, pass;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter password: ";
            cin >> pass;
            AdminAccount newAcc;
            newAcc.newUser(name, pass);
        }
        else if (choice == 12)
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

void EntryRoles(Entry &entry)
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
            string vehicleNumber;
            int typeChoice;
            cout << "Vehicle Number: ";
            cin >> vehicleNumber;
            cout << "Vehicle Type (0-Bike, 1-Car, 2-Truck): ";
            cin >> typeChoice;
            entry.enterVehicle(vehicleNumber, static_cast<VehicleType>(typeChoice));
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

void ExitRoles(Exit &exitOperator)
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
            string vehicleNumber;
            cout << "Vehicle Number: ";
            cin >> vehicleNumber;
            int fee = exitOperator.exitVehicle(vehicleNumber);
            if (fee > 0)
            {
                cout << "Fee charged: " << fee << "\n";
            }
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
