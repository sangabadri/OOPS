#include "Account.h"
#include <iostream>
#include <fstream>
#include <ctime>

int Account ::SecPerDay = 86400;

int Account ::getUserId()
{
    return UserId;
}

void Account ::setUserId(int id)
{
    UserId = id;
    return;
}

int Account ::getFine()
{
    return fine;
}

void Account ::updateFine()
{
    if (bookCount)
    {
        int id[bookCount];
        int Time[bookCount];
        string filename = "Users/" + role + "/borrowed_" + to_string(getUserId()) + ".txt";
        ifstream file(filename);
        if (file.is_open())
        {
            for (int i = 0; i < bookCount; i++)
            {
                string temp;
                getline(file, temp);
                id[i] = stoi(temp);
                getline(file, temp);
                Time[i] = stoi(temp);
            }
            file.close();
        }
        else
        {
            cout << "\nSomething went wrong while fetching data. Account.updateFine.\n\n";
            return;
        }
        for (int i = 0; i < bookCount; i++)
        {
            int now = (int)time(0);
            int days = (now - Time[i]) / SecPerDay;
            if (days > timeLimit)
            {
                fine += 10 * (days - timeLimit);
                OverdueDays += (days - timeLimit);
                Time[i] += (days - timeLimit) * SecPerDay;
            }
        }
        ofstream fout(filename);
        if (fout.is_open())
        {
            for (int i = 0; i < bookCount; i++)
            {
                fout << id[i] << "\n"
                     << Time[i] << "\n";
            }
            fout.close();
        }
        else
        {
            cout << "\nSomething went wrong while updating fine. Account.updateFine.\n\n";
            return;
        }
        loadData(getUserId());
    }
    return;
}

void Account ::setFine(int money)
{
    fine = money;
    return;
}

void Account ::fetchData(int id)
{
    string filename = "Users/" + role + "/account_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        string temp;
        getline(file, temp);
        setFine(stoi(temp));
        getline(file, temp);
        OverdueDays = stoi(temp);
        getline(file, temp);
        bookCount = stoi(temp);

        file.close();
    }
    else
    {
        cout << "Something went wrong while fetching account data. Account.fetchData.\n\n";
    }
    return;
}

void Account ::loadData(int id)
{
    string filename = "Users/" + role + "/account_" + to_string(id) + ".txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << getFine() << "\n"
             << OverdueDays << "\n"
             << bookCount;
        file.close();
    }
    else
    {
        cout << "Something went wrong while loading data. Account.loadData.\n\n";
    }
    return;
}

void Account ::loadBorrowedBook(int bookId)
{
    string filename = "Users/" + role + "/borrowed_" + to_string(getUserId()) + ".txt";
    ofstream file(filename, ios::app);
    if (file.is_open())
    {
        int now = (int)time(0);
        file << bookId << "\n"
             << now << "\n";
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while storing borrowed books. Account.loadBorrowedBooks.\n\n";
    }
    return;
}

void Account ::loadBookHistory(int bookId)
{
    string filename = "Users/" + role + "/history_" + to_string(getUserId()) + ".txt";
    ofstream file(filename, ios::app);
    if (file.is_open())
    {
        file << bookId << "\n";
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while storing history. Account.loadBookHistory.\n\n";
    }
}

void Account ::viewBorrowedBooks()
{
    if (bookCount)
    {
        string filename = "Users/" + role + "/borrowed_" + to_string(getUserId()) + ".txt";
        ifstream file(filename);
        if (file.is_open())
        {
            string temp;
            while (getline(file, temp))
            {
                cout << temp << "\n";
                getline(file, temp);
            }
            cout << "\n";
            file.close();
        }
    }
    else
    {
        cout << "\nYou didn't borrow any books at the moment.\n\n";
    }
    return;
}