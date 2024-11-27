// header_date_time.h
#ifndef HEADER_DATE_TIME_H
#define HEADER_DATE_TIME_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

string getDate()
{
    // se obtine timpul curent
    time_t now = time(0);

    // convertirea timpului in structul tm
    tm *ltm = localtime(&now);

    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"                        // anul
       << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-" // luna
       << setw(2) << setfill('0') << ltm->tm_mday;          // ziua

    return ss.str(); // returneaza data ca string
}

string getTime()
{
    time_t now = time(0);

    tm *ltm = localtime(&now);

    stringstream ss;
    ss << setw(2) << setfill('0') << ltm->tm_hour << ":" // ora
       << setw(2) << setfill('0') << ltm->tm_min << ":"  // minutele
       << setw(2) << setfill('0') << ltm->tm_sec;        // secundele

    return ss.str(); // Returneaza ora ca string
}

#endif
