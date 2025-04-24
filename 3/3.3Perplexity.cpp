/*
Юный путешественник решил изучить схему авиационного сообщения Схема авиационного сообщения
задана в текстовом файле с именем FileName. в виде матрицы смежности. Первая строка файла
содержит количество городов (n) n<=25, связанных авиационным сообщением, а следующие n строк
хранят матрицу (m), m[i][j]=0, если не имеется возможности перелета из города i в город j,
иначе m[i][j]=1. Определить номера городов, в которые из города K можно долететь ровно с L
пересадками для самого короткого пути. Перечислите номера таких городов в порядке возрастания.
Нумерация городов начинается с 1. Если таких городов нет, выведите число (-1).
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для умножения двух матриц
vector<vector<int>> multiply(const vector<vector<int>>& a, const vector<vector<int>>& b, int n) {
    vector<vector<int>> res(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}

// Функция для возведения матрицы в степень
vector<vector<int>> matrixPower(const vector<vector<int>>& m, int power, int n) {
    vector<vector<int>> result(n, vector<int>(n, 0));
    vector<vector<int>> temp = m;

    // Инициализация единичной матрицы
    for (int i = 0; i < n; ++i) {
        result[i][i] = 1;
    }

    while (power > 0) {
        if (power % 2 == 1) {
            result = multiply(result, temp, n);
        }
        temp = multiply(temp, temp, n);
        power /= 2;
    }
    return result;
}

// Функция для решения задачи поиска городов с L пересадками из города K
vector<int> solve(const string& fileName, int K, int L) {
    ifstream in(fileName);
    // Проверяем, удалось ли открыть файл
    if (!in.is_open()) {
        cerr << "Error: Could not open file '" << fileName << "'!" << endl;
        return { -1 };
    }

    int n;
    in >> n;
    // Проверяем, что количество городов валидно
    if (n <= 0 || n > 25) {
        cerr << "Error: Invalid number of cities!" << endl;
        return { -1 };
    }
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> matrix[i][j];
            // Проверяем, что значение в матрице валидно
            if (matrix[i][j] != 0 && matrix[i][j] != 1) {
                cerr << "Error: Invalid value in adjacency matrix!" << endl;
                return { -1 };
            }
        }
    }

    vector<vector<int>> poweredMatrix = matrixPower(matrix, L + 1, n);
    vector<int> cities;

    for (int j = 0; j < n; ++j) {
        if (poweredMatrix[K - 1][j] > 0 && j != K - 1) {
            cities.push_back(j + 1);
        }
    }

    sort(cities.begin(), cities.end());
    return cities.empty() ? vector<int>{-1} : cities;
}

int main() {
    setlocale(LC_ALL, "Russian");

    string fileName;
    int K, L;

    cout << "Введите имя файла: ";
    cin >> fileName;
    cout << "Введите K и L: ";
    cin >> K >> L;

    vector<int> result = solve(fileName, K, L);
    for (int city : result) {
        cout << city << " ";
    }
    cout << endl;
    return 0;
}
