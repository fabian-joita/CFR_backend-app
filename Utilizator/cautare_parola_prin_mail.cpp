#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "criptare.h"

using namespace std;

bool password_by_email(string name_csv, string &name, string &password, string email)
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
                name = nume;

                int incercari = 3;
                while (incercari > 0)
                {
                    cout << "Introdu parola: ";
                    cin >> password;
                    string decryptedText = vigenereDecrypt(parola, "key");

                    if (decryptedText == password)
                    {
                        cout << "------------------------------------------------------------------------" << endl;
                        cout << "Te-ai conectat!" << endl;
                        cout << "------------------------------------------------------------------------" << endl;

                        fisier_csv.close();
                        return true;
                    }
                    else
                    {
                        cout << "Parola este incorecta! " << --incercari << " incercari ramase." << endl;
                    }
                }

                cout << "Prea multe incercari nereusite. Autentificare nereusita!" << endl;
                fisier_csv.close();
                return false;
            }
        }
    }

    cout << "E-mailul nu exista in baza de date!" << endl;

    fisier_csv.close();
    return false;
}
