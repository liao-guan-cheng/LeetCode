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
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        if(!root) return nullptr;
        //左右兩遍最深深度
        int leftDepth = getDepth(root->left);
        int rightDepth = getDepth(root->right);
        //如果兩邊深度相等，代表該節點就是最深節點的共同祖先
        if(leftDepth == rightDepth){
            return root;
        //如果左邊深度較深，往左子樹找
        } else if(leftDepth > rightDepth){
            return subtreeWithAllDeepest(root->left);
        } else {
        //剩下的就是右邊深度較深，往右子樹找
            return subtreeWithAllDeepest(root->right);
        }
    }
    //用遞迴找深度
    int getDepth(TreeNode* node) {
        if (!node) return 0;
        return 1 + max(getDepth(node->left), getDepth(node->right));
    }
};