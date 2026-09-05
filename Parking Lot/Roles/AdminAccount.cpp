#include "AdminAccount.h"

int AdminAccount::getUserId()
{
    return UserId;
}

int AdminAccount::getPrevId()
{
    string filename = "Data/Users/Admin/id_counter.txt";
    ifstream file(filename);
    int prevId;
    if (file.is_open())
    {
        file >> prevId;
        file.close();
    }
    else
    {
        prevId = 100;
    }
    return prevId;
}

OpResult AdminAccount::updateId()
{
    // NOTE: not safe for concurrent processes writing to this file — no locking yet.
    string filename = "Data/Users/Admin/id_counter.txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << UserId;
        file.close();
        return {true, ""};
    }
    return {false, "Failed to update admin ID counter."};
}

bool AdminAccount::accountExists(int id)
{
    string filename = "Data/Users/Admin/user_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        file.close();
        return true;
    }
    return false;
}

OpResult AdminAccount::fetchData(int id)
{
    string filename = "Data/Users/Admin/user_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        string temp;
        UserId = id;
        getline(file, role);
        getline(file, name);
        getline(file, temp);
        fetchPassword(temp);
        file.close();
        return {true, ""};
    }
    return {false, "Failed to load account data."};
}

OpResult AdminAccount::newUser(string name, string pass)
{
    filesystem::create_directories("Data/Users/Admin");
    int Id = getPrevId();

    this->name = name;
    setPassword(pass);
    UserId = Id;
    role = "Admin";

    string filename = "Data/Users/Admin/user_" + to_string(Id) + ".txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << role << "\n"
             << this->name << "\n"
             << password;
        file.close();

        UserId = Id + 1;
        updateId();
        UserId = Id;

        return {true, "Admin account created! Your UserId: " + to_string(Id) + "\nRemember this UserId, you will have to login using this.", Id};
    }

    return {false, "Failed to create admin account."};
}

bool AdminAccount::correctPassword(string pass)
{
    return encryptedPassword(pass) == password;
}

string AdminAccount::encryptedPassword(string pass)
{
    string salt1 = "abc";
    string salt2 = "123";
    return (salt1 + pass + salt2);
}

void AdminAccount::setPassword(string pass)
{
    password = encryptedPassword(pass);
}

void AdminAccount::fetchPassword(string pass)
{
    password = pass;
}

bool AdminAccount::anyAccountExists()
{
    return AdminAccount().getPrevId() > 100;
}
