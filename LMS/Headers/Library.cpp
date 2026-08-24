#include "Library.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

int Library ::getPrevId()
{
    string filename = "Books/id_counter.txt";
    ifstream file(filename);
    int prevId = 100;
    if (file.is_open())
    {
        file >> prevId;
        file.close();
    }
    return prevId;
}

void Library ::updateId()
{
    string filename = "Books/id_counter.txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << Id;
        file.close();
    }
    return;
}

void Library::updateStatustoAvailable(int bookId)
{
    book.fetchData(bookId);
    book.bookStatus = "Available";
    book.loadData(bookId);
    return;
}

void Library ::updateStatustoBorrowed(int bookId)
{
    book.fetchData(bookId);
    book.bookStatus = "Borrowed";
    book.loadData(bookId);
    return;
}

void Library ::addBook()
{
    CreateDirectory("Books", NULL);
    Id = getPrevId();
    string filename = "Books/book_" + to_string(Id) + ".txt";
    book.setId(Id);
    book.bookStatus = "Available";

    cout << "Enter Title of the book : ";
    cin >> book.title;
    cout << "\n";

    cout << "Enter the name of the Author : ";
    cin >> book.author;
    cout << "\n";

    cout << "Enter Publisher : ";
    cin >> book.publisher;
    cout << "\n";

    while(1){
        cout << "Enter published Year : ";
        cin >> book.year;
        cout << "\n";
        try{
            stoi(book.year);
            break;
        }
        catch(...){
            cout << "\nInvalid input. Try again.\n\n";
        }
    }
    
    cout << "Successfully added a new book to the Library. BookId : " << Id << "\n\n";
    book.loadData(Id);
    Id = getPrevId() + 1;
    updateId();
    int tot = book.getTotal();
    book.updateTotal(tot + 1);
    return;
}

void Library ::removeBook()
{
    cout << "Enter bookId : ";
    int id;
    cin >> id;
    cout << "\n";
    string filename = "Books/book_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        book.fetchData(id);
        file.close();
        if (!(book.bookStatus == "Available"))
        {
            cout << "\nThe book is borrowed at the moment. Try again when it is Available in the Library.\n\n";
        }
        else
        {
            if (!remove((filename).c_str()))
            {
                int tot = book.getTotal();
                book.updateTotal(tot - 1);
                cout << "\nSuccessfully removed the book from library.\n\n";
            }
            else
            {
                cout << "\nSomething went wrong while removing book. Library.removeBook.\n\n";
            }
        }
    }
    else
    {
        cout << "\nThe book is not registered in the library.\n\n";
    }
    return;
}

void Library ::viewBooks()
{
    cout << "\n";
    int i = 0;
    int id = 100;
    if (book.getTotal())
    {
        while (i < book.getTotal())
        {
            string filename = "Books/book_" + to_string(id) + ".txt";
            ifstream file(filename);
            if (file.is_open())
            {
                file.close();
                book.fetchData(id);
                cout << "BookId : " + to_string(book.getId()) + " , Title : " + book.title + " , Status : " + book.bookStatus << "\n";
                i++;
            }
            id++;
        }
        cout << "\n";
    }
    else
    {
        cout << "There are no books registered in the Library.\n\n";
    }

    return;
}
