#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
//特定組合似乎有問題。
class Solution {
  public:
    int target = 0;
    int recursive_solve(int sum, int index, int dp[], std::vector<int> nums) {
        std::cout << "sum:" << sum << " ,index:" << index << ", nums[index]:" << nums[index] << '\n';
        if (index >= nums.size())
            return 0;
        if ((sum + nums[index] > target))
            return -1;
        if (sum + nums[index] == target)
            return 1;

        if (dp[sum + nums[index]] == 0)
            dp[sum + nums[index]] = recursive_solve(sum + nums[index], index + 1, dp, nums);
        if (dp[sum] == 0)
            dp[sum] = recursive_solve(sum, index + 1, dp, nums);
        if (dp[sum + nums[index]] == 1 || dp[sum] == 1)
            return 1;
        else {
            std::cout << "\n*********************************************" << '\n';
            std::cout << "sum:" << sum << " ,index:" << index << ", nums[index]:" << nums[index] << '\n';
            std::cout << "dp[" << sum + nums[index] << "] = -1" << ", dp[" << sum << "] = -1" << '\n';
            std::cout << "*********************************************" << '\n';
            return -1;
        }
    }

    bool canPartition(std::vector<int> &nums) {
        sort(nums.begin(), nums.end());
        for (auto i : nums)
            target += i;
        if (target & 1)
            return false;
        target /= 2;
        int dp[target + 1];
        memset(dp, 0, sizeof(dp));
        if (recursive_solve(0, 0, dp, nums) == 1)
            return true;
        return false;
    }
};
int main() {
    Solution solution;
    std::vector<int> nums {18, 17, 18, 11, 15, 4, 13, 11, 9}; // 4,9,11,11,13,15,17,18,18  | 4,9,13,15,17 (58) 41,26,13,4,0
    std::cout << solution.canPartition(nums) << '\n';
    return 0;
}
// DATA TEST
// [1,5,11,5]
// [1,2,3,5]
// [100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,99,97]
// [14,9,8,4,3,2]
// [10,9,9,9,9,8,7,3,1,1]
// [18,17,18,11,15,4,13,11,9]