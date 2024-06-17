/*
 * 題目: https://leetcode.com/problems/sum-of-square-numbers/description/
 *
 * 題目解釋:
 *
 * 思路:
 *
 * 解法:
 *
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    bool judgeSquareSum(int c) {
        long long int l = 0, r = std::sqrt(c), pow_l = 0, pow_r = r * r;

        while (l <= r) {
            long long int sum = pow_l + pow_r;
            if (sum == c) {
                return true;
            }
            else if (sum < c) {
                ++l;
                pow_l = l * l;
            }
            else {
                --r;
                pow_r = r * r;
            }
        }

        return false;
    }
};

int main() {

    return 0;
}