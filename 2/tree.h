#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>

using namespace std;

/**
 * @brief Структура узла дерева выражений
 * 
 * Содержит целочисленное значение (операнд или код операции),
 * а также указатели на левое и правое поддеревья.
 */
struct TreeNode {
    int value;     ///< Значение узла (операнд 0-9 или код операции: -1..-4)
    TreeNode* left;  ///< Указатель на левое поддерево
    TreeNode* right; ///< Указатель на правое поддерево

    /**
     * @brief Конструктор узла дерева
     * @param val Значение узла
     */
    explicit TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

/**
 * @brief Читает токены из файла
 * @param filename Имя файла для чтения
 * @return Вектор строк-токенов
 */
vector<string> ReadTokensFromFile(const string& filename);

/**
 * @brief Строит дерево из префиксной записи
 * @param tokens Вектор токенов
 * @param index Текущий индекс в векторе токенов (передается по ссылке)
 * @return Указатель на корень построенного дерева
 */
TreeNode* BuildTreeFromPrefix(const vector<string>& tokens, int& index);

/**
 * @brief Вычисляет значение поддерева
 * @param node Корень поддерева
 * @return Результат вычисления поддерева
 */
int EvaluateSubtree(TreeNode* node);

/**
 * @brief Преобразует дерево, заменяя операции сложения/вычитания их результатами
 * @param root Корень дерева для преобразования
 * @return Указатель на корень преобразованного дерева
 */
TreeNode* TransformTree(TreeNode* root);

/**
 * @brief Выводит дерево в инфиксной форме
 * @param root Корень дерева для печати
 */
void PrintTree(const TreeNode* root);

/**
 * @brief Удаляет дерево и освобождает память
 * @param root Корень дерева для удаления
 */
void DeleteTree(TreeNode* root);

#endif
