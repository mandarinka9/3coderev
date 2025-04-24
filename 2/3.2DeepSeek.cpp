/*
В текстовом файле с именем filename дано арифметическое выражение в префиксной
форме. Операндами в выражении являются целые числа из промежутка от 0 до 9. Используемые
операции: сложение (+), вычитание (-), умножение (*) и деление нацело(/). Постройте дерево, 
соответствующее данному выражению. Знаки операций кодируйте числами: сложение(-1), вычитание(-2), 
умножение(-3), деление(-4). Преобразуйте дерево так, чтобы в нем не было операций сложения и вычитания. 
Иными словами, замените поддеревья, в которых есть сложение или вычитание значением данного поддерева. 
Выведите указатель на корень полученного дерева.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// Узел бинарного дерева выражений
struct TreeNode {
    int value;      
    TreeNode* left;  
    TreeNode* right; 

    explicit TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Чтение выражения из файла
vector<string> ReadExpressionFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filename);
    }

    vector<string> tokens;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
    }

    return tokens;
}

// Построение дерева из префиксной записи
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
        return new TreeNode(stoi(token));
    }
    catch (...) {
        throw runtime_error("Некорректный токен: " + token);
    }
}

// Вычисление значения поддерева
int EvaluateSubtree(TreeNode* node) {
    if (!node) return 0;

    // Если это числовой лист
    if (node->value >= 0) {
        return node->value;
    }

    const int left_val = EvaluateSubtree(node->left);
    const int right_val = EvaluateSubtree(node->right);

    switch (node->value) {
    case -1: return left_val + right_val;  
    case -2: return left_val - right_val;  
    case -3: return left_val * right_val;  
    case -4:                              
        if (right_val == 0) throw runtime_error("Деление на ноль");
        return left_val / right_val;
    default: return 0;
    }
}

// Преобразование дерева (замена + и - на вычисленные значения)
TreeNode* TransformTree(TreeNode* root) {
    if (!root) return nullptr;

    // Заменяем узлы сложения/вычитания на их значения
    if (root->value == -1 || root->value == -2) {
        const int val = EvaluateSubtree(root);
        delete root->left;
        delete root->right;
        return new TreeNode(val);
    }

    // Рекурсивно преобразуем поддеревья
    root->left = TransformTree(root->left);
    root->right = TransformTree(root->right);

    return root;
}

// Печать дерева в инфиксной форме
void PrintTree(const TreeNode* root) {
    if (!root) return;

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

// Рекурсивное удаление дерева
void DeleteTree(TreeNode* root) {
    if (!root) return;
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
}

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        cout << "Введите имя файла: ";
        string filename;
        cin >> filename;

        // Построение дерева
        const vector<string> tokens = ReadExpressionFromFile(filename);
        if (tokens.empty()) {
            cout << "Ошибка: файл пуст или содержит некорректные данные\n";
            return 1;
        }

        int index = 0;
        TreeNode* root = BuildTreeFromPrefix(tokens, index);

        // Вывод исходного дерева
        cout << "Исходное дерево: ";
        PrintTree(root);
        cout << endl;

        // Преобразование дерева
        TreeNode* transformed_root = TransformTree(root);

        // Вывод результатов
        cout << "Преобразованное дерево: ";
        PrintTree(transformed_root);
        cout << endl;
        cout << "Указатель на корень: " << transformed_root << endl;

        // Очистка памяти
        DeleteTree(transformed_root);

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
