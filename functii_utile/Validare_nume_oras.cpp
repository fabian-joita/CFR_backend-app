#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

bool ValidareOras(string &oras)
{
    char oras_copie[30];

    strncpy(oras_copie, oras.c_str(), sizeof(oras_copie) - 1);
    oras_copie[sizeof(oras_copie) - 1] = '\0';

    bool valid = true;

    for (int i = 0; i < strlen(oras_copie); i++)
    {
        if (!isalpha(oras_copie[i]) && !isspace(oras_copie[i]))
        {
            valid = false;
            break;
        }
    }

    if (valid)
    {
        cout << "Orasul este valid: contine doar litere si spatii.\n";
        return true;
    }
    else
    {
        cout << "Orasul NU este valid: contine alte caractere.\n";
        return false;
    }
}