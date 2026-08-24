#include "User.h"
#include <iostream>
#include <fstream>
#include <string>

int User ::getUserId()
{
    return UserId;
}

void User ::setUserId(int id)
{
    UserId = id;
    return;
}

string User ::getPassword()
{
    return password;
}

bool User ::correctPassword(string pass)
{
    return encryptedPassword(pass) == getPassword();
}

string User ::encryptedPassword(string pass)
{
    string salt1 = "abc";
    string salt2 = "123";
    return (salt1 + pass + salt2);
}

void User ::setPassword(string pass)
{
    password = encryptedPassword(pass);
    return;
}

void User ::fetchPassword(string pass)
{
    password = pass;
    return;
}


void User ::updateStatustoAvailable(int bookId)
{
    Library lib;
    lib.updateStatustoAvailable(bookId);
    return;
}

void User ::updateStatustoBorrowed(int bookId)
{
    Library lib;
    lib.updateStatustoBorrowed(bookId);
}
