/*
 * 題目: https://leetcode.com/problems/minimum-increment-to-make-array-unique/description/
 *
 * 題目解釋:
 *
 * 思路:
 *
 * 解法:
 *
 */
#include <iostream>
#include <map>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
// 方法1
class Solution {
  public:
    int minIncrementForUnique(std::vector<int> &nums) {
        int res = 0, n = nums.size();

        std::sort(nums.begin(), nums.end());

        for (int i = 1; i < n; ++i) {
            if (nums[i] == nums[i - 1]) {
                ++res;
                ++nums[i];
            }
            else if (nums[i] < nums[i - 1]) {
                res += (nums[i - 1] - nums[i]) + 1;
                nums[i] = nums[i - 1] + 1;
            }
        }

        return res;
    }
};

// // 方法2
// class Solution {
//   public:
//     int minIncrementForUnique(std::vector<int> &nums) {
//         int res = 0;
//         std::map<int, int> table;

//         for (int &n : nums) {
//             ++table[n];
//         }
//         int n = -1;
//         for (auto &t : table) {
//             n = std::max(t.first + 1, n);
//             while (t.second > 1) {
//                 if (table.find(n) == table.end()) {
//                     table[n] = 1;
//                     --t.second;
//                     res += n - t.first;
//                 }
//                 ++n;
//             }
//         }

//         return res;
//     }
// };

int main() {

    return 0;
}