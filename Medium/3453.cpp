#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        double low = 2e9, high = -2e9;
        double totalArea = 0.0;
        for (const auto& s : squares) {
            double x = s[0], y = s[1], l = s[2];
            low = min(low, y);
            high = max(high, y + l);
            totalArea += l * l;
        }
        double ans = low;
        for (int i = 0; i < 100; ++i) {
            double mid = low + (high - low) / 2.0;
            if (checkBelow(squares, mid) >= totalArea / 2.0) {
                ans = mid;    // 下方面積夠大，嘗試往低處找（因為要找 minimum y）
                high = mid;
            } else {
                low = mid;    // 下方面積不夠，往高處找
            }
        }

        return ans;
    }

private:
    // 輔助函式：計算在水平線 lineY 以下的總面積
    double checkBelow(const vector<vector<int>>& squares, double lineY) {
        double area = 0;
        for (const auto& s : squares) {
            double y = s[1], l = s[2];
            if (lineY <= y) {
                // 線在正方形下方
                continue;
            } else if (lineY >= y + l) {
                // 線在正方形上方
                area += l * l;
            } else {
                // 線切過正方形
                area += l * (lineY - y);
            }
        }
        return area;
    }
};