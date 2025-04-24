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
#include <queue>
#include <string>

// Структура для хранения информации о городе в очереди
struct CityInfo {
    int city;
    int transfers;
    CityInfo(int c, int t) : city(c), transfers(t) {}
};

// Функция для поиска городов с заданным количеством пересадок
std::vector<int> findCitiesWithTransfers(const std::vector<std::vector<int>>& graph,
    int startCity, int transfers) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::vector<int> result;

    std::queue<CityInfo> q;
    q.push(CityInfo(startCity, 0));
    visited[startCity] = true;

    while (!q.empty()) {
        CityInfo current = q.front();
        q.pop();

        if (current.transfers == transfers) {
            result.push_back(current.city);
        }
        else if (current.transfers < transfers) {
            for (int i = 0; i < n; ++i) {
                if (graph[current.city][i] == 1 && !visited[i]) {
                    q.push(CityInfo(i, current.transfers + 1));
                    visited[i] = true;
                }
            }
        }
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::string filename;
    std::cout << "Введите имя файла: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка: не удалось открыть файл\n";
        return 1;
    }

    int n;
    file >> n;

    std::vector<std::vector<int>> graph(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> graph[i][j];
        }
    }
    file.close();

    int startCity, transfers;
    std::cout << "Введите номер начального города (1-" << n << "): ";
    std::cin >> startCity;
    std::cout << "Введите количество пересадок: ";
    std::cin >> transfers;

    if (startCity < 1 || startCity > n) {
        std::cerr << "Ошибка: неверный номер города\n";
        return 1;
    }

    std::vector<int> result = findCitiesWithTransfers(graph, startCity - 1, transfers);

    if (result.empty()) {
        std::cout << "-1\n";
    }
    else {
        for (int city : result) {
            std::cout << city << " ";
        }
        std::cout << "\n";
    }

    return 0;
}