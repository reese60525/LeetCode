/*
 * 題目: https://leetcode.com/problems/minimum-bit-flips-to-convert-number/description/
 *
 * 題目解釋:
 * 給一對數字，試問其二進制有多少bit不同。
 *
 * 思路:
 * 利用xor運算過濾所有相同bit，再用and運算計算有幾個不同bit。
 *
 * 解法:
 * 同上所述。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int minBitFlips(int start, int goal) {
        int ans = 0;
        int x = start ^ goal; // 進行xor運算，若bit不同則會變成1，例如010 xor 110 = 100

        while (x > 0) {
            ans += x & 1; // 將x最右邊的bit和1做and運算，如果為1則ans+1
            x >>= 1;      // 運算後將x向右位移1bit
        }

        return ans;
    }
};

int main() {
    return 0;
}