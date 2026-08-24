#ifndef FACULTY_H
#define FACULTY_H

#include "User.h"

class Faculty : public User
{
public:
    int getOverdues();
    int Id;
    int getPrevId();
    void updateId();
    void borrowBook(int bookId);
    void returnBook(int bookId);
    void viewBorrowedBooks();
    void viewHistory();
    bool accountExists(int id) override;
    void fetchData(int id) override;
    void newUser(string name, string pass) override;
    void deleteAccount(int id) override;
    Account acc;
};

#endif