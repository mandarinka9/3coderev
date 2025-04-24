/*
Юный путешественник решил изучить схему авиационного сообщения Схема авиационного сообщения 
задана в текстовом файле с именем FileName. в виде матрицы смежности. Первая строка файла 
содержит количество городов (n) n<=25, связанных авиационным сообщением, а следующие n строк
хранят матрицу (m), m[i][j]=0, если не имеется возможности перелета из города i в город j, 
иначе m[i][j]=1. Определить номера городов, в которые из города K можно долететь ровно с L 
пересадками для самого короткого пути. Перечислите номера таких городов в порядке возрастания. 
Нумерация городов начинается с 1. Если таких городов нет, выведите число (-1).
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX_CITIES = 25;

// Функция для поиска городов с заданным числом пересадок
vector<int> FindReachableCities(const string& filename,
    const int start_city,
    const int transfers) {
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return { -1 };
    }

    int total_cities;
    input_file >> total_cities;

    if (total_cities > MAX_CITIES || start_city < 1 || start_city > total_cities) {
        cerr << "Ошибка: некорректные входные параметры" << endl;
        return { -1 };
    }

    vector<vector<int>> adjacency_matrix(total_cities, vector<int>(total_cities));
    for (int i = 0; i < total_cities; ++i) {
        for (int j = 0; j < total_cities; ++j) {
            input_file >> adjacency_matrix[i][j];
        }
    }

    queue<pair<int, int>> search_queue; 
    vector<bool> visited_cities(total_cities, false);
    vector<int> result_cities;

    search_queue.push({ start_city - 1, 0 });
    visited_cities[start_city - 1] = true;

    while (!search_queue.empty()) {
        auto current = search_queue.front();
        search_queue.pop();

        if (current.second == transfers) {
            result_cities.push_back(current.first + 1);
            continue;
        }

        for (int neighbor = 0; neighbor < total_cities; ++neighbor) {
            if (adjacency_matrix[current.first][neighbor] == 1 &&
                !visited_cities[neighbor]) {
                visited_cities[neighbor] = true;
                search_queue.push({ neighbor, current.second + 1 });
            }
        }
    }

    if (result_cities.empty()) {
        return { -1 };
    }

    sort(result_cities.begin(), result_cities.end());
    return result_cities;
}

int main() {
    setlocale(LC_ALL, "Russian");

    string filename;
    cout << "Введите имя файла с матрицей смежности: ";
    cin >> filename;

    int start_city, target_transfers;
    cout << "Введите номер начального города (1..n): ";
    cin >> start_city;
    cout << "Введите количество пересадок L: ";
    cin >> target_transfers;

    vector<int> reachable_cities = FindReachableCities(filename,
        start_city,
        target_transfers);

    cout << "Достижимые города: ";
    for (const auto& city : reachable_cities) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}
