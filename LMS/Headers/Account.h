#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account
{
private:
    int fine;
    int UserId;

public:
    static int SecPerDay;
    string role;
    int getUserId();
    void setUserId(int id);
    int getFine();
    void updateFine();
    void setFine(int money);
    int bookLimit;
    int timeLimit;
    int OverdueDays;
    int bookCount;
    void fetchData(int id);
    void loadData(int id);
    void loadBorrowedBook(int bookId);
    void loadBookHistory(int bookId);
    void viewBorrowedBooks();
};

#endif
