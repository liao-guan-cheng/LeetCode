#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // 預處理每行
        vector<vector<int>> rowSum(m, vector<int>(n + 1, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                rowSum[i][j + 1] = rowSum[i][j] + grid[i][j];
            }
        }
        
        // 預處理每列
        vector<vector<int>> colSum(n, vector<int>(m + 1, 0));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                colSum[j][i + 1] = colSum[j][i] + grid[i][j];
            }
        }

        // 從最大的可能邊長 k 開始試
        for (int k = min(m, n); k >= 2; --k) {
            for (int i = 0; i <= m - k; ++i) {
                for (int j = 0; j <= n - k; ++j) {
                    if (check(grid, rowSum, colSum, i, j, k)) return k;
                }
            }
        }
        
        return 1; // 1x1 永遠是 Magic Square
    }

private:
    bool check(vector<vector<int>>& grid, vector<vector<int>>& rowSum, vector<vector<int>>& colSum, int r, int c, int k) {
        // 拿第一行的和當基準值
        int target = rowSum[r][c + k] - rowSum[r][c];
        
        // 檢查每一列 (Rows)
        for (int i = r + 1; i < r + k; ++i) {
            if (rowSum[i][c + k] - rowSum[i][c] != target) return false;
        }
        
        // 檢查每一行 (Cols)
        for (int j = c; j < c + k; ++j) {
            if (colSum[j][r + k] - colSum[j][r] != target) return false;
        }
        
        // 檢查兩條對角線 (Diagonals) - 這裡 k 不大，直接用迴圈跑
        int d1 = 0, d2 = 0;
        for (int i = 0; i < k; ++i) {
            d1 += grid[r + i][c + i];
            d2 += grid[r + i][c + k - 1 - i];
        }
        if (d1 != target || d2 != target) return false;
        
        return true;
    }
};