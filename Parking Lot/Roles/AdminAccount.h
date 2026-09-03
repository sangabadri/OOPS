#pragma once

#include <string>
#include <iostream>
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
    string getName();
    int getPrevId();
    void updateId();
    bool accountExists(int id);
    void fetchData(int id);
    void newUser(string name, string pass);
    bool correctPassword(string pass);
    string encryptedPassword(string pass);
    void setPassword(string pass);
    void fetchPassword(string pass);
    static bool anyAccountExists();
};
