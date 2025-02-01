/*
 * 題目： https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/description/
 *
 * 題目解釋：
 * 給一個整數array和整數k，找出所有長度為k的nums的subarray的power，並將其放入res中。
 * consecutive(連續)的定義:一個array為遞增排序，且每個element彼此相差1。
 * power的定義:如果array是consecutive，則power = 該array的最大值，反之power = -1。
 * e.g. {1, 2, 3}的power = 3，{1, 3, 5}的power = -1。
 * array = {1, 2, 3, 5, 6, 7}，k = 3，
 * subarray = {{1, 2, 3}, {2, 3, 5}, {3, 5, 6}, {5, 6, 7}}，則res = {3, -1, -1, 7}。
 *
 * 思路：
 * 用sliding window algorithm。
 * 設兩個pointer l 和 r，l為當前subarray的起始index，r為結尾index，l = 0,r = 1。
 * 用r遍歷整個array，如果array[r]和array[r-1]連續，r往後一個element繼續判斷，
 * 直到該subarray的長度為k，則將該subarray的最大值放入res中。
 * 如果array[r]和array[r-1]不是連續，表示包含這兩個數字的subarray的power = -1。
 * 以題目解釋的array為例，l = 1、r = 3時，array[r-1] = 3和array[r] = 5為不連續，
 * 因此subarray{{2, 3, 5}, {3, 5, 6}}的power都是-1，所以會有(r - l)個subarray的power = -1。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<int> resultsArray(std::vector<int> &nums, int k) {
        if (k == 1) { // k = 1時，nums本身就是答案
            return nums;
        }

        int l = 0, r = 1, n = nums.size();           // l為當前subarray的起始index，r為結尾index
        std::vector<int> res(n - k + 1);             // 初始化res的大小
        while (r < n) {                              // 以r遍歷整個nums
            bool check = nums[r - 1] + 1 == nums[r]; // 確認是否為連續

            if (check) {
                if (r - l == k - 1) { // 連續且當前subarray的長度為k
                    res[l] = nums[r];
                    ++l; // 每放入一個subarray的power，l就往後移動一格
                }
            }
            else {
                while (l < n - k + 1 && l < r) { // l < n-k+1 是為了避免subarray超出nums的範圍
                    res[l] = -1;
                    ++l; // 每放入一個subarray的power，l就往後移動一格
                }
            }
            ++r;
        }

        return res;
    }
};

int main() {

    return 0;
}