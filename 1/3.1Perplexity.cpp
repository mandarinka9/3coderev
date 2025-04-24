/*
Напишите программу-телеграф, которая принимает от пользователя сообщение и выводит
его на экран в виде последовательности точек и тире.
*/
#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>
#include <stdexcept> 

using namespace std; 

const unordered_map<char, string> MORSE_CODE = {
    {'А', "·−"}, {'Б', "−···"}, {'В', "·−−"}, {'Г', "−−·"}, {'Д', "−··"},
    {'Е', "·"}, {'Ж', "···−"}, {'З', "−−··"}, {'И', "··"}, {'Й', "·−−−"},
    {'К', "−·−"}, {'Л', "·−··"}, {'М', "−−"}, {'Н', "−·"}, {'О', "−−−"},
    {'П', "·−−·"}, {'Р', "·−·"}, {'С', "···"}, {'Т', "−"}, {'У', "··−"},
    {'Ф', "··−·"}, {'Х', "····"}, {'Ц', "−·−·"}, {'Ч', "−−−·"}, {'Ш', "−−−−"},
    {'Щ', "−−·−"}, {'Ъ', "·−−·−·"}, {'Ы', "−·−−"}, {'Ь', "−··−"}, {'Э', "··−··"},
    {'Ю', "··−−"}, {'Я', "·−·−"}
};

void validateInput(char c) {
    if (MORSE_CODE.find(c) == MORSE_CODE.end() && c != ' ') {
        throw invalid_argument("Неподдерживаемый символ: " + string(1, c));
    }
}

string convertToMorse(const string& input) {
    string result;
    for (char c : input) {
        c = toupper(c);
        validateInput(c);

        if (c == ' ') {
            result += "  ";
        }
        else {
            result += MORSE_CODE.at(c) + " ";
        }
    }
    return result;
}

int main() {
    string input;
    cout << "Введите сообщение (русскими буквами): ";
    getline(cin, input);

    try {
        cout << convertToMorse(input) << endl;
    }
    catch (const invalid_argument& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
