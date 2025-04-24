/*
В текстовом файле с именем filename дано арифметическое выражение в префиксной
форме. Операндами в выражении являются целые числа из промежутка от 0 до 9. Используемые
операции: сложение (+), вычитание (-), умножение (*) и деление нацело(/). Постройте дерево,
соответствующее данному выражению. Знаки операций кодируйте числами: сложение(-1), вычитание(-2),
умножение(-3), деление(-4). Преобразуйте дерево так, чтобы в нем не было операций сложения и вычитания.
Иными словами, замените поддеревья, в которых есть сложение или вычитание значением данного поддерева.
Выведите указатель на корень полученного дерева.
 */

#include "tree.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

vector<string> ReadTokensFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл: " << filename << endl;
        return {};
    }

    vector<string> tokens;
    string token;
    while (file >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        cerr << "Ошибка: файл пуст" << endl;
    }

    return tokens;
}

TreeNode* BuildTreeFromPrefix(const vector<string>& tokens, int& index) {
    if (index >= tokens.size()) {
        return nullptr;
    }

    const string& token = tokens[index++];

    // Обработка операторов
    if (token == "+") {
        TreeNode* node = new TreeNode(-1);
        node->left = BuildTreeFromPrefix(tokens, index);
        node->right = BuildTreeFromPrefix(tokens, index);
        return node;
    }
    if (token == "-") {
        TreeNode* node = new TreeNode(-2);
        node->left = BuildTreeFromPrefix(tokens, index);
        node->right = BuildTreeFromPrefix(tokens, index);
        return node;
    }
    if (token == "*") {
        TreeNode* node = new TreeNode(-3);
        node->left = BuildTreeFromPrefix(tokens, index);
        node->right = BuildTreeFromPrefix(tokens, index);
        return node;
    }
    if (token == "/") {
        TreeNode* node = new TreeNode(-4);
        node->left = BuildTreeFromPrefix(tokens, index);
        node->right = BuildTreeFromPrefix(tokens, index);
        return node;
    }

    // Обработка операндов
    try {
        int value = stoi(token);
        if (value < 0 || value > 9) {
            cerr << "Ошибка: число должно быть от 0 до 9: " << token << endl;
            return nullptr;
        }
        return new TreeNode(value);
    }
    catch (...) {
        cerr << "Ошибка: некорректный токен: " << token << endl;
        return nullptr;
    }
}

int EvaluateSubtree(TreeNode* node) {
    if (!node) {
        cerr << "Ошибка: пустое поддерево при вычислении" << endl;
        return 0;
    }

    if (node->value >= 0) {
        return node->value;
    }

    int left_val = EvaluateSubtree(node->left);
    int right_val = EvaluateSubtree(node->right);

    switch (node->value) {
    case -1: return left_val + right_val;
    case -2: return left_val - right_val;
    case -3: return left_val * right_val;
    case -4:
        if (right_val == 0) {
            cerr << "Ошибка: деление на ноль" << endl;
            return 0;
        }
        return left_val / right_val;
    default:
        cerr << "Ошибка: неизвестная операция: " << node->value << endl;
        return 0;
    }
}

TreeNode* TransformTree(TreeNode* root) {
    if (!root) {
        return nullptr;
    }

    root->left = TransformTree(root->left);
    root->right = TransformTree(root->right);

    if (root->value == -1 || root->value == -2) {
        int val = EvaluateSubtree(root);
        delete root->left;
        delete root->right;
        return new TreeNode(val);
    }

    return root;
}

void PrintTree(const TreeNode* root) {
    if (!root) {
        return;
    }

    if (root->left) {
        cout << "(";
        PrintTree(root->left);
    }

    if (root->value >= 0) {
        cout << root->value;
    }
    else {
        switch (root->value) {
        case -1: cout << "+"; break;
        case -2: cout << "-"; break;
        case -3: cout << "*"; break;
        case -4: cout << "/"; break;
        }
    }

    if (root->right) {
        PrintTree(root->right);
        cout << ")";
    }
}

void DeleteTree(TreeNode* root) {
    if (!root) {
        return;
    }
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
}