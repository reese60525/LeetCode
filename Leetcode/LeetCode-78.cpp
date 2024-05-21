/*
 * 題目: https://leetcode.com/problems/subsets/description/
 *
 * 題目解釋:
 * 給一組nums，求所有不重複的subset。
 *
 * 思路:
 * 窮舉所有組合。時間複雜度O(2^n)。
 *
 * 解法:
 * 1.backtracking algorithm。
 * 用遞迴去窮舉所有可能，每次遞迴都能分支成當前數字選或是不選。
 * 2.bit manipulation。
 * 組合共有2^n種，n為nums的size，可以使用雙迴圈來解，外迴圈遍歷2^n次，用來表示各種不同組合，EX:{1,2,3}有2^3 = 8種
 * 組合，因此外迴圈的i若是以2進制來看，i = {000, 001, 010, 011, 100, 101, 110, 111}正好每個狀態都能對應到一種組
 * 合，而內迴圈遍歷nums，並以i的值來判斷當前nums[j]是否該被放入res[i]中。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 解法2: bit manipulation
class Solution {
  public:
    std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
        int n = nums.size();
        std::vector<std::vector<int>> res(1 << n); // 1 << n代表2^n。

        for (int i = 0; i < 1 << n; ++i) { // 迭代2^n種組合
            for (int j = 0; j < n; ++j) {  // 對每種組合迭代nums
                if (i & 1 << j) {          // 以i的值判斷當前bit是否該放入num
                    res[i].emplace_back(nums[j]);
                }
            }
        }
        return res;
    }
};

// // 解法1: backtracing algorithm
// class Solution {
//   public:
//     std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
//         std::vector<std::vector<int>> res;
//         std::vector<int> arr;

//         backTracking(0, arr, nums, res);
//         return res;
//     }

//   private:
//     void backTracking(int index, std::vector<int> &arr, std::vector<int> &nums, std::vector<std::vector<int>> &res) {
//         if (index == nums.size()) {
//             res.emplace_back(arr);
//             return;
//         }

//         arr.emplace_back(nums[index]);
//         backTracking(index + 1, arr, nums, res);
//         arr.pop_back();
//         backTracking(index + 1, arr, nums, res);
//     }
// };

int main() {
    return 0;
}
