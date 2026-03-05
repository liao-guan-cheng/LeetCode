#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        int count0 = 0;
        for(int i = 0; i < n; i++) {
            if(i % 2 == 0 && s[i] == '0') {
                count0++;
            } else if(i % 2 == 1 && s[i] == '1') {
                count0++;
            }
        }
        return min(count0, n - count0);
    }
};