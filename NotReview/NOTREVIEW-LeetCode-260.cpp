/*
 * 題目: https://leetcode.com/problems/single-number-iii/description/
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
    std::vector<int> singleNumber(std::vector<int> &nums) {
        int a = 0, b = 0, ab = 0;

        for (int n : nums) {
            ab ^= n;
        }

        int k = 0;
        for (int i = 0; i < 32; ++i) {
            if (ab >> i & 1) {
                k = i;
                break;
            }
        }

        for (int n : nums) {
            if (n >> k & 1) {
                a ^= n;
            }
            else {
                b ^= n;
            }
        }

        return {a, b};
    }
};

int main() {

    return 0;
}