#include "graph.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    // Ввод параметров
    cout << "Введите имя файла: ";
    string filename;
    cin >> filename;

    vector<vector<int>> adjacency_matrix;
    int city_count;
    if (!ReadAdjacencyMatrix(filename, adjacency_matrix, city_count)) {
        return 1;
    }

    cout << "Введите номер начального города (1-" << city_count << "): ";
    int start_city;
    cin >> start_city;

    cout << "Введите количество пересадок L: ";
    int target_transfers;
    cin >> target_transfers;

    // Проверка входных данных
    if (start_city < 1 || start_city > city_count) {
        cerr << "Ошибка: неверный номер начального города" << endl;
        return 1;
    }

    // Поиск городов
    vector<int> reachable_cities = FindReachableCities(
        adjacency_matrix,
        start_city - 1,
        target_transfers
    );

    cout << "Результат: ";
    for (const auto& city : reachable_cities) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}