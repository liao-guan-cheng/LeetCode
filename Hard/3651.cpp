#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int M = 10001; // grid 值的最大範圍
const int NN = 6400; // 80x80 的最大格子數
const int INF = 1e9 + 7;

static int xList[M], nxt[NN];
static unsigned dp[2][NN]; 
static unsigned suffixMin[M]; 

class Solution {
public:
    static inline int idx(int i, int j, int c) { return i * c + j; }

    int minCost(vector<vector<int>>& grid, int k) {
        const int r = grid.size(), c = grid[0].size(), N = r * c;
        
        // 1. 初始化與分組：按 grid 值將座標存入鏈結串列
        memset(xList, -1, sizeof(xList));
        int xMax = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                int x = grid[i][j], p = idx(i, j, c);
                nxt[p] = xList[x];
                xList[x] = p;
                if (x > xMax) xMax = x;
            }
        }

        // 2. Base Case: 0 次傳送 (純走路 DP)
        fill(dp[0], dp[0] + N, INF);
        dp[0][0] = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                int pos = idx(i, j, c);
                if (i > 0) dp[0][pos] = min(dp[0][pos], dp[0][pos - c] + (unsigned)grid[i][j]);
                if (j > 0) dp[0][pos] = min(dp[0][pos], dp[0][pos - 1] + (unsigned)grid[i][j]);
            }
        }

        // 3. 核心 DP 轉移：處理 1 到 k 次傳送
        for (int t = 1; t <= k; t++) {
            const bool curr = t & 1, prev = (t - 1) & 1;
            fill(dp[curr], dp[curr] + N, INF);

            // 計算後綴最小值：從最大的值往回掃
            unsigned currMin = INF;
            for (int x = xMax; x >= 0; x--) {
                for (int e = xList[x]; e != -1; e = nxt[e]) {
                    currMin = min(currMin, dp[prev][e]);
                }
                suffixMin[x] = currMin;
            }

            // 更新當前層的 DP 狀態
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    int pos = idx(i, j, c);
                    int x = grid[i][j];
                    // 核心轉移方程
                    unsigned best = min(dp[prev][pos], suffixMin[x]); // 不動或傳送過來
                    if (i > 0) best = min(best, dp[curr][pos - c] + x); // 從上走來
                    if (j > 0) best = min(best, dp[curr][pos - 1] + x); // 從左走來
                    dp[curr][pos] = best;
                }
            }
        }

        return dp[k & 1][N - 1];
    }
};