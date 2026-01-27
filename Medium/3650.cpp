#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        // 1. 建立鄰接串列
        // pair<int, int> -> (鄰居, 權重)
        vector<vector<pair<int, int>>> adj(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            // 原始邊：從 u 到 v，花費 w
            adj[u].push_back({v, w});
            // 反轉邊：從 v 到 u，花費 2*w
            adj[v].push_back({u, 2 * w});
        }

        // 2. 初始化 Dijkstra
        // 使用 long long 防止溢位
        // dist 設為 -1 或極大值表示尚未到達
        vector<long long> dist(n, -1);
        
        // priority_queue 預設是大，我們要找小
        // 儲存格式: {cost, node}
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

        // 起點初始化 dist[i]表示從起點到 i 的最小花費
        dist[0] = 0;
        pq.push({0, 0});

        // 3. 開始走訪
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            // 如果目前的距離已經大於紀錄的距離，跳過 (優化)
            if (d > dist[u] && dist[u] != -1) continue;

            // 遍歷鄰居
            for (auto& [v, weight] : adj[u]) {
                if (dist[v] == -1 || dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist[n - 1];
    }
};