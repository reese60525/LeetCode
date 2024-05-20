/*
 * 題目: https://leetcode.com/problems/sum-of-all-subset-xor-totals/description/
 *
 * 題目解釋:
 * 給一個整數array，求把其所有subset做xor運算的總和。
 * EX:array = {5, 1, 6}，可得subset = {}, {5}, {1}, {6}, {5, 1}, {5, 6}, {1, 6}, {5, 1, 6}
 * 把所有subset做xor運算後的總合為28。
 *
 * 思路:
 * backtracking algorithm解題。
 *
 * 解法:
 * 如上所說，簡單的backtracking。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int subsetXORSum(std::vector<int> &nums) {
        int res = 0;

        backTracking(0, res, 0, nums);
        return res;
    }

  private:
    void backTracking(int cur, int &sum, int index, const std::vector<int> &nums) {
        if (index == nums.size()) {
            sum += cur;
            return;
        }

        backTracking(cur ^ nums[index], sum, index + 1, nums);
        backTracking(cur, sum, index + 1, nums);
    }
};

int main() { return 0; }