#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        int n = bottomLeft.size();
        long long maxSide = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                // 1. 找出相交區域的邊界
                int x_left = max(bottomLeft[i][0], bottomLeft[j][0]);
                int x_right = min(topRight[i][0], topRight[j][0]);
                int y_bottom = max(bottomLeft[i][1], bottomLeft[j][1]);
                int y_top = min(topRight[i][1], topRight[j][1]);

                // 2. 計算相交區域的寬與高
                int width = x_right - x_left;
                int height = y_top - y_bottom;

                // 3. 如果有相交，計算最大正方形邊長
                if (width > 0 && height > 0) {
                    long long currentSide = min(width, height);
                    maxSide = max(maxSide, currentSide);
                }
            }
        }
        
        // 返回面積
        return maxSide * maxSide;
    }
};