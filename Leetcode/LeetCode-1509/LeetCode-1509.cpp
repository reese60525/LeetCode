/*
 *  Author      : Reese
 *  Created On  : 2024-12-26 18:34
 *  Description :
 *  https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// Greedy
class Solution {
  public:
    int minDifference(std::vector<int> &nums) {
        // size 小於 5 的 必定為 0
        if (nums.size() < 5) {
            return 0;
        }

        // 維護前四大和前四小的 array
        auto func = [&](std::vector<int> &arr, int &num, int flag) -> void {
            int idx = 0, n = arr.size();
            // 找可以被 num 取代的 element
            while (idx < n && num * flag >= arr[idx] * flag) {
                ++idx;
            }
            // 從被取代的 element 向後更新
            if (idx < n) {
                for (size_t i = n - 1; i > idx; --i) {
                    arr[i] = arr[i - 1];
                }
                arr[idx] = num;
            }
        };

        // 找前四大和前四小的數
        std::vector<int> min_arr(4, INT_MAX), max_arr(4, INT_MIN + 1);
        for (int &num : nums) {
            func(min_arr, num, 1);
            func(max_arr, num, -1);
        }

        // i 表示最小的數有幾個被移除，則最大的數會有 3 - i 個被移除
        int res = INT_MAX;
        for (size_t i = 0; i < 4; ++i) {
            res = std::min(res, std::abs(min_arr[i] - max_arr[3 - i]));
        }

        return res;
    }
};

// // Sorting
// class Solution {
//   public:
//     int minDifference(std::vector<int> &nums) {
//         // size 小於 5 的 必定為 0
//         if (nums.size() < 5) {
//             return 0;
//         }

//         int n = nums.size();
//         std::sort(nums.begin(), nums.end());

//         return std::min({
//             nums[n - 4] - nums[0], // 移除最大的三個值
//             nums[n - 3] - nums[1], // 移除最大的兩個值和最小的一個值
//             nums[n - 2] - nums[2], // 移除最大的一個值和最小的兩個值
//             nums[n - 1] - nums[3]  // 移除最小的三個值
//         });
//     }
// };

int main() {

    return 0;
}