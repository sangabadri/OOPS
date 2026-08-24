#include "Faculty.h"
#include <iostream>
#include <fstream>
#include <string>

int Faculty ::getOverdues()
{
    acc.updateFine();
    return acc.OverdueDays;
}

int Faculty ::getPrevId()
{
    string filename = "Users/Faculty/id_counter.txt";
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

void Faculty ::updateId()
{
    string filename = "Users/Faculty/id_counter.txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << Id;
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while updating Id. Faculty.updateId.\n\n";
    }
    return;
}

bool Faculty ::accountExists(int id)
{
    string filename = "Users/Faculty/user_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        file.close();
        return true;
    }
    return false;
}

void Faculty ::fetchData(int id)
{
    string filename = "Users/Faculty/user_" + to_string(id) + ".txt";
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

        acc.role = "Faculty";
        acc.bookLimit = 5;
        acc.timeLimit = 30;
        acc.setUserId(id);
        acc.fetchData(id);
    }
    else
    {
        cout << "\nSomething went wrong while fetching data. Faculty.fetchData.\n\n";
    }
    return;
}

void Faculty ::borrowBook(int bookId)
{
    Book book;
    if (!book.bookExists(bookId))
    {
        cout << "\nBook is not registered in the library at the moment.\n\n";
        return;
    }
    book.fetchData(bookId);
    acc.updateFine();
    if (acc.OverdueDays >= 60)
    {
        cout << "\nYour Overdue Days have exceeded 60. You can no longer borrow books.\n\n";
        return;
    }
    else if (acc.bookCount >= acc.bookLimit)
    {
        cout << "\nYou have reached borrowing limit. Please submit atleast one book to borrow other books.\n\n";
        return;
    }
    else if (book.bookStatus != "Available")
    {
        cout << "\nCannot borrow book at the moment, it has been borrowed.\n\n";
        return;
    }
    else
    {
        acc.loadBorrowedBook(bookId);
        acc.bookCount += 1;
        acc.loadData(getUserId());
        updateStatustoBorrowed(bookId);
        cout << "\nYou have successfully borrowed the book.\n\n";
    }
    return;
}

void Faculty ::returnBook(int bookId)
{
    if (acc.bookCount)
    {
        int id[acc.bookCount];
        int Time[acc.bookCount];
        int index = -1;
        string filename = "Users/" + role + "/borrowed_" + to_string(getUserId()) + ".txt";
        ifstream file(filename);
        if (file.is_open())
        {
            string temp;
            for (int i = 0; i < acc.bookCount; i++)
            {
                getline(file, temp);
                id[i] = stoi(temp);
                getline(file, temp);
                Time[i] = stoi(temp);
                if (id[i] == bookId)
                {
                    index = i;
                }
            }
            file.close();
        }
        else
        {
            cout << "\nSomething is wrong while finding borrowed books. Faculty.returnBook.\n\n";
            return;
        }
        if (index == -1)
        {
            cout << "\nYou didn't borrow this book.\n\n";
            return;
        }
        acc.updateFine();
        ofstream fout(filename);
        if (fout.is_open())
        {
            for (int i = 0; i < acc.bookCount; i++)
            {
                if (index != i)
                {
                    fout << id[i] << "\n"
                         << Time[i] << "\n";
                }
            }
            fout.close();
        }
        else
        {
            cout << "\nIdentified the book in the borrowed. Something is wrong while returning. Faculty.returnBook.\n\n";
            return;
        }
        acc.bookCount -= 1;
        acc.loadBookHistory(bookId);
        acc.loadData(getUserId());
        updateStatustoAvailable(bookId);
        cout << "\nYou have successfully returned the book.\n\n";
    }
    else
    {
        cout << "\nYou don't have any borrowed books at the moment to return.\n\n";
    }
    return;
}

void Faculty ::viewBorrowedBooks()
{
    acc.viewBorrowedBooks();
    return;
}

void Faculty ::viewHistory()
{
    string filename = "Users/" + role + "/history_" + to_string(getUserId()) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        string temp;
        int i = 0;
        while (getline(file, temp))
        {
            cout << temp << "\n";
            i++;
        }
        file.close();
        cout << "\n";
        if (i == 0)
        {
            cout << "\nYou didn't return any book to view history.\n\n";
        }
    }
    else
    {
        cout << "\nSomething went wrong while checking history. Faculty.viewHistory.\n\n";
    }
    return;
}

void Faculty ::newUser(string name, string pass)
{
    CreateDirectory("Users/Faculty", NULL);
    Id = getPrevId();

    this->name = name;
    setPassword(pass);
    setUserId(Id);
    role = "Faculty";

    acc.role = "Faculty";
    acc.setUserId(Id);
    acc.setFine(0);
    acc.bookCount = 0;
    acc.OverdueDays = 0;
    acc.bookLimit = 5;
    acc.timeLimit = 30;
    acc.loadData(Id);

    string filename = "Users/Faculty/user_" + to_string(Id) + ".txt";
    ofstream file;
    file.open(filename);
    if (file.is_open())
    {
        file << role << "\n"
             << this->name << "\n"
             << getPassword();
        file.close();
        cout << "\nFaculty account created!\n";
        cout << "Your UserId : " << getUserId() << "\n";
        cout << "Remember this UserId, you will have to login using this.\n\n";
    }
    else
    {
        cout << "\nSomething went wrong while creating a new user. Faculty.newUser.\n\n";
        return;
    }
    filename = "Users/Faculty/borrowed_" + to_string(Id) + ".txt";
    file.open(filename);
    if (file.is_open())
    {
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while creating a new user in borrowed. Faculty.newUser.\n\n";
        return;
    }
    filename = "Users/Faculty/history_" + to_string(Id) + ".txt";
    file.open(filename);
    if (file.is_open())
    {
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while creating a new user in history. Faculty.newUser.\n\n";
        return;
    }

    Id = getPrevId() + 1;
    updateId();

    return;
}

void Faculty ::deleteAccount(int id)
{
    if (accountExists(id))
    {
        string filename1 = "Users/Faculty/user_" + to_string(id) + ".txt";
        string filename2 = "Users/Faculty/account_" + to_string(id) + ".txt";
        string filename3 = "Users/Faculty/borrowed_" + to_string(id) + ".txt";
        string filename4 = "Users/Faculty/history_" + to_string(id) + ".txt";
        if (remove((filename1).c_str()))
        {
            cout << "\nSomething went wrong while deleting filename1. Faculty.deleteAccount.\n\n";
            return;
        }
        if (remove((filename2).c_str()))
        {
            cout << "\nSomething went wrong while deleting filename2. Faculty.deleteAccount.\n\n";
            return;
        }
        if (remove((filename3).c_str()))
        {
            cout << "\nSomething went wrong while deleting filename3. Faculty.deleteAccount.\n\n";
            return;
        }
        if (remove((filename4).c_str()))
        {
            cout << "\nSomething went wrong while deleting filename4. Faculty.deleteAccount.\n\n";
            return;
        }
        cout << "\nYou have successfully removed the Faculty with UserId : " << to_string(id) << "\n\n";
    }
    else
    {
        cout << "\nUser doesn't exist to remove.\n\n";
    }
}
