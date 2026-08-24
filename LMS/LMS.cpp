#include "Headers/Librarian.h"
#include "Headers/Student.h"
#include "Headers/Faculty.h"
#include "Headers/Utility.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void Login();
void LibrarianRoles(Librarian l1);
void StudentRoles(Student s1);
void FacultyRoles(Faculty f1);

int main()
{
    cout << "\nIf you are new or wish to create account, consult Librarian.\n\n";
    Login();
    cout << "Thank you for using our Library Management System.\n\n";
    return 0;
}

void Login()
{
    string role = chooseRole();
    int i;
    if (role == "1")
    {
        string id;
        string pass;
        Student s1;
        i = 0;
        while (i < 3)
        {
            try{
                cout << "Enter your UserId : ";
                cin >> id;
                cout << "\n";
                stoi(id);
            }
            catch(...){
                i++;
                if (i == 3)
                {
                    cout << "\nInvalid input.";
                }
                else
                {
                    cout << "\nInvalid input. Try again.\n\n";
                }
                continue;
            }
            if (s1.accountExists(stoi(id)))
            {
                s1.fetchData(stoi(id));
                break;
            }
            else
            {
                i++;
                if (i == 3)
                {
                    cout << "\nUserId doesn't exist.";
                }
                else
                {
                    cout << "\nUserId doesn't exist. Try again.\n\n";
                }
            }
        }
        if (i == 3)
        {
            cout << "\nToo many failed attempts.";
            cout << "\nSession ended.\n\n";
            return;
        }
        i = 0;
        while (i < 3)
        {
            cout << "Enter your password : ";
            cin >> pass;
            cout << "\n";
            if (s1.correctPassword(pass))
            {
                break;
            }
            else
            {
                i++;
                if (i == 3)
                {
                    cout << "\nIncorrect Password.";
                }
                else
                {
                    cout << "\nIncorrect Password. Try again.\n\n";
                }
            }
        }
        if (i == 3)
        {
            cout << "\nToo many failed attempts.";
            cout << "\nSession ended.\n\n";
            return;
        }
        StudentRoles(s1);
    }
    else if (role == "2")
    {
        string id;
        string pass;
        Faculty f1;
        i = 0;
        while (i < 3)
        {
            try{
                cout << "Enter your UserId : ";
                cin >> id;
                cout << "\n";
                stoi(id);
            }
            catch(...){
                cout << "\nInvalid input. Try again.\n\n";
                i++;
                continue;
            }
            if (f1.accountExists(stoi(id)))
            {
                f1.fetchData(stoi(id));
                break;
            }
            else
            {
                i++;
                if (i == 3)
                {
                    cout << "\nUserId doesn't exist.";
                }
                else
                {
                    cout << "\nUserId doesn't exist. Try again.\n\n";
                }
            }
        }
        if (i == 3)
        {
            cout << "\nToo many failed attempts.";
            cout << "\nSession ended.\n\n";
            return;
        }
        i = 0;
        while (i < 3)
        {
            cout << "Enter your password : ";
            cin >> pass;
            cout << "\n";
            if (f1.correctPassword(pass))
            {
                break;
            }
            else
            {
                i++;
                if (i == 3)
                {
                    cout << "\nIncorrect Password.";
                }
                else
                {
                    cout << "\nIncorrect Password. Try again.\n\n";
                }
            }
        }
        if (i == 3)
        {
            cout << "\nToo many failed attempts.";
            cout << "\nSession ended.\n\n";
            return;
        }
        FacultyRoles(f1);
    }
    else if (role == "3")
    {
        string id;
        string pass;
        Librarian l1;
        i = 0;
        while (i < 3)
        {
            try{
                cout << "Enter your UserId : ";
                cin >> id;
                cout << "\n";
                stoi(id);
            }
            catch(...){
                cout << "\nInvalid input. Try again.\n\n";
                i++;
                continue;
            }
            if (l1.accountExists(stoi(id)))
            {
                l1.fetchData(stoi(id));
                break;
            }
            else
            {
                i++;
                if (i == 3)
                {
                    cout << "\nUserId doesn't exist.";
                }
                else
                {
                    cout << "\nUserId doesn't exist. Try again.\n\n";
                }
            }
        }
        if (i == 3)
        {
            cout << "\nToo many failed attempts.";
            cout << "\nSession ended.\n\n";
            return;
        }
        i = 0;
        while (i < 3)
        {
            cout << "Enter your password : ";
            cin >> pass;
            cout << "\n";
            if (l1.correctPassword(pass))
            {
                break;
            }
            else
            {
                i++;
                if (i == 3)
                {
                    cout << "\nIncorrect Password.";
                }
                else
                {
                    cout << "\nIncorrect Password. Try again.\n\n";
                }
            }
        }
        if (i == 3)
        {
            cout << "\nToo many failed attempts.";
            cout << "\nSession ended.\n\n";
            return;
        }
        LibrarianRoles(l1);
    }
    else
    {
        cout << "\nRole not available. Session ended.\n\n";
    }
    return;
}

void StudentRoles(Student s1)
{
    cout << "\nYou have successfully into you Student account with UserId : " << s1.getUserId() << "\n\n";
    int id = s1.getUserId();
    while (1)
    {
        s1.fetchData(id);
        cout << "Here are your permissions as Student : \n";
        cout << "1. View all Books along with its BookId\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "4. BookId's of the Borrowed Books\n";
        cout << "5. View Borrowed History\n";
        cout << "6. View Fine\n";
        cout << "7. Pay Fine\n";
        cout << "8. View no. of Overdue Days\n";
        cout << "9. Logout\n";
        cout << "Choose an option : ";
        string action;
        cin >> action;
        cout << "\n";
        if (action == "1")
        {
            Library lib;
            lib.viewBooks();
        }
        else if (action == "2")
        {
            int bookId;
            cout << "Enter BookId : ";
            cin >> bookId;
            cout << "\n";
            s1.borrowBook(bookId);
        }
        else if (action == "3")
        {
            int bookId;
            cout << "Enter BookId : ";
            cin >> bookId;
            cout << "\n";
            s1.returnBook(bookId);
        }
        else if (action == "4")
        {
            s1.viewBorrowedBooks();
        }
        else if (action == "5")
        {
            s1.viewHistory();
        }
        else if (action == "6")
        {
            if (s1.Fine())
            {
                cout << "\nYour fine : " << s1.Fine() << "/-\n\n";
            }
            else
            {
                cout << "\nYou have no fines at the moment.\n\n";
            }
        }
        else if (action == "7")
        {
            s1.payFine();
        }
        else if (action == "8")
        {
            cout << "\nNo. of Overdue Days : " << s1.getOverdues() << "\n\n";
        }
        else if (action == "9")
        {
            cout << "\nYou have succesfully logged out of the Student account.\n\n";
            Login();
            break;
        }
        else
        {
            cout << "\nSession ended.\n\n";
            break;
        }
    }
    return;
}

void FacultyRoles(Faculty f1)
{
    cout << "\nYou have successfully into you Faculty account with UserId : " << f1.getUserId() << "\n\n";
    int id = f1.getUserId();
    while (1)
    {
        f1.fetchData(id);
        cout << "Here are your permissions as Faculty : \n";
        cout << "1. View all Books along with its BookId\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "4. BookId's of the Borrowed Books\n";
        cout << "5. View Borrowed History\n";
        cout << "6. View no. of Overdue Days\n";
        cout << "7. Logout\n";
        cout << "Choose an option : ";
        string action;
        cin >> action;
        cout << "\n";
        if (action == "1")
        {
            Library lib;
            lib.viewBooks();
        }
        else if (action == "2")
        {
            int bookId;
            cout << "Enter BookId : ";
            cin >> bookId;
            cout << "\n";
            f1.borrowBook(bookId);
        }
        else if (action == "3")
        {
            int bookId;
            cout << "Enter BookId : ";
            cin >> bookId;
            cout << "\n";
            f1.returnBook(bookId);
        }
        else if (action == "4")
        {
            f1.viewBorrowedBooks();
        }
        else if (action == "5")
        {
            f1.viewHistory();
        }
        else if (action == "6")
        {
            cout << "\nNo. of Overdue Days : " << f1.getOverdues() << "\n\n";
        }
        else if (action == "7")
        {
            cout << "\nYou have succesfully logged out of the Faculty account.\n\n";
            Login();
            break;
        }
        else
        {
            cout << "\nSession ended.\n\n";
            break;
        }
    }
    return;
}

void LibrarianRoles(Librarian l1)
{
    cout << "\nYou have successfully into you Librarian account with UserId : " << l1.getUserId() << "\n\n";
    while (1)
    {
        cout << "Here are your permissions as Librarian : \n";
        cout << "1. View all Books along with its BookId\n";
        cout << "2. Add Book\n";
        cout << "3. Remove Book\n";
        cout << "4. Add User\n";
        cout << "5. Remove User\n";
        cout << "6. Logout\n";
        cout << "Choose an option : ";
        string action;
        cin >> action;
        cout << "\n";
        if (action == "1")
        {
            l1.lib.viewBooks();
        }
        else if (action == "2")
        {
            l1.addBook();
        }
        else if (action == "3")
        {
            l1.removeBook();
        }
        else if (action == "4")
        {
            cout << "\nCreating a new account.\n\n";
            l1.addUser();
        }
        else if (action == "5")
        {
            cout << "\nRemoving an account.\n\n";
            l1.removeUser();
        }
        else if (action == "6")
        {
            cout << "\nYou have succesfully logged out of the Librarian account.\n\n";
            Login();
            break;
        }
        else
        {
            cout << "\nSession ended.\n\n";
            break;
        }
    }
    return;
}
