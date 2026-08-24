#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User
{
public:
    int Fine();
    void payFine();
    int getOverdues();
    int Id;
    int getPrevId();
    void updateId();
    bool accountExists(int id) override;
    void fetchData(int id) override;
    void borrowBook(int bookId);
    void returnBook(int bookId);
    void viewBorrowedBooks();
    void viewHistory();
    void newUser(string name, string pass) override;
    void deleteAccount(int id) override;
    Account acc;
};

#endif
