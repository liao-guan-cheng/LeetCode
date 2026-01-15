#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>

using namespace std;

/**
 * SegmentTree: 專門處理「線段聯集長度」的線段樹
 * 這種線段樹不需要 Lazy Propagation，因為區間修改是成對出現的（y 和 y+l）。
 */
class SegmentTree {
private:
    vector<int> count;    // 紀錄該區間被覆蓋了幾次
    vector<int> covered;  // 紀錄該區間實際被覆蓋的長度 (Union Length)
    vector<int> xs;       // 離散化後的 X 座標陣列
    int n;

    // 核心修改函式
    void modify(int qleft, int qright, int qval, int left, int right, int pos) {
        // 區間不重疊，直接回傳
        if (xs[right + 1] <= qleft || xs[left] >= qright) {
            return;
        }
        // 當前區間完全包含在查詢區間內
        if (qleft <= xs[left] && xs[right + 1] <= qright) {
            count[pos] += qval;
        } else {
            // 標準二分遞迴
            int mid = (left + right) / 2;
            modify(qleft, qright, qval, left, mid, pos * 2 + 1);
            modify(qleft, qright, qval, mid + 1, right, pos * 2 + 2);
        }

        // 更新此節點的 covered 長度
        if (count[pos] > 0) {
            // 如果此區間被覆蓋次數 > 0，覆蓋長度就是該區間總長
            covered[pos] = xs[right + 1] - xs[left];
        } else {
            // 如果沒被完整覆蓋，長度由子節點加總
            if (left == right) {
                covered[pos] = 0;
            } else {
                covered[pos] = covered[pos * 2 + 1] + covered[pos * 2 + 2];
            }
        }
    }

public:
    SegmentTree(vector<int>& xs_) : xs(xs_) {
        n = xs.size() - 1;
        count.resize(4 * n, 0);
        covered.resize(4 * n, 0);
    }

    // 更新區間 [qleft, qright]，qval 為 +1 (進入) 或 -1 (離開)
    void update(int qleft, int qright, int qval) {
        modify(qleft, qright, qval, 0, n - 1, 0);
    }

    // 查詢目前 X 軸上被覆蓋的總聯集長度
    int query() { return covered[0]; }
};

class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        vector<tuple<int, int, int, int>> events; // {y, type, x_left, x_right}
        set<int> xsSet;

        // 1. 建立掃描線事件與 X 座標離散化
        for (auto& sq : squares) {
            int x = sq[0], y = sq[1], l = sq[2];
            int xr = x + l;
            events.emplace_back(y, 1, x, xr);      // 下邊界進入
            events.emplace_back(y + l, -1, x, xr); // 上邊界離開
            xsSet.insert(x);
            xsSet.insert(xr);
        }

        // 依據 Y 座標排序事件
        sort(events.begin(), events.end());
        
        // 離散化 X 座標
        vector<int> xs(xsSet.begin(), xsSet.end());
        SegmentTree segTree(xs);

        vector<double> psum;  // 儲存到目前 y 為止的面積前綴和
        vector<int> widths;   // 儲存每一段 y 區間的聯集寬度
        double total_area = 0.0;
        int prev_y = get<0>(events[0]);

        // 2. Y 軸掃描：計算總面積並紀錄過程
        for (auto& [y, delta, xl, xr] : events) {
            int current_width = segTree.query(); // 取得目前的水平聯集長度
            total_area += 1LL * current_width * (y - prev_y);
            
            // 更新線段樹，加入或移除當前正方形的邊界
            segTree.update(xl, xr, delta);
            
            // 紀錄前綴和與寬度，方便後續計算
            psum.push_back(total_area);
            widths.push_back(segTree.query());
            prev_y = y;
        }

        // 3. 尋找平分面積的高度
        // 目標：下半部面積 = total_area / 2
        
        // 使用 lower_bound 找到第一個累積面積大於等於一半的位置
        int i = lower_bound(psum.begin(), psum.end(), total_area / 2.0) - psum.begin();
        
        // 處理前一個點的數據
        double area_before = (i == 0) ? 0 : psum[i-1];
        int width_at_interval = widths[i-1]; 
        int y_start = get<0>(events[i-1]);

        // 利用插值法計算精確高度：(目標面積 - 已累積面積) / 該段寬度
        double remaining_area_needed = (total_area / 2.0) - area_before;
        
        return y_start + (remaining_area_needed / width_at_interval);
    }
};