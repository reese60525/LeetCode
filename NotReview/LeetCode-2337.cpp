/*
 * 題目： https://leetcode.com/problems/move-pieces-to-obtain-a-string/description/
 *
 * 題目解釋：
 * 給兩個字串長度相同的 s 和 t，其中 s 和 t 由 'L'、'R' 和 '_' 組成，可以對 s 進行以下操作：
 * 1. 如果 s[i] = 'L' and s[i - 1] = '_'，能將兩者交換。
 * 2. 如果 s[i] = 'R' and s[i + 1] = '_'，能將兩者交換。
 * 試問 s 經過以上的操作後是否能變成 t。
 *
 * 思路：
 * 想將 s[i] 的 'L' 配對 t[j] 的 'L' ，如果 s[i] 所在位置比 t[j] 小(靠左)，則因為 'L'
 * 只能向左移動，s[i] 無論如何操作都無法到達 t[j] 的位置，相對地 'R' 也是一樣的邏輯， 如果
 * s[i] 的 'R' 所在位置比 t[j] 大(靠右)，則因為 'R' 只能向右移動，s[i] 無論如何操作也都無
 * 法到達 和 t[j] 相同的位置。
 * 因此可以用 two pointer 遍歷 s 和 t 取得要匹配的字元，如果字元相同則根據以上的邏輯來進行判
 * 斷，若是判斷後 s 不可能變成 t，return false。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    bool canChange(std::string &start, std::string &target) {
        size_t len = start.length();

        for (size_t i = 0, j = 0; i < len || j < len; ++i, ++j) {
            // 各自取得要匹配的字元
            while (j < len && target[j] == '_') {
                ++j;
            }
            while (i < len && start[i] == '_') {
                ++i;
            }

            // 若兩字串已遍歷完，則 s 可以變成 t
            if (i == len && j == len) {
                return true;
            }
            // 如果字元不同或字元相同但位置不合判斷，則 s 不可能變成 t
            if (start[i] != target[j] || (start[i] == 'L' && i < j) || (start[i] == 'R' && i > j)) {
                return false;
            }
        }

        // 若能順利遍歷完 s 和 t 則 s 可以變成 t
        return true;
    }
};

int main() {

    return 0;
}