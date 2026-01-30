#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        int n = source.length();
        // 1. 將所有字串映射為 ID
        unordered_map<string, int> strToId;
        int idCount = 0;
        
        // 找出所有在 original 或 changed 出現過的長度，優化 DP 搜尋
        vector<int> lengths;
        auto getID = [&](string& s) {
            if (strToId.find(s) == strToId.end()) {
                strToId[s] = idCount++;
            }
            return strToId[s];
        };

        for (int i = 0; i < original.size(); ++i) {
            getID(original[i]);
            getID(changed[i]);
        }

        // 2. 初始化 Floyd-Warshall 矩陣
        long long INF = 1e18; // 使用足夠大的數代表無限大
        vector<vector<long long>> dist(idCount, vector<long long>(idCount, INF));
        for (int i = 0; i < idCount; ++i) dist[i][i] = 0;

        for (int i = 0; i < original.size(); ++i) {
            int u = strToId[original[i]];
            int v = strToId[changed[i]];
            dist[u][v] = min(dist[u][v], (long long)cost[i]);
        }

        // Floyd-Warshall 計算任兩字串間最短路徑
        for (int k = 0; k < idCount; ++k) {
            for (int i = 0; i < idCount; ++i) {
                for (int j = 0; j < idCount; ++j) {
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        // 3. DP 過程
        vector<long long> dp(n + 1, INF);
        dp[0] = 0;

        // 先整理出所有可能的字串長度，減少不必要的迴圈
        vector<int> distinctLens;
        for (auto& s : original) distinctLens.push_back(s.length());
        sort(distinctLens.begin(), distinctLens.end());
        distinctLens.erase(unique(distinctLens.begin(), distinctLens.end()), distinctLens.end());

        for (int i = 0; i < n; ++i) {
            if (dp[i] == INF) continue;

            // 狀況 A: 字元相同，直接跳過
            if (source[i] == target[i]) {
                dp[i + 1] = min(dp[i + 1], dp[i]);
            }

            // 狀況 B: 嘗試轉換子字串
            for (int len : distinctLens) {
                if (i + len > n) break;
                string sSub = source.substr(i, len);
                string tSub = target.substr(i, len);
                
                if (strToId.count(sSub) && strToId.count(tSub)) {
                    int u = strToId[sSub];
                    int v = strToId[tSub];
                    if (dist[u][v] < INF) {
                        dp[i + len] = min(dp[i + len], dp[i] + dist[u][v]);
                    }
                }
            }
        }

        return dp[n] == INF ? -1 : dp[n];
    }
};