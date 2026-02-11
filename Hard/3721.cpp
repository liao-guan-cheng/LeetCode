#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class SegmentTree {
private:
    int n;
    vector<int> tree_sum, tree_min, tree_max;

    // 向上更新節點資訊
    void pull(int node) {
        int left = node * 2, right = node * 2 + 1;
        tree_sum[node] = tree_sum[left] + tree_sum[right];
        // 區間內的前綴最小值 = min(左區間最小, 左區間總和 + 右區間最小)
        tree_min[node] = min(tree_min[left], tree_sum[left] + tree_min[right]);
        // 區間內的前綴最大值 = max(左區間最大, 左區間總和 + 右區間最大)
        tree_max[node] = max(tree_max[left], tree_sum[left] + tree_max[right]);
    }

public:
    SegmentTree(int n) : n(n) {
        tree_sum.assign(4 * n, 0);
        tree_min.assign(4 * n, 0);
        tree_max.assign(4 * n, 0);
    }

    // 更新特定索引的值 (非遞迴實作)
    void update(int idx, int val) {
        update_recursive(1, 0, n - 1, idx, val);
    }

    void update_recursive(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree_sum[node] = tree_min[node] = tree_max[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) update_recursive(node * 2, start, mid, idx, val);
        else update_recursive(node * 2 + 1, mid + 1, end, idx, val);
        pull(node);
    }

    // 尋找最右邊的前綴和等於 target 的索引
    int find_rightmost(int target) {
        if (tree_min[1] > target || tree_max[1] < target) return -1;
        return find_recursive(1, 0, n - 1, 0, target);
    }

    int find_recursive(int node, int start, int end, int sum_before, int target) {
        if (start == end) return start;
        
        int mid = (start + end) / 2;
        int left_node = node * 2, right_node = node * 2 + 1;
        
        // 優先檢查右子樹
        int sum_after_left = sum_before + tree_sum[left_node];
        // 檢查 target 是否落在右子樹的前綴範圍內
        if (target >= sum_after_left + tree_min[right_node] && 
            target <= sum_after_left + tree_max[right_node]) {
            return find_recursive(right_node, mid + 1, end, sum_after_left, target);
        }
        // 否則往左子樹找
        return find_recursive(left_node, start, mid, sum_before, target);
    }
};

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        SegmentTree st(n);
        unordered_map<int, int> first_occurrence; // 紀錄當前 l 往右看，數字第一次出現的位置
        int result = 0;

        // 從右往左掃描，固定左端點 l
        for (int l = n - 1; l >= 0; --l) {
            int x = nums[l];

            // 如果 x 之前在右邊出現過，它就不再是「第一次出現」，將其貢獻歸零
            if (first_occurrence.count(x)) {
                st.update(first_occurrence[x], 0);
            }

            // 更新當前位置 l 為 x 的第一次出現位置
            first_occurrence[x] = l;
            st.update(l, (x % 2 == 0) ? 1 : -1);

            // 在線段樹中尋找最右邊的 r，使得區間 [l, r] 的平衡值為 0
            int r = st.find_rightmost(0);
            if (r != -1 && r >= l) {
                result = max(result, r - l + 1);
            }
        }
        return result;
    }
};