#pragma once

#include <string>

using namespace std;

enum VehicleType
{
    BIKE,
    CAR,
    TRUCK
};

string vehicleTypeToString(VehicleType type);
VehicleType stringToVehicleType(string str);

class Vehicle
{
private:
    string vehicleNumber;
    VehicleType type;

public:
    Vehicle(string vehicleNumber, VehicleType type);
    VehicleType getType();
    string getVehicleNumber();
};