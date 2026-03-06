#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool checkOnesSegment(string s) {
        bool hasZero = false;
        for (char c : s) {
            if (c == '0') {
                hasZero = true;
            } else if (hasZero) {
                return false;
            }
        }
        return true;
    }
};