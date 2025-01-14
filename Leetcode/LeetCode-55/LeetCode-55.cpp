/*
 *  Author      : Reese
 *  Created On  : 2025-01-14 14:02
 *  Description : https://leetcode.com/problems/jump-game/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// DP
class Solution {
  public:
    bool canJump(std::vector<int> &nums) {
        int max_jump = 0, n = nums.size();

        for (int i = 0; i < n; ++i) {
            // 跳不到當前位置，則後面所有位置也都到不了，return false
            if (max_jump < i) {
                return false;
            }
            // 更新 max_jump
            max_jump = std::max(max_jump, nums[i] + i);
        }

        // 每個位置都能到則 return true
        return true;
    }
};

// Greedy
// class Solution {
//   public:
//     bool canJump(std::vector<int> &nums) {
//         int step = 0, n = nums.size();
//         for (int i = n - 2; i >= 0; --i) {
//             ++step;
//             if (nums[i] >= step) {
//                 step = 0;
//             }
//         }

//         return step == 0;
//     }
// };

int main() {

    return 0;
}