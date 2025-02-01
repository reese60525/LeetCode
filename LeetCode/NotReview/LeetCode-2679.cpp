/*
 * 題目: https://leetcode.com/problems/sum-in-a-matrix/description/
 *
 * 題目解釋:
 * 給一個整數2d vector，每次都挑出每列(row)最大的數，再把這些數之中最大的數累加，直到2d vector
 * 為空。
 *
 * 思路:
 * 對每列(row)進行排序，之後再找出每一行(col)最大的數累加。
 * 時間複雜度:O(m*nlogn)，n是col，m是row。
 *
 * 解法:
 * 如上述。
 *
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
    int matrixSum(std::vector<std::vector<int>> &nums) {
        int res = 0;

        // 對每列排序
        for (std::vector<int> &n : nums) { // 記得用reference才能使n排序
            std::sort(n.begin(), n.end());
        }
        // 找出每行最大的數
        for (int i = 0; i < nums[0].size(); ++i) {
            int n = -1;
            for (int j = 0; j < nums.size(); ++j) {
                n = std::max(n, nums[j][i]);
            }
            res += n;
        }

        return res;
    }
};

int main() {
    return 0;
}