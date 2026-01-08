#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        //把num1和num2的點乘起來，相加最大值
        //Dynamic Programming
        int n = nums1.size();
        int m = nums2.size();
        //dp[i][j]表示nums1前i個元素和nums2前j個元素的最大點乘和
        //建立(n+1 x m+1)的dp陣列，初始值為INT_MIN
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MIN));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                dp[i][j] = max({dp[i - 1][j],   //不選nums1[i-1]
                                dp[i][j - 1],   //不選nums2[j-1]
                                max(0, dp[i - 1][j - 1]) + nums1[i - 1] * nums2[j - 1]});   //選nums1[i-1]和nums2[j-1]
            }
        }
        return dp[n][m];
    }
};