#ifndef ZILE_IN_LUNA_H
#define ZILE_IN_LUNA_H

#include <iostream>

using namespace std;

bool esteAnBisect(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        return true; // an bisect
    }
    else
    {
        return false; // an obisnuit
    }
}

bool getZileLuna(int an, int luna, int zi)
{
    if (luna < 1 || luna > 12)
    {
        return false;
    }

    if (zi < 1)
    {
        return false;
    }

    int luni[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (luna == 2)
    {
        bool anBisect = esteAnBisect(an);

        if (anBisect)
        {
            if (zi > 29)
            {
                cout << "Luna februarie are doar 29 de zile in an bisect!" << endl;
                return false;
            }
        }
        else
        {
            if (zi > 28)
            {
                cout << "Luna februarie are 29 de zile doar in anii bisecti, iar anul " << an << " nu este bisect." << endl;
                return false;
            }
        }
    }
    else
    {
        if (zi > luni[luna - 1])
        {
            cout << "Luna " << luna << " are doar " << luni[luna - 1] << " de zile!" << endl;
            return false;
        }
    }
    return true;
}

#endif
