#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    int recursive_solve(int target, int index, int dp[], std::vector<int> nums) {
        // std::cout << "target:" << target << " ,index:" << index << ", nums[index]:" << nums[index] << '\n';
        if (index >= nums.size() || target < nums[index] || dp[target - nums[index]] != 0)
            return -1;
        if (target == nums[index])
            return 1;
        if (recursive_solve(target - nums[index], index + 1, dp, nums) == 1 || recursive_solve(target, index + 1, dp, nums) == 1)
            return 1;
        std::cout << "*****dp[" << target - nums[index] << "] = -1*****" << '\n';
        return dp[target - nums[index]] = -1;
        // return -1;
    }

    bool canPartition(std::vector<int> &nums) {
        int target = 0;
        sort(nums.begin(), nums.end());
        for (auto i : nums)
            target += i;
        if (target & 1)
            return false;
        int dp[target / 2 + 1];
        memset(dp, 0, sizeof(dp));
        if (recursive_solve(target / 2, 0, dp, nums) == 1)
            return true;
        return false;
    }
};
int main() {
    Solution solution;
    std::vector<int> nums {
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 99,  97};
    std::cout << solution.canPartition(nums) << '\n';
    return 0;
}