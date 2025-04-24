/*
Напишите программу-телеграф, которая принимает от пользователя сообщение и выводит
его на экран в виде последовательности точек и тире.
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>

using namespace std;

// Словарь для русских букв и соответствующих кодов Морзе
const unordered_map<char, string> morseCode = {
    {'А', ".-"}, {'Б', "-..."}, {'В', ".--"}, {'Г', "--."},
    {'Д', "-.."}, {'Е', "."}, {'Ж', "...-"}, {'З', "--.."},
    {'И', ".."}, {'Й', ".---"}, {'К', "-.-"}, {'Л', ".-.."},
    {'М', "--"}, {'Н', "-."}, {'О', "---"}, {'П', ".--."},
    {'Р', ".-."}, {'С', "..."}, {'Т', "-"}, {'У', "..-"},
    {'Ф', "..-."}, {'Х', "...."}, {'Ц', "-.-."}, {'Ч', "---."},
    {'Ш', "----"}, {'Щ', "--.-"}, {'Ъ', "--.--"}, {'Ы', "-.--"},
    {'Ь', "-..-"}, {'Э', "..-.."}, {'Ю', "..--"}, {'Я', ".-.-"},
    {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
    {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."},
    {'9', "----."}, {'0', "-----"}, {' ', " "}
};

// Функция для преобразования строки в код Морзе
string convertToMorse(const string& message) {
    string morseMessage;
    for (char c : message) {
        char upperC = toupper(c);
        auto it = morseCode.find(upperC);
        if (it != morseCode.end()) {
            morseMessage += it->second + " ";
        }
    }
    return morseMessage;
}

int main() {
    string inputMessage;

    cout << "Введите сообщение для преобразования в азбуку Морзе: ";
    getline(cin, inputMessage);

    string morseMessage = convertToMorse(inputMessage);

    if (morseMessage.empty()) {
        cerr << "Ошибка: введенное сообщение не содержит символов, поддерживаемых программой." << endl;
        return 1;
    }

    cout << "Сообщение в азбуке Морзе: " << morseMessage << endl;

    return 0;
}
