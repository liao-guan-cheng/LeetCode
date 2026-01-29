#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long D[26][26];
    const long long INF = 1e15; // 定義一個足夠大但不至於相加溢位的無限大

    void FW(vector<char>& original, vector<char>& changed, vector<int>& cost) {
        // 1. 初始化
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                D[i][j] = (i == j) ? 0 : INF;
            }
        }

        // 2. 填入初始邊 (處理重複邊取最小值)
        for (int i = 0; i < original.size(); i++) {
            int u = original[i] - 'a';
            int v = changed[i] - 'a';
            D[u][v] = min(D[u][v], (long long)cost[i]);
        }

        // 3. Floyd-Warshall 主迴圈
        for (int k = 0; k < 26; k++) {
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < 26; j++) {
                    if (D[i][k] + D[k][j] < D[i][j]) {
                        D[i][j] = D[i][k] + D[k][j];
                    }
                }
            }
        }
    }

    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        FW(original, changed, cost);
        
        long long total_cost = 0;
        for (int i = 0; i < source.size(); i++) {
            int u = source[i] - 'a';
            int v = target[i] - 'a';
            if (D[u][v] >= INF) return -1;
            total_cost += D[u][v];
        }
        return total_cost;
    }
};