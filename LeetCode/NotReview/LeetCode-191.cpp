/*
 * 題目: https://leetcode.com/problems/number-of-1-bits/description/
 *
 * 題目解釋:
 * 給一個十進位整數，求轉成二進位後有幾個1。
 *
 * 思路:
 * 基本位元運算。

 * 解法:
 * 和1做and，看2^0是否為1，然後將num shift right 1格。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int hammingWeight(int n) {
        int res = 0;
        while (n > 0) {
            if (n & 1) {
                ++res;
            }
            n >>= 1;
        }
        return res;
    }
};

int main() {

    return 0;
}