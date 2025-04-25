#ifndef MORSE_H
#define MORSE_H

#include <string>
#include <unordered_map>
#include <locale>
#include <cctype>

using namespace std;

/**
 * @brief Таблица соответствия русских букв и пробела азбуке Морзе
 * 
 * Ключи - русские буквы в верхнем регистре и пробел,
 * значения - соответствующие коды Морзе
 */
extern const unordered_map<char, string> MORSE_CODE;

/**
 * @brief Проверяет, поддерживается ли символ таблицей Морзе
 * 
 * @param c Символ для проверки
 * @return true если символ поддерживается, false в противном случае
 */
bool validateInput(char c);

/**
 * @brief Преобразует строку в азбуку Морзе
 * 
 * @param input Входная строка для преобразования
 * @param result Строка для сохранения результата преобразования
 * @return true если преобразование прошло успешно, false при ошибке
 */
bool convertToMorse(const string& input, string& result);

#endif
