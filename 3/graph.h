/**
 * @file graph.h
 * @brief Заголовочный файл для работы с графами городов и маршрутами
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

using namespace std;

/**
 * @brief Максимальное количество городов, поддерживаемое программой
 */
const int MAX_CITIES = 25;

/**
 * @brief Структура узла города в графе
 * 
 * Содержит информацию о городе и количестве пересадок,
 * сделанных для достижения этого города.
 */
struct CityNode {
    int id;        // Идентификатор города (нумерация с 0)
    int transfers; // Количество сделанных пересадок до этого города

    /**
     * @brief Конструктор узла города
     * @param city_id Идентификатор города
     * @param t Количество пересадок
     */
    CityNode(int city_id, int t) : id(city_id), transfers(t) {}
};

/**
 * @brief Читает матрицу смежности из файла
 * 
 * @param filename Имя файла для чтения
 * @param matrix Ссылка на вектор для сохранения матрицы смежности
 * @param city_count Ссылка на переменную для сохранения количества городов
 * @return true если чтение прошло успешно, false в случае ошибки
 */
bool ReadAdjacencyMatrix(const string& filename, vector<vector<int>>& matrix, int& city_count);

/**
 * @brief Находит все достижимые города за ограниченное число пересадок
 * 
 * @param graph Матрица смежности графа городов
 * @param start_city Начальный город (индекс в матрице)
 * @param max_transfers Максимальное допустимое количество пересадок
 * @return Вектор идентификаторов достижимых городов
 */
vector<int> FindReachableCities(const vector<vector<int>>& graph, int start_city, int max_transfers);

#endif
