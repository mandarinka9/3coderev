#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>

using namespace std;

// Структура узла дерева выражений
struct TreeNode {
    int value;     
    TreeNode* left;  
    TreeNode* right; 

    explicit TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Прототипы функций
vector<string> ReadTokensFromFile(const string& filename);
TreeNode* BuildTreeFromPrefix(const vector<string>& tokens, int& index);
int EvaluateSubtree(TreeNode* node);
TreeNode* TransformTree(TreeNode* root);
void PrintTree(const TreeNode* root);
void DeleteTree(TreeNode* root);

#endif 
