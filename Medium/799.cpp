#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        // 建立一個 101x101 的塔，初始化為 0
        // row 最多到 100
        vector<vector<double>> tower(102, vector<double>(102, 0.0));
        
        // 將所有香檳倒入最頂端的杯子 (0, 0)
        tower[0][0] = (double)poured;
        
        for (int i = 0; i <= query_row; ++i) {
            for (int j = 0; j <= i; ++j) {
                // 如果目前的杯子溢出了
                if (tower[i][j] > 1.0) {
                    double excess = (tower[i][j] - 1.0) / 2.0;
                    // 分流給下一層的左下與右下
                    tower[i + 1][j] += excess;
                    tower[i + 1][j + 1] += excess;
                    // 當前杯子留下的上限就是 1.0
                    tower[i][j] = 1.0;
                }
            }
        }
        
        // 回傳目標位置的量，注意不能超過 1.0
        return min(1.0, tower[query_row][query_glass]);
    }
};