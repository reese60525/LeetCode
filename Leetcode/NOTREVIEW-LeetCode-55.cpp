/*
 * 題目: https://leetcode.com/problems/jump-game/description/
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
    bool canJump(std::vector<int> &nums) {
        int n = nums.size();

        if (n == 1) {
            return true;
        }

        for (int i = 0; i < n; ++i) {
            if (nums[i] >= (n - i - 1)) {
                return true;
            }
            if (nums[i] == 0) {
                int j = i;
                while (j > -1) {
                    if (nums[j] > (i - j)) {
                        break;
                    }
                    --j;
                }
                if (j == -1) {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {

    return 0;
}