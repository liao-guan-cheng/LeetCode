#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        // 補上邊界
        hFences.push_back(1);
        hFences.push_back(m);
        vFences.push_back(1);
        vFences.push_back(n);

        // 取得所有可能的間距
        unordered_set<int> hGaps = getAllGap(hFences);
        unordered_set<int> vGaps = getAllGap(vFences);

        long long maxSide = -1;
        for(int gap : hGaps) {
            if(vGaps.count(gap)) {
                maxSide = max(maxSide, static_cast<long long>(gap));
            }
        }

        if(maxSide == -1) return -1;

        long long mod = 1e9 + 7;
        return (maxSide * maxSide) % mod;
    }
    unordered_set<int> getAllGap(const vector<int>& fences) {
        unordered_set<int> gaps;
        int size = fences.size();
        // 計算所有兩兩之間的差值
        for(int i=0; i<size; ++i) {
            for(int j=i+1; j<size; ++j) {
                gaps.insert(abs(fences[j] - fences[i]));
            }
        }
        return gaps;
    }
};