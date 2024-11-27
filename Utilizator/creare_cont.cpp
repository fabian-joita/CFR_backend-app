#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include "putere_parola.h"
#include "criptare.h"

using namespace std;

bool is_email_valid(const string &email)
{
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

    return regex_match(email, pattern);
}

void creare_cont(string &user_name, string &password, string &email1)
{
    int identic;
    do
    {
        ifstream fisier_utilizatori("utilizatori.csv");

        // verificam daca exista deja un utilizator cu acelasi nume
        if (fisier_utilizatori.is_open())
        {
            string line;

            cout << "Creati noul cont: " << endl;
            cout << "Nume utilizator: ";

            string name;
            cin >> name;

            user_name = name;

            identic = 0;

            while (getline(fisier_utilizatori, line))
            {
                stringstream ss(line);
                string nume, parola;

                if (getline(ss, nume, ',') && getline(ss, parola, ','))
                {
                    if (nume == name)
                    {
                        cout << "Utilizatorul " << name << " deja exista!" << endl;
                        identic = 1;
                    }

                    if (identic == 1)
                        break;
                }
            }

            user_name = name;

            fisier_utilizatori.close();
        }
        else
        {
            cout << "Eroare: Nu s-a putut deschide fișierul pentru verificare username!" << endl;
        }
    } while (identic == 1);

    bool valid = false;
    string email;

    do
    {
        cout << "Introduceti emailul utilizatorului: ";
        cin >> email;
        email1 = email;
        valid = is_email_valid(email);
    } while (valid == false);
    cout << "Emailul este valid!" << endl;

    string parola;

    string putere_parola;

    do
    {
        cout << "Draga " << user_name << " te rugam sa introduci parola pentru a va crea un cont nou: ";

        cin >> parola;
        string key = "key";
        string ciphertext = vigenereEncrypt(parola, key);
        cout << "Ciphertext: " << ciphertext << endl;
        string decryptedText = vigenereDecrypt(ciphertext, key);
        cout << "Decrypted Text: " << decryptedText << endl;

        password = ciphertext;

        try
        {
            putere_parola = verificaParola(parola);
            cout << "Puterea parolei este: " << putere_parola << endl;
        }
        catch (const char *mesaj)
        {
            cout << "Eroare: " << mesaj << endl;
            cout << "Va rugam sa incercati din nou!" << endl;
            continue;
        }
    } while (putere_parola != "Puternica" && putere_parola != "Medie");

    ofstream fisier_utilizatori("utilizatori.csv", ios::app);

    if (!fisier_utilizatori.is_open())
    {
        cout << "Eroare de deschidere" << endl;
    }
    cout << user_name << " " << password << " " << email1 << endl;
    fisier_utilizatori << user_name << "," << password << "," << email << endl;

    fisier_utilizatori.close();
}
