/*
 * 題目: https://leetcode.com/problems/continuous-subarray-sum/description/
 *
 * 題目解釋:
 *
 * 思路:
 * 計算所有nums的pre_sum(index0~0 ~ index0~n-1)，如果有兩個pre_sum相同且彼此index相減大於1，
 * 則為答案，另如果當前nums[i] % k = 0要有例外判斷。
 * 解法:
 *
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
    bool checkSubarraySum(std::vector<int> &nums, int k) {
        int sum = 0;
        std::unordered_map<int, int> table;

        for (int i = 0; i < nums.size(); ++i) {
            nums[i] %= k;
            if (nums[i] == 0) {
                if (i > 0 && nums[i - 1] == 0) {
                    return true;
                }
                continue;
            }

            sum += nums[i];
            sum %= k;
            if (((table.find(sum) != table.end()) && ((i - table[sum]) > 1)) || (sum == 0)) {
                return true;
            }
            if (table.find(sum) == table.end()) {
                table[sum] = i;
            }
        }

        return false;
    }
};

int main() {

    return 0;
}