#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    long long totalSum = 0;
    long long maxProd = 0;  //最大乘積

    //DFS計算整棵樹的總和
    void getTotalSum(TreeNode* node) {
        if (!node) return;
        totalSum += node->val;
        getTotalSum(node->left);
        getTotalSum(node->right);
    }

    long long findMax(TreeNode* node) {
        if (!node) return 0;
        //DFS計算子樹的和
        long long subTreeSum = node->val + findMax(node->left) + findMax(node->right);
        //計算當前子樹的和，並更新最大乘積
        maxProd = max(maxProd, subTreeSum * (totalSum - subTreeSum));
        return subTreeSum;
    }
    int maxProduct(TreeNode* root) {
        totalSum = 0;
        maxProd = 0;

        getTotalSum(root);
        findMax(root);

        return maxProd % 1000000007;
    }
};