#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    int target = 0;
    // std::unordered_map<int, std::unordered_map<int, int>> dp;
    std::vector<std::vector<int>> dp1; // 使用2D VECTOR來代替 unordered_map，會快超多
    int recursive_solve(int sum, int index, std::vector<int> &nums) {
        // std::cout << "sum:" << sum << " ,index:" << index << ", nums[index]:" << nums[index] << '\n';
        if (sum == target)
            return 1;
        if (index >= nums.size() || sum > target || dp1[index][sum] != 0)
            return -1;
        if ((recursive_solve(sum + nums[index], index + 1, nums) == 1) || recursive_solve(sum, index + 1, nums) == 1)
            return 1;
        return dp1[index][sum] = -1;
    }

    bool canPartition(std::vector<int> &nums) {
        for (auto i : nums)
            target += i;
        if (target & 1)
            return false;
        target /= 2;
        dp1.assign(nums.size(), std::vector<int>(target + 1, 0)); // 初始化 dp 表格
        if (recursive_solve(0, 0, nums) == 1)
            return true;
        return false;
    }
};
int main() {
    Solution solution;
    std::vector<int> nums {1, 2, 5}; // 1,1,3,9,9,10   7,8,9,9
    std::cout << solution.canPartition(nums) << '\n';
    return 0;
}
// DATA TEST
// [1,5,11,5]
// [1,2,3,5]
// [100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,99,97]
// [14,9,8,4,3,2]
// [10,9,9,9,9,8,7,3,1,1]
// [18,17,18,11,15,4,13,11,9]  //=> 4,9,11,11,13,15,17,18,18  | 4,9,13,15,17 (58) 41,26,13,4,0
// [14,75,64,20,95,78,6,98,77,4,71,66,78,44,4,46,77,46,4,84,18,14,52,5,89,26,12,48,71,35,57,10,59,69,35,70,34,80,80,66,91,9,36,91,85,24,46,45,54,86,3,40,30,23,24,4,88,50,42,25,41,60,27,47,92,92,49,50,56,94,9,82,49,41,18,1,23,85,8,48,55,59,82,82,12,84,47,45,41,28,22,15,50,9,64,91,6,94,14,31]