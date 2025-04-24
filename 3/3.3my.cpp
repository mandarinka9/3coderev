/*
Юный путешественник решил изучить схему авиационного сообщения Схема авиационного сообщения
задана в текстовом файле с именем FileName. в виде матрицы смежности. Первая строка файла
содержит количество городов (n) n<=25, связанных авиационным сообщением, а следующие n строк
хранят матрицу (m), m[i][j]=0, если не имеется возможности перелета из города i в город j,
иначе m[i][j]=1. Определить номера городов, в которые из города K можно долететь ровно с L
пересадками для самого короткого пути. Перечислите номера таких городов в порядке возрастания.
Нумерация городов начинается с 1. Если таких городов нет, выведите число (-1).
 */

#include "graph.h"
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

bool ReadAdjacencyMatrix(const string& filename, vector<vector<int>>& matrix, int& city_count) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return false;
    }

    file >> city_count;

    if (city_count <= 0 || city_count > MAX_CITIES) {
        cerr << "Ошибка: некорректное количество городов" << endl;
        return false;
    }

    matrix.resize(city_count, vector<int>(city_count));
    for (int i = 0; i < city_count; ++i) {
        for (int j = 0; j < city_count; ++j) {
            file >> matrix[i][j];
            if (matrix[i][j] != 0 && matrix[i][j] != 1) {
                cerr << "Ошибка: некорректное значение в матрице" << endl;
                return false;
            }
        }
    }

    return true;
}

vector<int> FindReachableCities(const vector<vector<int>>& graph, int start_city, int max_transfers) {
    const int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> result;

    queue<CityNode> search_queue;
    search_queue.push(CityNode(start_city, 0));
    visited[start_city] = true;

    while (!search_queue.empty()) {
        CityNode current = search_queue.front();
        search_queue.pop();

        if (current.transfers == max_transfers) {
            result.push_back(current.id + 1); 
            continue;
        }

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (graph[current.id][neighbor] == 1 && !visited[neighbor]) {
                visited[neighbor] = true;
                search_queue.push(CityNode(neighbor, current.transfers + 1));
            }
        }
    }

    if (result.empty()) {
        return vector<int>{-1};
    }
    else {
        return result;
    }
}