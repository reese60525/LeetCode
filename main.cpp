/*
 * 題目： https://leetcode.com/problems/4sum/description/
 *
 * 題目解釋：
 * 給一組整數array和整數target，找出所有四個整數組合使其總和等於target，並且該組合
 * 不能重複。
 *
 * 思路：
 *
 */
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
    std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target) {
        if (nums.size() < 4) {
            return {};
        }

        std::vector<std::vector<int>> res;

        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() - 3; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            for (int j = i + 1; j < nums.size() - 2; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }

                int l = j + 1, r = nums.size() - 1;
                while (l < r) {
                    int sum = nums[i] + nums[j] + nums[l] + nums[r];

                    while (l < r && sum < target) {
                        ++l;
                        sum = nums[i] + nums[j] + nums[l] + nums[r];
                    }
                    while (l < r && sum > target) {
                        --r;
                        sum = nums[i] + nums[j] + nums[l] + nums[r];
                    }

                    if (sum == target) {
                        res.push_back({nums[i], nums[j], nums[l], nums[r]});
                        ++l;
                        --r;
                        while (l < r && nums[l] == nums[l - 1]) {
                            ++l;
                        }
                        while (l < r && nums[r] == nums[r + 1]) {
                            --r;
                        }
                    }
                }
            }
        }

        return res;
    }
};

int main() {

    return 0;
}