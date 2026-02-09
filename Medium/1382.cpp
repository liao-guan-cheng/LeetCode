#include<iostream>
#include<vector>
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
    vector<int> sortedVals;

    // 中序遍歷：把樹轉成排序數組
    void inorder(TreeNode* root) {
        if (!root) return;
        inorder(root->left);
        sortedVals.push_back(root->val);
        inorder(root->right);
    }

    // 核心邏輯：從數組區間 [left, right] 建立平衡 BST
    TreeNode* buildBalancedBST(int left, int right) {
        if (left > right) return nullptr;

        // 挑選中間索引作為根節點，這是平衡的關鍵
        int mid = left + (right - left) / 2;
        TreeNode* node = new TreeNode(sortedVals[mid]);

        // 遞迴處理左右兩半
        node->left = buildBalancedBST(left, mid - 1);
        node->right = buildBalancedBST(mid + 1, right);

        return node;
    }

    TreeNode* balanceBST(TreeNode* root) {
        sortedVals.clear();
        inorder(root); // 先把資料拿出來
        return buildBalancedBST(0, sortedVals.size() - 1); // 再重新蓋回去
    }
};