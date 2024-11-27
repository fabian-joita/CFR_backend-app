#include <iostream>
#include <string>
#include <cctype>
#include "putere_parola.h"

using namespace std;

string verificaParola(string &parola)
{
    int lungime = parola.length();
    bool areLiteraMica = false, areLiteraMare = false;
    bool areCifra = false, areCaractereSpeciale = false;

    for (size_t i = 0; i < parola.length(); ++i)
    {
        char c = parola[i];
        if (islower(c))
            areLiteraMica = true;
        else if (isupper(c))
            areLiteraMare = true;
        else if (isdigit(c))
            areCifra = true;
        else
            areCaractereSpeciale = true;
    }

    int scor = 0;
    if (areLiteraMica)
        scor++;
    if (areLiteraMare)
        scor++;
    if (areCifra)
        scor++;
    if (areCaractereSpeciale)
        scor++;

    if (lungime < 8)
    {
        throw "Parola este prea scurta, trebuie sa aiba cel putin 8 caractere!";
    }
    else if (lungime >= 12 && scor >= 4)
    {
        cout << "Puternica: Parola este foarte sigura." << endl;
        return "Puternica";
    }
    else if (lungime >= 8 && scor >= 2)
    {
        cout << "Medie: Parola este acceptabila, dar poate fi imbunatatita." << endl;
        return "Medie";
    }
    else
    {
        throw "Slaba: Parola este nesigura.";
    }
}
