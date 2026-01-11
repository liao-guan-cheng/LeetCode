#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int n = matrix.size();
        int m = matrix[0].size();
        //height[j]表示以當前列為底，行j的高度
        vector<int> height(m, 0);
        int maxArea = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(matrix[i][j] == '1') {
                    height[j]++;
                } else {
                    height[j] = 0;
                }
            }
            //計算以height為高度的直方圖的最大矩形面積
            maxArea = max(maxArea, largestRectangleArea(height));
        }
        return maxArea;
    }
    int largestRectangleArea(const vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n), right(n);
        //計算每個柱子的左邊界
        for(int i = 0; i < n; ++i) {
            left[i] = i;
            //當前柱子比左邊柱子矮，更新左邊界
            while(left[i] > 0 && heights[left[i] - 1] >= heights[i]) {
                left[i] = left[left[i] - 1];
            }
        }
        //計算每個柱子的右邊界
        for(int i = n - 1; i >= 0; --i) {
            right[i] = i;
            //當前柱子比右邊柱子矮，更新右邊界
            while(right[i] < n - 1 && heights[right[i] + 1] >= heights[i]) {
                right[i] = right[right[i] + 1];
            }
        }
        //計算最大矩形面積
        int maxArea = 0;
        for(int i = 0; i < n; ++i) {
            maxArea = max(maxArea, heights[i] * (right[i] - left[i] + 1));
        }
        return maxArea;
    }
};