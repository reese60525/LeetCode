/*
 * 題目: https://leetcode.com/problems/single-number-ii/description/
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
    int singleNumber(std::vector<int> &nums) {
        int ans = 0;

        for (int i = 0; i < 32; ++i) {
            int sum = 0;
            for (const int num : nums)
                sum += num >> i & 1;
            sum %= 3;
            ans += sum << i;
        }

        return ans;
    }
};

int main() {

    return 0;
}