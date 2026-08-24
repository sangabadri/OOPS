#include "Librarian.h"
#include "Student.h"
#include "Faculty.h"
#include "Utility.h"
#include <iostream>
#include <fstream>
#include <string>

int Librarian ::getPrevId()
{
    string filename = "Users/Librarian/id_counter.txt";
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

void Librarian ::updateId()
{
    string filename = "Users/Librarian/id_counter.txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << Id;
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while updating Id. Librarian.updateId.\n\n";
    }
    return;
}

void Librarian ::addBook()
{
    lib.addBook();
    return;
}

void Librarian ::removeBook()
{
    lib.removeBook();
    return;
}

void Librarian ::fetchData(int id)
{
    string filename = "Users/Librarian/user_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        string temp;
        setUserId(id);
        getline(file, role);
        getline(file, name);
        getline(file, temp);
        fetchPassword(temp);
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while fetching data. Librarian.fetchData.\n\n";
    }
    return;
}

void Librarian ::newUser(string name, string pass)
{
    Id = getPrevId();

    this->name = name;
    setPassword(pass);
    setUserId(Id);
    role = "Librarian";

    string filename = "Users/Librarian/user_" + to_string(Id) + ".txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << role << "\n"
             << this->name << "\n"
             << getPassword();
        file.close();
        cout << "\nLibrarian account created!\n";
        cout << "Your UserId : " << getUserId() << "\n";
        cout << "Remember this UserId, you will have to login using this.\n\n";
    }
    else
    {
        cout << "\nSomething went wrong while creating a new user. Librarian.newUser.\n\n";
    }

    Id = getPrevId() + 1;
    updateId();

    return;
}

bool Librarian ::accountExists(int id)
{
    string filename = "Users/Librarian/user_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        file.close();
        return true;
    }
    return false;
}

void Librarian ::addUser()
{
    string role = chooseRole();
    string name;
    string pass;
    if (role == "1")
    {
        cout << "Enter your name : ";
        cin >> name;
        cout << "\n";
        cout << "Enter password : ";
        cin >> pass;
        cout << "\n";
        Student s1;
        s1.newUser(name, pass);
    }
    else if (role == "2")
    {
        cout << "Enter your name : ";
        cin >> name;
        cout << "\n";
        cout << "Enter password : ";
        cin >> pass;
        cout << "\n";
        Faculty f1;
        f1.newUser(name, pass);
    }
    else if (role == "3")
    {
        cout << "Enter your name : ";
        cin >> name;
        cout << "\n";
        cout << "Enter password : ";
        cin >> pass;
        cout << "\n";
        Librarian l1;
        l1.newUser(name, pass);
    }
    else
    {
        cout << "\nChoose valid Role.\n\n";
    }
    return;
}

void Librarian ::removeUser()
{
    string role = chooseRole();
    if (role == "1")
    {
        cout << "Enter UserId : ";
        int id;
        cin >> id;
        cout << "\n";
        Student s1;
        s1.deleteAccount(id);
    }
    else if (role == "2")
    {
        cout << "Enter UserId : ";
        int id;
        cin >> id;
        cout << "\n";
        Faculty f1;
        f1.deleteAccount(id);
    }
    else if (role == "3")
    {
        cout << "Enter UserId : ";
        int id;
        cin >> id;
        cout << "\n";
        deleteAccount(id);
    }
    else
    {
        cout << "\nChoose valid Role.\n\n";
    }
    return;
}

void Librarian ::deleteAccount(int id)
{
    string filename = "Users/Librarian/user_" + to_string(id) + ".txt";
    if (getUserId() == id)
    {
        cout << "\nYou cannot remove yourself. If you want to delete your account, ask other Librarians.\n\n";
    }
    else
    {
        if (accountExists(id))
        {
            if (remove((filename).c_str()))
            {
                cout << "\nSomething went wrong while deleting filenam4. Librarian.deleteAccount.\n\n";
                return;
            }
            cout << "\nYou have successfully removed the Librarian with UserId : " << to_string(id) << "\n\n";
        }
        else
        {
            cout << "\nUser doesn't exist to remove.\n\n";
        }
    }
}
