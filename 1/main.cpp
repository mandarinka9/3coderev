#include "morse.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Введите сообщение для преобразования в азбуку Морзе:\n";
    string input;
    getline(cin, input);

    string morse;
    if (!convertToMorse(input, morse)) {
        cerr << "Ошибка преобразования сообщения" << endl;
        return 1;
    }

    cout << "Результат:\n" << morse << endl;
    return 0;
}
