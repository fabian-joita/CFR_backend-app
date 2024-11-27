#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "criptare.h"

using namespace std;

bool find_user_name_email_csv(string name_csv, string user_name, string &password, string &email, bool *trei_parole)
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
            if (nume == user_name)
            {
                email = mail;
                int incercari = 0;
                do
                {
                    cout << "Introdu parola : ";
                    cin >> password;
                    string decryptedText = vigenereDecrypt(parola, "key");
                    cout << endl;

                    if (decryptedText == password)
                    {
                        cout << "------------------------------------------------------------------------" << endl;
                        cout << "Te-ai conectat!" << endl;
                        cout << "------------------------------------------------------------------------" << endl;
                        return true;
                    }
                    else
                    {
                        cout << "Parola este incorecta!" << endl;
                        incercari++;
                    }

                } while (incercari < 3);

                if (incercari == 3)
                {
                    cout << "Ai introdus prea multe parole incorecte." << endl;
                    (*trei_parole) = true;
                }
            }
        }
    }
    fisier_csv.close();

    return false;
}