/*
 * 題目: https://leetcode.com/problems/combination-sum/description/
 *
 * 題目解釋:
 * 給一組nums和一個target整數，使用nums裡的整數，求所有不重複的組合使得相加起來等於target。
 * EX: nums = {2, 3, 5}， target = 7， 不重複的組合有: {2, 2, 3}、{2, 5}，{2, 3, 2}和{5, 2}之類的
 * 是重複組合，不可使用。
 *
 * 思路:
 * backtracking algorithm，對於每個nums都有選和不選兩種選擇，若不選就把當前nums_index + 1，這樣不會有重
 * 複的組合問題。
 *
 * 解法:
 * 如上所說。
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
    std::vector<std::vector<int>> res;

    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target) {
        std::vector<int> temp; // 暫存目前的組合

        std::sort(candidates.begin(), candidates.end()); // 小到大排序
        backTracking(0, target, temp, candidates);
        return res;
    }

  private:
    void backTracking(int index, int target, std::vector<int> &temp, const std::vector<int> &candidates) {
        // 當前index超過array範圍或是target為負，由於candidates是小到大排序，若減去當前的num會造成負數，後面的num也必為負數
        if (index == candidates.size() || target - candidates[index] < 0) {
            return;
        }
        if (target == 0) { // 找到合法的組合
            res.emplace_back(temp);
            return;
        }

        // 選用當前的num
        temp.emplace_back(candidates[index]);
        backTracking(index, target - candidates[index], temp, candidates);
        temp.pop_back();
        // 不選當前的num
        backTracking(index + 1, target, temp, candidates);
    }
};

int main() {

    return 0;
}
