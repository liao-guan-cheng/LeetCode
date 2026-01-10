#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int n = s1.size();
        int m = s2.size();
        //建立(n+1 x m+1)的dp陣列，初始值為0
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        //當S2是空字串時，刪除S1所有字元
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = dp[i - 1][0] + s1[i - 1];
        }
        //當S1是空字串時，刪除S2所有字元
        for (int j = 1; j <= m; ++j) {
            dp[0][j] = dp[0][j - 1] + s2[j - 1];
        }
        //填表
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];    //字元相同，不需要刪除
                } else {                            //字元不同，選代價小的
                    dp[i][j] = min(dp[i - 1][j] + s1[i - 1],   //刪除s1的字元
                                   dp[i][j - 1] + s2[j - 1]);  //刪除s2的字元
                }
            }
        }
        return dp[n][m];
    }
};
