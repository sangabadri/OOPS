#include "Parking/ParkingLot.h"
#include "Roles/Admin.h"
#include "Roles/Entry.h"
#include "Roles/Exit.h"
#include "Roles/AdminAccount.h"
#include "InputUtil.h"
#include <iostream>
#include <string>

using namespace std;

void MainMenu();
void AdminLogin(Admin &admin);
void createAdminAccount();
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

    while (true)
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
        int role = readInt("Enter choice: ");

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
                createAdminAccount();
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
    }
}

void createAdminAccount()
{
    cout << "\n===== Create Admin Account =====\n";
    string name, pass;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> pass;
    AdminAccount acc;
    OpResult r = acc.newUser(name, pass);
    cout << r.message << "\n";
}

void AdminLogin(Admin &admin)
{
    AdminAccount acc;
    int userId = -1;

    bool idOk = retryLoop(3, [&](int attempt, int maxAttempts) -> bool {
        string id;
        cout << "Enter your UserId : ";
        cin >> id;
        cout << "\n";

        int parsed;
        try
        {
            parsed = stoi(id);
        }
        catch (...)
        {
            if (attempt == maxAttempts)
                cout << "\nInvalid input.";
            else
                cout << "\nInvalid input. Try again.\n\n";
            return false;
        }

        if (acc.accountExists(parsed))
        {
            acc.fetchData(parsed);
            userId = parsed;
            return true;
        }
        else
        {
            if (attempt == maxAttempts)
                cout << "\nUserId doesn't exist.";
            else
                cout << "\nUserId doesn't exist. Try again.\n\n";
            return false;
        }
    });

    if (!idOk)
    {
        cout << "\nToo many failed attempts.";
        cout << "\nSession ended.\n\n";
        return;
    }

    bool passOk = retryLoop(3, [&](int attempt, int maxAttempts) -> bool {
        string pass;
        cout << "Enter your password : ";
        cin >> pass;
        cout << "\n";

        if (acc.correctPassword(pass))
        {
            return true;
        }
        else
        {
            if (attempt == maxAttempts)
                cout << "\nIncorrect Password.";
            else
                cout << "\nIncorrect Password. Try again.\n\n";
            return false;
        }
    });

    if (!passOk)
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
    while (true)
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
        int choice = readInt("Enter choice: ");

        if (choice == 1)
        {
            admin.addFloor();
        }
        else if (choice == 2)
        {
            int floorId = readInt("Floor ID: ");
            int typeChoice = readInt("Vehicle Type (0-Bike, 1-Car, 2-Truck): ", 0, 2);
            int count = readInt("Count: ");
            admin.addSlots(floorId, static_cast<VehicleType>(typeChoice), count);
        }
        else if (choice == 3)
        {
            int floorId = readInt("Floor ID: ");
            admin.removeFloor(floorId);
        }
        else if (choice == 4)
        {
            int floorId = readInt("Floor ID: ");
            int typeChoice = readInt("Vehicle Type (0-Bike, 1-Car, 2-Truck): ", 0, 2);
            int slotId = readInt("Slot ID: ");
            admin.removeSlot(floorId, static_cast<VehicleType>(typeChoice), slotId);
        }
        else if (choice == 5)
        {
            admin.viewFloors();
        }
        else if (choice == 6)
        {
            int floorId = readInt("Floor ID: ");
            admin.viewSlots(floorId);
        }
        else if (choice == 7)
        {
            int floorId = readInt("Floor ID: ");
            admin.viewFreeSlots(floorId);
        }
        else if (choice == 8)
        {
            admin.viewRates();
        }
        else if (choice == 9)
        {
            int typeChoice = readInt("Vehicle Type (0-Bike, 1-Car, 2-Truck): ", 0, 2);
            int firstHour = readInt("First Hour Fee: ");
            int halfHour = readInt("Per 30-min Block Fee: ");
            admin.setRate(static_cast<VehicleType>(typeChoice), firstHour, halfHour);
        }
        else if (choice == 10)
        {
            admin.amountCollected();
        }
        else if (choice == 11)
        {
            createAdminAccount();
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
    }
}

void EntryRoles(Entry &entry)
{
    while (true)
    {
        cout << "\n===== Entry Operator =====\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Logout\n";
        int choice = readInt("Enter choice: ");

        if (choice == 1)
        {
            string vehicleNumber = readSafeToken("Vehicle Number: ");
            int typeChoice = readInt("Vehicle Type (0-Bike, 1-Car, 2-Truck): ", 0, 2);
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
    }
}

void ExitRoles(Exit &exitOperator)
{
    while (true)
    {
        cout << "\n===== Exit Operator =====\n";
        cout << "1. Process Vehicle Exit\n";
        cout << "2. Logout\n";
        int choice = readInt("Enter choice: ");

        if (choice == 1)
        {
            string vehicleNumber = readSafeToken("Vehicle Number: ");
            exitOperator.exitVehicle(vehicleNumber);
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
    }
}
