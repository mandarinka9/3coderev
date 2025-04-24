#include "tree.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "������� ��� ����� � ���������� �������: ";
    string filename;
    cin >> filename;

    vector<string> tokens = ReadTokensFromFile(filename);
    if (tokens.empty()) {
        return 1;
    }

    int index = 0;
    TreeNode* root = BuildTreeFromPrefix(tokens, index);
    if (!root) {
        return 1;
    }

    cout << "�������� ������: ";
    PrintTree(root);
    cout << endl;

    TreeNode* transformed_root = TransformTree(root);

    cout << "��������������� ������: ";
    PrintTree(transformed_root);
    cout << endl;
    cout << "��������� �� ������: " << transformed_root << endl;
    cout << "�������� �����: " << transformed_root->value << endl;

    DeleteTree(transformed_root);
    return 0;
}