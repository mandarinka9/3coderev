#include "graph.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    // ���� ����������
    cout << "������� ��� �����: ";
    string filename;
    cin >> filename;

    vector<vector<int>> adjacency_matrix;
    int city_count;
    if (!ReadAdjacencyMatrix(filename, adjacency_matrix, city_count)) {
        return 1;
    }

    cout << "������� ����� ���������� ������ (1-" << city_count << "): ";
    int start_city;
    cin >> start_city;

    cout << "������� ���������� ��������� L: ";
    int target_transfers;
    cin >> target_transfers;

    // �������� ������� ������
    if (start_city < 1 || start_city > city_count) {
        cerr << "������: �������� ����� ���������� ������" << endl;
        return 1;
    }

    // ����� �������
    vector<int> reachable_cities = FindReachableCities(
        adjacency_matrix,
        start_city - 1,
        target_transfers
    );

    cout << "���������: ";
    for (const auto& city : reachable_cities) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}