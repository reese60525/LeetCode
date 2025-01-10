/*
 *  Author      : Reese
 *  Created On  : 2025-01-06 08:13
 *  Description : https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<int> minOperations(std::string boxes) {
        // sum 為所有球到 index = i 的距離，一開始 i = 0
        // l 和 r 為 boxes 在 [0,i] 和 [i, n-1] 範圍中各有幾個球
        int sum = 0, l = 0, r = 0, n = boxes.size();
        for (int i = 0; i < n; ++i) {
            sum += (boxes[i] == '1') ? i : 0;
            r += (boxes[i] - '0');
        }

        std::vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            res[i] = sum;
            // 若當前 box 的有球，則計算下個 box 時左邊的球數會加一，右邊減一
            r -= (boxes[i] - '0');
            l += (boxes[i] - '0');
            // 往右移動一個 box，離左邊的球遠一步，離右邊的近一步
            sum -= r;
            sum += l;
        }

        return res;
    }
};

int main() {

    return 0;
}