#include "VehicleType.h"

string vehicleTypeToString(VehicleType type)
{
    if (type == BIKE) return "BIKE";
    if (type == CAR) return "CAR";
    if (type == TRUCK) return "TRUCK";
    return "UNKNOWN";
}

VehicleType stringToVehicleType(string str)
{
    if (str == "BIKE") return BIKE;
    if (str == "CAR") return CAR;
    if (str == "TRUCK") return TRUCK;
    return BIKE;
}
