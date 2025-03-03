/*
 * 題目：https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-i/description/
 *
 * 題目解釋：
 * 給一個integer array banned 和兩個integer n 和 maxSum，從 1 ~ n 之中，找出不存在於
 * banned 的數字，將這些數字相加的總和必須小於 maxSum，請問最多可以選擇幾個數字。
 * e.g.
 * banned = {1, 6, 3, 5}, n = 8, maxSum = 15
 * 能選的數字為: {2, 4, 7, 8}，可以選 {2, 4, 7} 使其總和 13 < maxSum 且能選出最多數字。
 *
 * 思路：
 * 以上面的例子來看，原本可選擇 {1, 2, 3, 4, 5, 6, 7, 8}，去除掉 banned 中的數字後，
 * 變成 {x, 2, x, 4, x, x, 7, 8}，因此可以先將 banned 建立 hash map，然後遍歷
 * 1 ~ n，如果當前數字沒有在 banned 中，就將其加入總和，直到總和超過 maxSum 為止。
 */
#include <iostream>
#include <unordered_map>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int maxCount(std::vector<int>& banned, int n, int maxSum) {
        // std::unordered_map<int, bool> banned_map; // 很慢，190 ms
        std::bitset<10001> banned_map; // 0 ms
        for (int i = 0; i < banned.size(); ++i) {
            banned_map[banned[i]] = true;
        }

        int count = 0;
        for (int i = 1; i <= n; ++i) {
            // i 存在於 banned 中則跳過
            if (banned_map[i]) {
                continue;
            }
            // 總和超過 maxSum 則跳出迴圈
            if (maxSum - i < 0) {
                break;
            }

            maxSum -= i;
            ++count;
        }

        return count;
    }
};

int main() {

    return 0;
}