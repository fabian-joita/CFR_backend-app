#include <iostream>
#include <string>
#include <unordered_map>
#include "criptare.h"

using namespace std;

const string set_caractere = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*() ";

int getCharIndex(char c)
{
    return set_caractere.find(c);
}

char getCharFromIndex(int index)
{
    return set_caractere[index];
}

string vigenereEncrypt(const string &plaintext, const string &key)
{
    string ciphertext = "";
    int keyLength = key.length();
    int setSize = set_caractere.length();

    for (size_t i = 0; i < plaintext.length(); i++)
    {
        int plainIndex = getCharIndex(plaintext[i]);
        int keyIndex = getCharIndex(key[i % keyLength]);
        int cipherIndex = (plainIndex + keyIndex) % setSize;
        ciphertext += getCharFromIndex(cipherIndex);
    }
    return ciphertext;
}

string vigenereDecrypt(const string &ciphertext, const string &key)
{
    string plaintext = "";
    int keyLength = key.length();
    int setSize = set_caractere.length();

    for (size_t i = 0; i < ciphertext.length(); i++)
    {
        int cipherIndex = getCharIndex(ciphertext[i]);
        int keyIndex = getCharIndex(key[i % keyLength]);
        int plainIndex = (cipherIndex - keyIndex + setSize) % setSize;
        plaintext += getCharFromIndex(plainIndex);
    }
    return plaintext;
}
