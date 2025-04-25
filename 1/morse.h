#ifndef MORSE_H
#define MORSE_H

#include <string>
#include <unordered_map>
#include <locale>
#include <cctype>

using namespace std;

// Таблица соответствия русских букв и пробела азбуке Морзе
extern const unordered_map<char, string> MORSE_CODE;

// Проверка, что символ поддерживается таблицей Морзе
bool validateInput(char c); 

// Преобразование строки в азбуку Морзе
bool convertToMorse(const string& input, string& result);

#endif
