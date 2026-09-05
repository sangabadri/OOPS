#pragma once

#include <string>
#include <functional>
#include <optional>
#include <iostream>
#include <limits>

using namespace std;

int readInt(const string &prompt);
int readInt(const string &prompt, int lo, int hi);
string readSafeToken(const string &prompt);
bool retryLoop(int maxAttempts, function<bool(int attempt, int maxAttempts)> body);
