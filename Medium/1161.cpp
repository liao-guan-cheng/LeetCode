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
    int maxLevelSum(TreeNode* root) {
        if(!root) return 0;
        int maxSum = root->val;
        int maxLevel = 1;
        vector<TreeNode*> currentLevel;
        currentLevel.push_back(root);
        int level = 1;
        while(!currentLevel.empty()){   // BFS traversal
            vector<TreeNode*> nextLevel;
            int levelSum = 0;
            for(auto node : currentLevel){
                levelSum += node->val;
                if(node->left) nextLevel.push_back(node->left);
                if(node->right) nextLevel.push_back(node->right);
            }
            if(levelSum > maxSum){
                maxSum = levelSum;
                maxLevel = level;
            }
            currentLevel = nextLevel;
            level++;
        }
        return maxLevel;
    }
};

int main() {
    Solution sol;
    // Example usage:
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(7);
    root->right = new TreeNode(0);
    root->left->left = new TreeNode(7);
    root->left->right = new TreeNode(-8);

    cout << sol.maxLevelSum(root) << endl; // Output the result
    return 0;
}