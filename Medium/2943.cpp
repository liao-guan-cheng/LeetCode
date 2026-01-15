#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        // 對水平和垂直障礙物排序
        sort(hBars.begin(), hBars.end());
        sort(vBars.begin(), vBars.end());

        int maxHGap = getMaxGap(hBars, n);
        int maxVGap = getMaxGap(vBars, m);

        int side = min(maxHGap, maxVGap);

        return side * side;
    }
    int getMaxGap(const vector<int>& bars, int length) {
        if (bars.empty()) return 1;

        int maxLen = 1;
        int currentLen = 1;
        //i要從1開始
        for(int i=1; i<bars.size(); ++i) {
            // 如果是連續的 +1
            if(bars[i]==bars[i-1]+1){
                currentLen++;
            }
            // 如果不是連續的，則重置 currentLen
            else{
                currentLen=1;
            }
            maxLen = max(maxLen, currentLen);
        }
        return maxLen + 1;
    }
};