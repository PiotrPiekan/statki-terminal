#include "helpers.h"

bool isNumber(const string& str)
{
    return !str.empty() && find_if(str.begin(),
        str.end(), [](unsigned char c) { return !isdigit(c); }) == str.end();
}

void removeSpaces(string& str)
{
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}