#pragma once

#include "../Parking/OpResult.h"
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;

class AdminAccount
{
private:
    int UserId;
    string name;
    string password;
    string role;

public:
    int getUserId();
    int getPrevId();
    OpResult updateId();
    bool accountExists(int id);
    OpResult fetchData(int id);
    OpResult newUser(string name, string pass);
    bool correctPassword(string pass);
    string encryptedPassword(string pass);
    void setPassword(string pass);
    void fetchPassword(string pass);
    static bool anyAccountExists();
};
