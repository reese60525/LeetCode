/*
 * 題目: https://leetcode.com/problems/the-number-of-beautiful-subsets/description/
 *
 * 題目解釋:
 * 給一組整數nums array和一個整數k，如果nums的subset內任意兩個element相減後的絕對值不等於k，則該
 * subset被稱為beautiful subset，請計算nums共有幾種beautiful subset，不包含空集合{}。
 * subset的定義:nums的subset是一個可以從nums中刪除一些(可能沒有)元素來獲得的數組。且僅當選擇的要刪
 * 除的index不同時，兩個subset才不同。
 * EX:nums = {1, 2, 2, 5}，k = 1。
 * beautiful subset = {1}、{2}、{2}、{5}、{1, 5}、{2, 2}、{2, 5}、{2, 5}、{2, 2, 5}，可以
 * 看到相同的num但index不同也會被視為不同的subset，subset。
 *
 * 思路:
 * backtracking algorithm，並且用hashtable紀錄當前的subset有哪些num。
 *
 * 解法:
 *
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 1,4,7,10 = {} {1} {4} {7} {10} {1 7} {1 10} {4 10} = 8
// 2,5,8 = {} {2} {5} {8} {2 8} = 5
// 3,6,9 = {} {3} {6} {9} {3 9} = 5
// 5 * 5 * 8 = 200
// 200 - {} = 199
// 尚未完成
class Solution {
  public:
    int beautifulSubsets(std::vector<int> &nums, int k) {
        int res = 1, min_num = 1001, max_num = 0;
        std::unordered_map<int, int> table;
        std::unordered_map<int, bool> visited;
        std::vector<std::vector<int>> groups;

        std::sort(nums.begin(), nums.end());
        for (auto num : nums) {
            ++table[num];
            min_num = std::min(min_num, num);
            max_num = std::max(max_num, num);
        }

        for (auto n : nums) {
            if (!visited[n]) {
                int x = n;
                std::vector<int> group;
                while (x >= min_num) {
                    if (table[x] > 0) {
                        group.push_back(x);
                        visited[x] = true;
                    }
                    x -= k;
                }
                x = n + k;
                while (x <= max_num) {
                    if (table[x] > 0) {
                        group.push_back(x);
                        visited[x] = true;
                    }
                    x += k;
                }
                groups.push_back(group);
            }
        }

        for (auto g : groups) {
            for (auto i : g) {
                std::cout << i << ' ';
            }
            std::cout << '\n';
        }

        for (auto g : groups) {}

        return res - 1;
    }
};

// // backtracking algorithm
// class Solution {
//   public:
//     int beautifulSubsets(std::vector<int> &nums, int k) {
//         int res = 0;
//         std::unordered_map<int, int> table;

//         std::sort(nums.begin(), nums.end());
//         backTracking(0, k, res, table, nums);
//         return res - 1;
//     }

//   private:
//     void backTracking(int index, int &k, int &res, std::unordered_map<int, int> &table,
//                       std::vector<int> &nums) {
//         if (index == nums.size()) {
//             ++res;
//             return;
//         }

//         if (table[nums[index] - k] == 0) {
//             ++table[nums[index]];
//             backTracking(index + 1, k, res, table, nums);
//             --table[nums[index]];
//         }
//         backTracking(index + 1, k, res, table, nums);
//     }
// };

int main() {
    return 0;
}