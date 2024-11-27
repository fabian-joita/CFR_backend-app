#include <iostream>
#include <string>

using namespace std;

void afisare_continut_fisier(string name_csv, int *numar_linii, bool afisare)
{

    ifstream fisier_csv(name_csv);

    if (!fisier_csv.is_open())
    {
        cout << "Nu s-a putut deschide fisierul!" << endl;
    }

    string line;
    if (afisare == true)
    {
        cout << endl
             << "Se afiseaza cursele disponibile: " << endl;
    }

    while (getline(fisier_csv, line))
    {
        if (afisare == true)
        {
            cout << line << endl;
        }

        (*numar_linii)++;
    }

    cout << endl;
    fisier_csv.close();
}