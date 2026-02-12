#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    int longestBalanced(std::string s) {
        int n = s.length();
        int maxLen = 0;

        // 遍歷子字串的起點
        for (int i = 0; i < n; ++i) {
            std::vector<int> count(26, 0); // 統計字頻 (Frequency)
            
            // 遍歷子字串的終點
            for (int j = i; j < n; ++j) {
                count[s[j] - 'a']++;
                
                // 檢查目前子字串 s[i...j] 是否平衡
                if (isBalanced(count)) {
                    maxLen = std::max(maxLen, j - i + 1);
                }
            }
        }
        return maxLen;
    }

private:
    bool isBalanced(const std::vector<int>& count) {
        int targetFreq = -1;
        
        for (int i = 0; i < 26; ++i) {
            if (count[i] > 0) {
                if (targetFreq == -1) {
                    // 記錄第一個遇到的字元頻率作為基準
                    targetFreq = count[i];
                } else if (count[i] != targetFreq) {
                    // 若後續出現的字元頻率不一致，則不平衡
                    return false;
                }
            }
        }
        return targetFreq != -1; // 確保子字串非空
    }
};