/*
 * 題目: https://leetcode.com/problems/count-complete-subarrays-in-an-array/
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
    int countCompleteSubarrays(std::vector<int> &nums) {
        int res = 0, nums_count = 0;
        bool check[2001] {0};

        // 找出nums中總共有幾個相異的數字
        for (const int &n : nums) {
            if (!check[n]) {
                check[n] = true;
                ++nums_count;
            }
        }

        int j = 0, table[2001] {0}, window_count = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (; j < nums.size(); ++j) {
                if (++table[nums[j]] == 1) {
                    ++window_count;
                }
                if (window_count == nums_count) {
                    res += nums.size() - j;
                    if (--table[nums[i]] == 0) {
                        --window_count;
                    }
                    if (--table[nums[j]] == 0) {
                        --window_count;
                    }
                    break;
                }
            }
        }

        return res;
    }
};

int main() {
    return 0;
}