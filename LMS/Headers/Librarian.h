#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "User.h"

class Librarian : public User
{
public:
    Library lib;
    int Id;
    int getPrevId();
    void updateId();
    bool accountExists(int id) override;
    void fetchData(int id) override;
    void addBook();
    void removeBook();
    void addUser();
    void removeUser();
    void newUser(string name, string pass) override;
    void deleteAccount(int id) override;
};

#endif