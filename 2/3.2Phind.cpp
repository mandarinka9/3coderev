/*
В текстовом файле с именем filename дано арифметическое выражение в префиксной
форме. Операндами в выражении являются целые числа из промежутка от 0 до 9. Используемые
операции: сложение (+), вычитание (-), умножение (*) и деление нацело(/). Постройте дерево,
соответствующее данному выражению. Знаки операций кодируйте числами: сложение(-1), вычитание(-2),
умножение(-3), деление(-4). Преобразуйте дерево так, чтобы в нем не было операций сложения и вычитания.
Иными словами, замените поддеревья, в которых есть сложение или вычитание значением данного поддерева.
Выведите указатель на корень полученного дерева.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Структура узла дерева
struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для построения дерева из префиксного выражения
Node* buildTree(const vector<int>& expression, int& pos) {
    if (pos >= expression.size()) return nullptr;

    Node* node = new Node(expression[pos++]);

    if (node->value >= 0) {  
        return node;
    }

    // Рекурсивно строим левого и правого потомка
    node->left = buildTree(expression, pos);
    node->right = buildTree(expression, pos);

    return node;
}

// Функция для вычисления значения поддерева
int evaluateSubtree(Node* root) {
    if (root == nullptr) return 0;
    if (root->value >= 0) return root->value;

    int leftValue = evaluateSubtree(root->left);
    int rightValue = evaluateSubtree(root->right);

    switch (root->value) {
    case -1: return leftValue + rightValue;  
    case -2: return leftValue - rightValue;  
    case -3: return leftValue * rightValue; 
    case -4: return leftValue / rightValue; 
    default: return 0;
    }
}

// Функция для преобразования дерева (удаление сложения и вычитания)
Node* transformTree(Node* root) {
    if (root == nullptr) return nullptr;

    // Сначала преобразуем поддеревья
    root->left = transformTree(root->left);
    root->right = transformTree(root->right);

    // Если в узле операция сложения или вычитания
    if (root->value == -1 || root->value == -2) {
        int result = evaluateSubtree(root);
        Node* left = root->left;
        Node* right = root->right;
        delete root->left;
        delete root->right;
        delete root;
        return new Node(result);
    }

    return root;
}

// Функция для освобождения памяти
void freeTree(Node* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    setlocale(LC_ALL, "Russian");

    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка: не удалось открыть файл\n";
        return 1;
    }

    vector<int> expression;
    int num;
    while (file >> num) {
        expression.push_back(num);
    }
    file.close();

    int pos = 0;
    Node* root = buildTree(expression, pos);

    if (root == nullptr) {
        cerr << "Ошибка: пустое выражение\n";
        return 1;
    }

    root = transformTree(root);

    cout << "Корень преобразованного дерева: " << root->value << endl;

    freeTree(root);
    return 0;
}
