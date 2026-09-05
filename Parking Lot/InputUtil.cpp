#include "InputUtil.h"

int readInt(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        return value;
    }
}

int readInt(const string &prompt, int lo, int hi)
{
    while (true)
    {
        int value = readInt(prompt);
        if (value >= lo && value <= hi)
        {
            return value;
        }
        cout << "Please enter a value between " << lo << " and " << hi << ".\n";
    }
}

string readSafeToken(const string &prompt)
{
    string token;
    while (true)
    {
        cout << prompt;
        cin >> token;
        if (token.empty())
        {
            cout << "Input cannot be empty.\n";
            continue;
        }
        if (token.find('/') != string::npos ||
            token.find('\\') != string::npos ||
            token.find("..") != string::npos)
        {
            cout << "Input must not contain '/', '\\', or '..'.\n";
            continue;
        }
        return token;
    }
}

bool retryLoop(int maxAttempts, function<bool(int attempt, int maxAttempts)> body)
{
    for (int i = 1; i <= maxAttempts; i++)
    {
        if (body(i, maxAttempts))
        {
            return true;
        }
    }
    return false;
}
