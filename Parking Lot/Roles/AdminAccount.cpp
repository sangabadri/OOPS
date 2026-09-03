#include "AdminAccount.h"

int AdminAccount::getUserId()
{
    return UserId;
}

string AdminAccount::getName()
{
    return name;
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

void AdminAccount::updateId()
{
    string filename = "Data/Users/Admin/id_counter.txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << UserId;
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while updating Id. AdminAccount.updateId.\n\n";
    }
    return;
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

void AdminAccount::fetchData(int id)
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
    }
    else
    {
        cout << "\nSomething went wrong while fetching data. AdminAccount.fetchData.\n\n";
    }
    return;
}

void AdminAccount::newUser(string name, string pass)
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
        cout << "\nAdmin account created!\n";
        cout << "Your UserId : " << UserId << "\n";
        cout << "Remember this UserId, you will have to login using this.\n\n";
    }
    else
    {
        cout << "\nSomething went wrong while creating a new user. AdminAccount.newUser.\n\n";
    }

    UserId = Id + 1;
    updateId();
    UserId = Id;

    return;
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
    return;
}

void AdminAccount::fetchPassword(string pass)
{
    password = pass;
    return;
}

bool AdminAccount::anyAccountExists()
{
    string filename = "Data/Users/Admin/id_counter.txt";
    ifstream file(filename);
    if (file.is_open())
    {
        int id;
        file >> id;
        file.close();
        return id > 100;
    }
    return false;
}
