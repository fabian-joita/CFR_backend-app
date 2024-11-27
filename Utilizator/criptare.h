#ifndef VIGENERE_H
#define VIGENERE_H

#include <string>
using namespace std;

extern const string set_caractere;

int getCharIndex(char c);
char getCharFromIndex(int index);
string vigenereEncrypt(const string &plaintext, const string &key);
string vigenereDecrypt(const string &ciphertext, const string &key);

#endif // VIGENERE_H
