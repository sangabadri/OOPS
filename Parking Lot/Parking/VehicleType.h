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
