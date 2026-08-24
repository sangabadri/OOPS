#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book{
    private:
        int bookId;
    public:
        int getId();
        void setId(int id);
        string bookStatus;
        string title;
        string author;
        string publisher;
        string year;
        void fetchData(int id);
        void loadData(int id);
        bool bookExists(int id);
        int getTotal();
        void updateTotal(int tot);
};

#endif