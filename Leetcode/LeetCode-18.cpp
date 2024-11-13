/*
 * 題目： https://leetcode.com/problems/4sum/description/
 *
 * 題目解釋：
 * 給一組整數array和整數target，找出所有四個整數組合使其總和等於target，並且該組合
 * 不能重複。
 *
 * 思路：
 * 用雙迴圈遍歷前兩個數的組合，然後在此雙迴圈中用two pointer找另外兩個數字。
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
        if (nums.size() < 4) { // array數字數量不足以湊一組
            return {};
        }

        std::vector<std::vector<int>> res;

        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() - 3; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) { // 重複的數字要跳過
                continue;
            }

            long long cur_max = (long long)nums[nums.size() - 1] * 4; // 當前所能達到的最大組合
            long long cur_min = (long long)nums[i] * 4;               // 當前所能達到的最小組合
            if (cur_max < target || cur_min > target) {               // 無法滿足target的話就跳出迴圈
                break;
            }

            for (int j = i + 1; j < nums.size() - 2; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) { // 重複的數字要跳過
                    continue;
                }

                int l = j + 1, r = nums.size() - 1;
                while (l < r) {
                    while (l < r && (long long)nums[i] + nums[j] + nums[l] + nums[r] < target) {
                        ++l;
                    }
                    while (l < r && (long long)nums[i] + nums[j] + nums[l] + nums[r] > target) {
                        --r;
                    }

                    if (l < r && (long long)nums[i] + nums[j] + nums[l] + nums[r] == target) {
                        res.push_back({nums[i], nums[j], nums[l], nums[r]});
                        ++l;
                        --r;
                        while (l < r && nums[l] == nums[l - 1]) { // 重複的數字要跳過
                            ++l;
                        }
                        while (l < r && nums[r] == nums[r + 1]) { // 重複的數字要跳過
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