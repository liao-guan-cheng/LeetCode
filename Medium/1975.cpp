#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long totalSum = 0;
        int min = 0;
        int negativeCount = 0;
        bool hasZero = false;
        // 負數為奇數時，可以最後可以移動到剩一個負號
        // 負數為偶數時，可以全部移動成正號

        for(const auto& row : matrix){
            for(int num : row){
                if(num == 0){
                    hasZero = true;
                }
                if(num < 0){
                    negativeCount++;
                    num = -num;
                }
                totalSum += num;
                if(min == 0 || num < min){
                    min = num;
                }
            }
        }
        if(negativeCount % 2 == 1 && !hasZero){
            totalSum -= 2 * min;
        }

        return totalSum;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> matrix = {{-1, 0, -3}, {-4, 5, 6}, {7, 8, 9}};
    cout << sol.maxMatrixSum(matrix) << endl; // Output the result
    return 0;
}