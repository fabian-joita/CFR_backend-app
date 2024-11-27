#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include "cautare_parola_prin_mail.cpp"
#include "find_user_name_email.cpp"
#include "find_user_email.cpp"
#include "putere_parola.cpp"
#include "criptare.cpp"

using namespace std;

bool email_valid(const string &email)
{
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

    return regex_match(email, pattern);
}

void introducere_email()
{
}

void autentificare_utilizator(string &name, string &password, string &email1)
{
    cout << "Vreti sa va conectati cu numele de utilizator sau cu email?" << endl;
    cout << "1. Nume de utilizator" << endl;
    cout << "2. Email" << endl;
    int optiune;
    cin >> optiune;
    if (optiune == 1)
    {
        bool trei_parole;
        bool exista;
        string parola;
        string user_name;
        do
        {
            trei_parole = false;
            cout << "Introduceti numele utilizatorului: ";

            cin >> user_name;
            name = user_name;

            // intai o sa verificam daca utilizatorul are cu adevarat un cont
            string parola;

            exista = find_user_name_email_csv("utilizatori.csv", user_name, parola, email1, &trei_parole);
        } while (trei_parole == true);

        if (!(exista))
        {
            cout << "Nu exista utilizatorul cu numele: " << user_name << endl;
            cout << "Va rugam sa va creati un cont nou!" << endl
                 << endl;

            string putere_parola;

            do
            {
                cout << "Draga " << name << " te rugam sa introduci parola pentru a va crea un cont nou: ";

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

            string email;

            if (fisier_utilizatori.is_open())
            {
                bool valid = false;
                do
                {
                    cout << "Introduceti emailul utilizatorului: ";
                    cin >> email;
                    email1 = email;

                    valid = email_valid(email);
                } while (valid == false);

                cout << "Emailul este valid!" << endl;

                fisier_utilizatori << user_name << "," << password << "," << email << '\n';
                fisier_utilizatori.close();

                cout << "Contul a fost creat cu succes!" << endl;
            }
            else
            {
                cout << "Eroare: Nu s-a putut deschide fișierul pentru scriere!" << endl;
            }
        }
        else
        {
            password = parola;
            cout << password << endl;
            cout << email1 << endl;
        }
    }
    else
    { // vreau sa ma conectez prin email
        bool valid = false;
        bool exista_email = false;

        string email;
        int rasp;

        do
        {
            cout << "Introduceti emailul utilizatorului: ";
            cin >> email;

            valid = email_valid(email);

            rasp = 0;

            if (valid)
            {
                exista_email = find_user_email("utilizatori.csv", email);

                if (!exista_email)
                {
                    cout << "Nu exista acest email." << endl;
                    cout << "Vrei sa creati un cont nou? (1) Da, (2) Nu" << endl;
                    cin >> rasp;
                }
            }

            if (rasp == 1 && valid)
                break;

        } while (!valid || !exista_email);

        cout << "Emailul este valid!" << endl;

        string nume, parola;
        bool conectat = false;

        if (exista_email)
        {
            do
            {
                conectat = password_by_email("utilizatori.csv", nume, parola, email);

                if (conectat)
                {
                    name = nume;
                    password = parola;
                }
                else
                {
                    cout << "Conectarea cu email a esuat !! " << endl;
                    do
                    {
                        cout << "Introduceti emailul utilizatorului: ";
                        cin >> email;

                        valid = email_valid(email);

                        rasp = 0;

                        if (valid)
                        {
                            exista_email = find_user_email("utilizatori.csv", email);

                            if (!exista_email)
                            {
                                cout << "Nu exista acest email." << endl;
                                cout << "Vrei sa creati un cont nou? (1) Da, (2) Nu" << endl;
                                cin >> rasp;
                            }
                        }

                        if (rasp == 1 && valid)
                            break;

                    } while (!valid || !exista_email);
                }
            } while (!conectat);
        }
        else
        {
            if (rasp == 1)
            {
                string putere_parola;
                do
                {
                    cout << "Draga " << name << " te rugam sa introduci parola pentru a va crea un cont nou: ";

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

                if (fisier_utilizatori.is_open())
                {
                    cout << "Te rugam sa introduci numele pentru a crea contul nou: ";
                    cin >> nume;

                    fisier_utilizatori << nume << "," << password << "," << email << "\n";
                    fisier_utilizatori.close();
                    cout << "Contul a fost creat cu succes!" << endl;
                }
                else
                {
                    cout << "Eroare la deschiderea fisierului!" << endl;
                }

                name = nume;
                email1 = email;

                cout << "Te-ai inregistrat cu succes!" << endl;
            }
            else
            {
                cout << "Ai ales sa nu creezi un cont. Programul se va opri." << endl;
            }
        }
    }
}