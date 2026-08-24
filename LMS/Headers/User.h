#ifndef USER_H
#define USER_H

#include <string>
using namespace std;
#include "Library.h"
#include "Account.h"

class User
{
private:
    int UserId;
    string password;

public:
    string role;
    string name;
    int getUserId();
    void setUserId(int id);
    string getPassword();
    bool correctPassword(string pass);
    string encryptedPassword(string pass);
    void setPassword(string pass);
    void fetchPassword(string pass);
    void updateStatustoAvailable(int bookId);
    void updateStatustoBorrowed(int bookId);
    virtual bool accountExists(int id) = 0;
    virtual void fetchData(int id) = 0;
    virtual void newUser(string name, string pass) = 0;
    virtual void deleteAccount(int id) = 0;
    virtual ~User() {}
};

#endif