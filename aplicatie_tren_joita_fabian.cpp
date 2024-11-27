#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include "functii_timp_data/header_date_time.cpp"
#include "functii_timp_data/zile_in_luna.cpp"
#include "functii_utile/Validare_nume_oras.cpp"
#include "functii_utile/afis_csv.cpp"
#include "functii_utile/find_user_name.cpp"
#include "functii_timp_data/extragere_data&timp.cpp"
#include "functii_utile/cautare_oras_plecare.cpp"
#include "Utilizator/autentificare.cpp"
#include "Utilizator/creare_cont.cpp"

using namespace std;

class Operator
{
private:
    string user_name;
    string password;

public:
    Operator()
    {
        bool conected = false;

        // daca user name a fost gasit in fisierul csv cu operatori
        // atunci continui conectarea cu password altfel nume incorect
        while (conected == false)
        {

            cout << "Introduceti numele operatorului: ";
            string user_name;
            string password;
            cin >> user_name;
            cout << endl;

            if (find_user_name_csv("operatori_site.csv", user_name, password) == true)
            {
                this->user_name = user_name;
                this->password = password;
                conected = true;
            }
            else
            {
                cout << "Numele de operator nu a fost gasit alaturi de parolele atribuite!" << endl;
            }
        }
    }

    void adaugare_curse(string locatie_plecare, string destinatie, string data, string ora)
    {
        // adaugare cursa in fisierul csv de catre operator
        ofstream fisier_csv_curse("curse.csv", ios::app);

        if (!fisier_csv_curse.is_open())
        {
            cout << "Nu s-a putut deschide fisierul!" << endl;
        }

        int numar_linii = 1;

        afisare_continut_fisier("curse.csv", &numar_linii, false);

        cout << "se adauga in fisierul csv" << " " << locatie_plecare << " " << destinatie << " " << data << " " << ora << endl;
        fisier_csv_curse << numar_linii << "," << locatie_plecare << "," << destinatie << "," << data << "," << ora << endl;

        fisier_csv_curse.close();
    }

    void stergere_curse(int nr_linie_de_sters)
    {
        // stergere cursa din fisierul csv de catre operator
        ifstream fisier_csv_curse("curse.csv");
        ofstream fisier_csv_curse_schimbate("curse_schimbate.csv");

        if (!fisier_csv_curse.is_open())
        {
            cout << "Nu s-a putut deschide fisierul!" << endl;
        }

        string line;

        int nr_linii = 0;

        int ajuns_linie_de_sters = false;

        while (getline(fisier_csv_curse, line))
        {
            nr_linii++;
            if (nr_linie_de_sters != nr_linii && ajuns_linie_de_sters == false)
            {
                fisier_csv_curse_schimbate << line << endl;
            }
            else if (nr_linie_de_sters != nr_linii && ajuns_linie_de_sters == true)
            {
                stringstream ss(line);
                string nrLinie, oras_plecare, destinatie, data, ora;

                getline(ss, nrLinie, ',');
                getline(ss, oras_plecare, ',');
                getline(ss, destinatie, ',');
                getline(ss, data, ',');
                getline(ss, ora, ',');

                fisier_csv_curse_schimbate << nr_linii - 1 << "," << oras_plecare << "," << destinatie << "," << data << "," << ora << endl;
            }
            else
            {
                ajuns_linie_de_sters = true;
            }
        }

        fisier_csv_curse.close();
        remove("curse.csv");
        rename("curse_schimbate.csv", "curse.csv");
        fisier_csv_curse_schimbate.close();
    }
};

class Utilizator
{
private:
    string user_name;
    string password;
    string email;

public:
    Utilizator()
    {
        cout << "Ai deja un cont ?" << endl;
        cout << "1. Da - AUTENTIFICARE" << endl;
        cout << "2. Nu - CREARE CONT" << endl;

        int rasp;
        cin >> rasp;

        // daca are deja un cont o sa cautam in fisierul de utilizatori
        if (rasp == 1)
        {
            autentificare_utilizator(this->user_name, this->password, this->email);
        }
        else
        {
            creare_cont(this->user_name, this->password, this->email);
        }
    }

    void CautareCursa()
    {
        int identitate_linie = 0;
        afisare_continut_fisier("curse.csv", &identitate_linie, true);

        bool gasit = false;

        cin.ignore();

        int linie_cursa;

        do
        {
            cout << endl
                 << "Introduceti orasul din care doriti sa plecati: ";

            string oras_plecare;
            string oras_destinatie;

            getline(cin, oras_plecare);
            gasit = cautare_oras_plecare(oras_plecare, oras_destinatie, 1, &linie_cursa);

            if (gasit == true)
            {
                do
                {
                    cout << endl
                         << "Introduceti orasul in care doriti sa ajungeti: ";

                    getline(cin, oras_destinatie);
                    gasit = cautare_oras_plecare(oras_plecare, oras_destinatie, 2, &linie_cursa);
                } while (gasit == false);
            }
        } while (gasit == false);

        ifstream fisier_curse("curse.csv");

        ofstream fisier_rezervari("rezervari.csv", ios::app);

        if (!fisier_curse.is_open() || !fisier_rezervari.is_open())
        {
            cout << "Eroare la deschiderea fișierelor!" << endl;
            return;
        }

        string line;
        int contor = 1;

        while (getline(fisier_curse, line))
        {
            if (contor == linie_cursa)
            {
                fisier_rezervari << this->user_name << "," << line << ",";
                cout << "La ce clasa vrei sa ai rezervarea? 1 / 2 : ";

                int clasa;
                cin >> clasa;

                fisier_rezervari << "clasa: " << clasa << ",";

                string ora_rezervare = getTime();
                fisier_rezervari << "Ora rezervarii: " << ora_rezervare << endl;

                cout << "Rezervarea a fost efectuata cu succes!" << endl;
                break;
            }
            contor++;
        }

        fisier_curse.close();
        fisier_rezervari.close();
    }

    string getNumeUtilizator()
    {
        return this->user_name;
    }
};

int main()
{
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Bine ati venit in aplicatia CFR!" << endl;
    cout << "Vrei sa continui ca operator sau ca utilizator?" << endl;
    cout << "1. Operator" << endl;
    cout << "2. Utilizator" << endl;

    int optiune;
    cin >> optiune;
    cout << "------------------------------------------------------------------------" << endl;

    if (optiune == 1)
    {

        Operator operator1;

        bool ramai_conectat = true;
        do
        {
            cout << "------------------------------------------------------------------------" << endl;
            cout << endl
                 << "Buna ziua, operator!" << endl
                 << endl;
            cout << "Ce operatie doriti sa efectuati?" << endl;
            cout << "1. Adauga cursa" << endl;
            cout << "2. Sterge cursa" << endl;

            int operatie;
            cout << "Optiunea: ";
            cin >> operatie;
            cout << "------------------------------------------------------------------------" << endl;

            // aici o sa fac adaugarea de curse de la tastatura
            if (operatie == 1)
            {
                cout << "------------------------------------------------------------------------" << endl;
                string oras_plecare, oras_sosire, data, timp;
                int an, luna, zi;
                int ora, minut, secunda;

                string data_curenta = getDate();
                int an_curent, luna_curenta, zi_curenta;
                ExtragereData_sau_timp(data_curenta, &an_curent, &luna_curenta, &zi_curenta);
                cout << "an luna zi curente: " << an_curent << " " << luna_curenta << " " << zi_curenta << endl;

                string timp_curent = getTime();
                int ora_curenta, minut_curent, secunda_curenta;
                ExtragereData_sau_timp(timp_curent, &ora_curenta, &minut_curent, &secunda_curenta);

                cin.ignore();
                int orasValid = false;
                do
                {
                    cout << "Orasul de plecare: ";
                    getline(cin, oras_plecare);

                    orasValid = ValidareOras(oras_plecare);
                } while (orasValid == false);

                orasValid = false;
                do
                {
                    cout << "Orasul de sosire: ";
                    getline(cin, oras_sosire);

                    orasValid = ValidareOras(oras_sosire);
                } while (orasValid == false);

                int input_corect = true;

                do
                {
                    cout << "Data format = aaaa-ll-zz : ";
                    cin >> data;

                    if (data.length() == 10 && data[4] == '-' && data[7] == '-')
                    {
                        ExtragereData_sau_timp(data, &an, &luna, &zi);
                        if (zi > 31 || luna > 12 || an < an_curent || (an_curent == an && luna < luna_curenta) || (an == an_curent && luna_curenta == luna && zi < zi_curenta))
                        {
                            cout << "Draga operator, ai introdus o data eronata." << endl;
                            input_corect = false;
                            cout << "Data curenta : " << data_curenta << endl;
                        }
                        else
                        {
                            bool zi_valida = getZileLuna(an, luna, zi);

                            if (zi_valida)
                                input_corect = true;
                        }
                    }
                    else
                    {
                        input_corect = false;
                        cout << "Data introdusa nu este in formatul aaaa-ll-zz" << endl;
                    }

                } while (input_corect == false);

                cout << "anu luna si ziua introduse: " << an << " " << luna << " " << zi << endl;

                do
                {
                    cout << "Ora format = oo:mm:ss : ";
                    cin >> timp;

                    if (timp.length() == 8 && timp[2] == ':' && timp[5] == ':')
                    {
                        ExtragereData_sau_timp(timp, &ora, &minut, &secunda);
                        if (an == an_curent && luna == luna_curenta && zi == zi_curenta)
                        {
                            if (ora < ora_curenta || (ora_curenta == ora && minut < minut_curent) || (ora_curenta == ora && minut_curent == minut && secunda < secunda_curenta))
                            {
                                cout << "Draga operator, ai introdus o ora eronata." << endl;
                                input_corect = false;
                                cout << "Ora curenta : " << timp_curent << endl;
                            }
                            else
                            {
                                input_corect = true;
                            }
                        }
                        else if (ora > 23 || minut > 59 || secunda > 59)
                        {
                            input_corect = false;
                            cout << "Draga operator, ai introdus o ora eronata." << endl;
                            cout << "Ora trebuie sa fie in intervalul 00:00:00 si 23:59:59" << endl;
                        }
                        else
                        {
                            input_corect = true;
                        }
                    }
                    else
                    {
                        input_corect = false;
                        cout << "Ora introdusa nu este in formatul oo:mm:ss sau ai introdus o ora eronata." << endl;
                    }
                } while (input_corect == false);

                cout << "------------------------------------------------------------------------" << endl;

                operator1.adaugare_curse(oras_plecare, oras_sosire, data, timp);
            }
            else if (operatie == 2)
            {
                // stergerea de curse o sa o fac dupa ce mi se afiseaza pe ecran cursele disponibile si o sa sterg in functie de numarul randului
                int linii;
                afisare_continut_fisier("curse.csv", &linii, true);

                int linie_de_sters;
                cout << "Introduceti numarul randului pe care vrei sa il stergi: ";
                cin >> linie_de_sters;
                operator1.stergere_curse(linie_de_sters);
            }
            else
                cout << "Optiune invalida!" << endl;

            cout << "Vrei sa ramai in aplicatie? (1) Da, (2) Nu" << endl;
            cin >> optiune;

            if (optiune == 2)
            {
                ramai_conectat = false;
                cout << "La revedere, operator!" << endl;
            }

        } while (ramai_conectat == true);
    }
    else if (optiune == 2)
    {

        Utilizator utilizator1;

        bool ramai_conectat = true;
        do
        {
            string nume_utilizator = utilizator1.getNumeUtilizator();
            cout << "------------------------------------------------------------------------" << endl;
            cout << "Buna ziua, Utilizator " << nume_utilizator << "!" << endl;
            cout << "Ce operatie doriti sa efectuati?" << endl;

            int actiune_utilizator;
            cout << "Rezervare cursa: (1)" << endl;
            cin >> actiune_utilizator;

            if (actiune_utilizator == 1)
            {
                utilizator1.CautareCursa();
            }

            cout << "Vrei sa ramai in aplicatie? (1) Da, (2) Nu" << endl;
            cin >> optiune;

            if (optiune == 2)
            {
                ramai_conectat = false;
                cout << "La revedere, utilizator!" << endl;
            }

        } while (ramai_conectat == true);
    }
    else
        cout << "Optiune invalida!" << endl;

    cout << "------------------------------------------------------------------------" << endl;

    return 0;
}