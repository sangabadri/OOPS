#include "Book.h"
#include <iostream>
#include <fstream>
#include <string>

int Book ::getId()
{
    return bookId;
}

void Book ::setId(int id)
{
    bookId = id;
    return;
}

void Book ::fetchData(int id)
{
    string filename = "Books/book_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        setId(id);
        getline(file, bookStatus);
        getline(file, title);
        getline(file, author);
        getline(file, publisher);
        getline(file, year);
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while fetching book data. Book.fetchData.\n\n";
    }
    return;
}

void Book ::loadData(int id)
{
    string filename = "Books/book_" + to_string(id) + ".txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << bookStatus << "\n"
             << title << "\n"
             << author << "\n"
             << publisher << "\n"
             << year;
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while storing book data. Book.loadData.\n\n";
    }
    return;
}

bool Book ::bookExists(int id)
{
    string filename = "Books/book_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        file.close();
        return true;
    }
    return false;
}

int Book ::getTotal()
{
    string filename = "Books/book_counter.txt";
    int tot = 0;
    ifstream file(filename);
    if (file.is_open())
    {
        file >> tot;
        file.close();
    }
    return tot;
}

void Book ::updateTotal(int tot)
{
    string filename = "Books/book_counter.txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << tot;
    }
    else
    {
        cout << "\nSomething went wrong while updating total books. Book.updateTotal.\n\n";
    }
    return;
}
