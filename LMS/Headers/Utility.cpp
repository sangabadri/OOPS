#include "Utility.h"
#include <iostream>
#include <string>

string chooseRole()
{
    cout << "1. Student\n";
    cout << "2. Faculty\n";
    cout << "3. Librarian\n";
    cout << "Choose your role : ";
    string role;
    cin >> role;
    cout << "\n";
    return role;
}
