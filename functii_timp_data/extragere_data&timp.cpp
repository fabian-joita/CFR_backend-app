#include <iostream>
#include <string>

using namespace std;

void ExtragereData_sau_timp(string data, int *an, int *luna, int *zi)
{
    stringstream ss(data);
    char separator;
    ss >> *an >> separator >> *luna >> separator >> *zi;
}