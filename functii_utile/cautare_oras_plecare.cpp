#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

bool cautare_oras_plecare(string &oras, string &oras2, int optiune_oras, int *numar_linie)
{
    ifstream fisier_csv("curse.csv");

    *numar_linie = 0;

    if (!fisier_csv.is_open())
    {
        cout << "Nu s-a putut deschide fisierul!" << endl;
        return false;
    }
    else
    {
        string line;

        while (getline(fisier_csv, line))
        {
            (*numar_linie)++;

            stringstream ss(line);
            string numar_cursa, nume_oras_plecare, nume_oras_destinatie;

            if (optiune_oras == 1)
            {
                if (getline(ss, numar_cursa, ',') && getline(ss, nume_oras_plecare, ','))
                {
                    if (nume_oras_plecare == oras)
                    {
                        cout << "Orasul din care doresti sa pleci exista." << endl;
                        fisier_csv.close();
                        return true; // orasul exista
                    }
                }
            }
            else
            {

                if (getline(ss, numar_cursa, ',') && getline(ss, nume_oras_plecare, ',') && getline(ss, nume_oras_destinatie, ','))
                {
                    if (nume_oras_plecare == oras && nume_oras_destinatie == oras2)
                    {
                        cout << "Orasul in care doresti sa ajungi exista." << endl;
                        fisier_csv.close();
                        return true; // orasul exista
                    }
                }
            }
        }
        if (optiune_oras == 1)
            cout << "Orasul din care doresti sa pleci nu exista." << endl;
        else
            cout << "Orasul in care doresti sa ajungi nu exista." << endl;

        fisier_csv.close();
        return false;
    }
}