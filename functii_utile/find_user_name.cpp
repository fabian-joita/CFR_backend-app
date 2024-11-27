#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

bool find_user_name_csv(string name_csv, string &user_name, string &password)
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
        string nume, parola;

        if (getline(ss, nume, ',') && getline(ss, parola, ','))
        {
            if (nume == user_name)
            {
                int incercari = 0;
                do
                {
                    cout << "Enter your password: ";
                    cin >> password;

                    if (parola == password)
                    {
                        cout << "------------------------------------------------------------------------" << endl;
                        cout << "You are connected!" << endl;
                        cout << "------------------------------------------------------------------------" << endl;
                        return true;
                    }
                    else
                    {
                        cout << "Password is incorrect!" << endl
                             << endl;
                        incercari++;
                    }

                } while (incercari < 3);
                cout << "Ai introdus de prea multe ori o parola gresita." << endl;
            }
        }
    }
    fisier_csv.close();

    return false;
}