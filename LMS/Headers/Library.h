#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"

class Library
{
public:
    Book book;
    int Id;
    int getPrevId();
    void updateId();
    void updateStatustoAvailable(int bookId);
    void updateStatustoBorrowed(int bookId);
    void addBook();
    void removeBook();
    void viewBooks();
};

#endif
