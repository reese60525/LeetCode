/*
 * 題目： https://leetcode.com/problems/combination-sum/description/
 *
 * 題目解釋：
 * 給一組整數 array 和 整數 target，array 中每個 element 都可以選用 0 ~ 無限次，找出所有
 * 組合使其總和等於 target。
 * e.g.
 * array = {2, 3, 6, 7}，target = 7，所有組合 = {{2, 2, 3}, {7}}
 *
 * 思路：
 * 使用 backtracking algorithm。
 * 對於每個 num 都有選和不選兩種選擇，若不選就把當前 array_index + 1，這樣不會有重複的組合問題。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    void backtrack(std::vector<std::vector<int>> &res, std::vector<int> &temp, std::vector<int> &candidates, int target,
                   int index) {
        //  target < 0 則該組合 invalid
        if (target < 0) {
            return;
        }
        // 找到一組解
        if (target == 0) {
            res.push_back(temp);
            return;
        }

        // 遞迴找所有組合
        for (; index < candidates.size(); ++index) {
            temp.push_back(candidates[index]);
            backtrack(res, temp, candidates, target - candidates[index], index);
            temp.pop_back();
        }
    }

    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target) {
        // 先排序，方便後面剪枝
        std::sort(candidates.begin(), candidates.end());

        std::vector<int> temp;
        std::vector<std::vector<int>> res;
        // backtracking 找所有組合
        backtrack(res, temp, candidates, target, 0);

        return res;
    }
};

int main() {

    return 0;
}