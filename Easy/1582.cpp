#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        int count = 0;
        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[0].size(); j++) {
                if (mat[i][j] == 1) {
                    bool isSpecial = true;
                    for (int k = 0; k < mat.size(); k++) {
                        if (k != i && mat[k][j] == 1) {
                            isSpecial = false;
                            break;
                        }
                    }
                    for (int k = 0; k < mat[0].size(); k++) {
                        if (k != j && mat[i][k] == 1) {
                            isSpecial = false;
                            break;
                        }
                    }
                    if (isSpecial) {
                        count++;
                    }
                }
            }
        }
        return count;
    }
};