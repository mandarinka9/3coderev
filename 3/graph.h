#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

using namespace std;

const int MAX_CITIES = 25;

struct CityNode {
    int id;        // Идентификатор города
    int transfers; // Количество сделанных пересадок

    CityNode(int city_id, int t) : id(city_id), transfers(t) {}
};

bool ReadAdjacencyMatrix(const string& filename, vector<vector<int>>& matrix, int& city_count);
vector<int> FindReachableCities(const vector<vector<int>>& graph, int start_city, int max_transfers);

#endif 
