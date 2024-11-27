#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

bool find_user_email(string name_csv, string email)
{
    ifstream fisier_csv(name_csv);

    if (!fisier_csv.is_open())
    {
        cout << "Nu s-a putut deschide fisierul!" << endl;
        return false;
    }

    string line;

    while (getline(fisier_csv, line))
    {
        stringstream ss(line);
        string nume, parola, mail;

        if (getline(ss, nume, ',') && getline(ss, parola, ',') && getline(ss, mail, ','))
        {
            if (mail == email)
            {
                return true;
            }
        }
    }
    fisier_csv.close();

    return false;
}