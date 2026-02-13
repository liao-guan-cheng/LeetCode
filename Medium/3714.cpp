#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
public:
    // 修改函式名稱以匹配 LeetCode 測試介面
    int longestBalanced(string s) {
        int n = s.length();
        int maxLen = 0;

        // 定義 7 種可能的字元組合
        vector<vector<char>> subsets = {
            {'a'}, {'b'}, {'c'},
            {'a', 'b'}, {'b', 'c'}, {'a', 'c'},
            {'a', 'b', 'c'}
        };

        for (const auto& target : subsets) {
            maxLen = max(maxLen, solveForSubset(s, target));
        }

        return maxLen;
    }

private:
    int solveForSubset(const string& s, const vector<char>& target) {
        vector<bool> isTarget(26, false);
        for (char c : target) isTarget[c - 'a'] = true;

        // 使用 map 紀錄差值狀態
        map<vector<int>, int> firstSeen;
        vector<int> counts(target.size(), 0);
        vector<int> diffs(target.size() - 1, 0); 
        
        if (target.size() > 1) {
            firstSeen[diffs] = -1;
        } else {
            // 單一字元處理
            int best = 0, cur = 0;
            for (char c : s) {
                if (c == target[0]) {
                    cur++;
                    best = max(best, cur);
                } else {
                    cur = 0;
                }
            }
            return best;
        }

        int res = 0;
        for (int i = 0; i < s.length(); ++i) {
            if (!isTarget[s[i] - 'a']) {
                // 遇到非目標字元，重置狀態
                firstSeen.clear();
                fill(counts.begin(), counts.end(), 0);
                fill(diffs.begin(), diffs.end(), 0);
                firstSeen[diffs] = i; 
                continue;
            }

            for (int k = 0; k < target.size(); ++k) {
                if (s[i] == target[k]) counts[k]++;
            }

            for (int k = 0; k < (int)target.size() - 1; ++k) {
                diffs[k] = counts[k] - counts[k+1];
            }

            if (firstSeen.count(diffs)) {
                bool allPresent = true;
                for (int c : counts) if (c == 0) allPresent = false;
                if (allPresent) {
                    res = max(res, i - firstSeen[diffs]);
                }
            } else {
                firstSeen[diffs] = i;
            }
        }
        return res;
    }
};