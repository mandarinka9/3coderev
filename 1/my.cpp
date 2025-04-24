/*
Напишите программу-телеграф, которая принимает от пользователя сообщение и выводит
его на экран в виде последовательности точек и тире.
*/

#include "morse.h"
#include <iostream>

using namespace std;

const unordered_map<char, string> MORSE_CODE = {
    {'А', ".-"}, {'Б', "-..."}, {'В', ".--"}, {'Г', "--."}, {'Д', "-.."},
    {'Е', "."}, {'Ё', "."}, {'Ж', "...-"}, {'З', "--.."}, {'И', ".."},
    {'Й', ".---"}, {'К', "-.-"}, {'Л', ".-.."}, {'М', "--"}, {'Н', "-."},
    {'О', "---"}, {'П', ".--."}, {'Р', ".-."}, {'С', "..."}, {'Т', "-"},
    {'У', "..-"}, {'Ф', "..-."}, {'Х', "...."}, {'Ц', "-.-."}, {'Ч', "---."},
    {'Ш', "----"}, {'Щ', "--.-"}, {'Ъ', "--.--"}, {'Ы', "-.--"}, {'Ь', "-..-"},
    {'Э', "..-.."}, {'Ю', "..--"}, {'Я', ".-.-"},
    {' ', " "}
};

bool validateInput(char c) {
    c = toupper((unsigned char)c);
    if (MORSE_CODE.find(c) == MORSE_CODE.end()) {
        cerr << "Ошибка: Неподдерживаемый символ: " << c << endl;
        return false;
    }
    return true;
}

bool convertToMorse(const string& input, string& result) {
    result.clear();
    for (char c : input) {
        c = toupper((unsigned char)c);
        if (!validateInput(c)) {
            return false;
        }
        result += MORSE_CODE.at(c) + " ";
    }
    return true;
}
