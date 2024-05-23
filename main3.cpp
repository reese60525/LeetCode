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

// backtracking algorithm
class Solution {
  public:
    int beautifulSubsets(std::vector<int> &nums, int k) {
        int res = 0;
        std::unordered_map<int, int> table;

        std::sort(nums.begin(), nums.end());
        backTracking(0, k, res, table, nums);
        return res - 1;
    }

  private:
    void backTracking(int index, int &k, int &res, std::unordered_map<int, int> &table,
                      std::vector<int> &nums) {
        if (index == nums.size()) {
            ++res;
            return;
        }

        if (table[nums[index] - k] == 0) {
            ++table[nums[index]];
            backTracking(index + 1, k, res, table, nums);
            --table[nums[index]];
        }
        backTracking(index + 1, k, res, table, nums);
    }
};

int main() { return 0; }