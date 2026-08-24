#pragma once

#include <string>

using namespace std;

enum VehicleType
{
    BIKE,
    CAR,
    TRUCK
};

enum VehicleCost
{
    BIKE_COST = 20,
    CAR_COST = 40,
    TRUCK_COST = 60
};

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