#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        int maxLen = 0;

        // 外層迴圈：子陣列的起始點 i
        for (int i = 0; i < n; ++i) {
            unordered_set<int> distinctEvens;
            unordered_set<int> distinctOdds;
            
            // 內層迴圈：子陣列的結束點 j
            for (int j = i; j < n; ++j) {
                // 根據奇偶性放入對應的 Set (自動處理相異性)
                if (nums[j] % 2 == 0) {
                    distinctEvens.insert(nums[j]);
                } else {
                    distinctOdds.insert(nums[j]);
                }
                
                // 檢查「相異偶數數量」是否等於「相異奇數數量」
                if (distinctEvens.size() == distinctOdds.size()) {
                    maxLen = max(maxLen, j - i + 1);
                }
            }
        }
        
        return maxLen;
    }
};