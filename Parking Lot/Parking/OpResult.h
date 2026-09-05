#pragma once

#include <string>

using namespace std;

struct OpResult
{
    bool success;
    string message;
    int value = -1;
};
