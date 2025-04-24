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
#include <cctype>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

size_t pos = 0;

// Функция для получения следующего токена из выражения.
char nextToken(const string& expr) {
    while (pos < expr.size() && isspace(expr[pos])) {
        pos++;
    }
    if (pos < expr.size()) {
        return expr[pos++];
    }
    return '\0';
}

// Функция для построения дерева разбора из префиксной записи.
TreeNode* parseTree(const string& expr) {
    char c = nextToken(expr);
    if (c == '\0') {
        return nullptr;
    }

    if (isdigit(c)) {
        // Если токен - цифра, создаем листовой узел.
        return new TreeNode(c - '0');
    }
    else {
        // Если токен - оператор, создаем узел операции.
        int opCode = 0;
        switch (c) {
        case '+':
            opCode = -1;
            break;
        case '-':
            opCode = -2;
            break;
        case '*':
            opCode = -3;
            break;
        case '/':
            opCode = -4;
            break;
        default:
            // Обработка ошибки, если встретился неизвестный оператор.
            cout << "Ошибка: неверный оператор: " << c << endl;
            return nullptr;
        }

        TreeNode* node = new TreeNode(opCode);
        node->left = parseTree(expr);
        node->right = parseTree(expr);
        return node;
    }
}

// Функция для вычисления значения поддерева.
int eval(TreeNode* node) {
    if (!node->left && !node->right) {
        return node->val;
    }

    int leftVal = eval(node->left);
    int rightVal = eval(node->right);

    switch (node->val) {
    case -1:
        return leftVal + rightVal;
    case -2:
        return leftVal - rightVal;
    case -3:
        return leftVal * rightVal;
    case -4:
        // Проверка деления на ноль.
        if (rightVal == 0) {
            cout << "Ошибка: деление на ноль." << endl;
            return 0;  
        }
        return leftVal / rightVal;
    default:
        cout << "Ошибка: неизвестная операция при вычислении." << endl;
        return 0;
    }
}

// Функция для преобразования дерева: заменяем + и - на вычисленные значения.
TreeNode* transform(TreeNode* node) {
    if (!node) {
        return nullptr;
    }

    if (!node->left && !node->right) {
        // Если это лист, ничего не делаем.
        return node;
    }

    node->left = transform(node->left);
    node->right = transform(node->right);

    if (node->val == -1 || node->val == -2) {
        // Если текущий узел - + или -, вычисляем значение поддерева.
        int value = eval(node);

        // Удаляем старые поддеревья.
        delete node->left;
        delete node->right;

        // Превращаем текущий узел в лист с вычисленным значением.
        node->left = node->right = nullptr;
        node->val = value;
    }

    return node;
}

int main() {
    setlocale(LC_ALL, "Russian");

    string filename;
    cout << "Введите имя файла: ";
    getline(cin, filename);

    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return 1;
    }

    string expr;
    getline(fin, expr);
    fin.close();

    // Проверка, что выражение не пустое.
    if (expr.empty()) {
        cout << "Ошибка: файл содержит пустое выражение." << endl;
        return 1;
    }

    pos = 0;
    TreeNode* root = parseTree(expr);

    // Проверка, что дерево построено успешно.
    if (!root) {
        cout << "Ошибка: не удалось построить дерево." << endl;
        return 1;
    }

    root = transform(root);

    cout << "Указатель на корень дерева: " << root << endl;

    return 0;
}
