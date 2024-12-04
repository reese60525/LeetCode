/*
 * 題目： https://leetcode.com/problems/first-missing-positive/description/
 *
 * 題目解釋：
 * 給一個整數 array，element 可重複，找出"不存在"於該 array 中的最小正整數。
 * 題目要求 O(n) 時間複雜度 和 O(1) 空間複雜度。
 *
 * 思路：
 * 前提：可以先去做做看LeetCode p268，靈感從那題得到的。
 * 首先第一直覺是建立 hash map 來對 array 中每個 element 做記號，但是這樣的空間複雜度是 O(n)，
 * 所以我們要利用 array 本身的空間才有可能達成 O(1) 的空間複雜度。
 * 題目要找未出現過的最小正整數，已知 array_size = n，array 就算從 1 開始嚴格遞增最多也只到 n，
 * 未出現的最小正整數最大會是 n + 1，最小是 1，由此確認了 lower bound = 1 和 upper bound = n + 1，
 * 因此我們所要關注的重點就是 1 ~ n + 1 的正整數，array 本身的空間正好能塞下 1 ~ n 的正整數資訊。
 * 將 array[0] 對應到 1、array[1] 對應到 2 ... array[n - 1] 對應到 n 為概念，遍歷 array，
 * 當 array[i] != i + 1 時，試著將 array[i] 放到對應的位置上，也就是 index = array[i] - 1 的位置上，
 * 若 array[i] = i + 1 或是 array[i] 對應的 index 的位置上已經有正確的值，則跳過。
 * 將整個 array 遍歷完後，除了缺少的正整數以外其他的 element 都會是 array[i] = i + 1 的型態，所以再遍歷
 * 一次 array，找出第一個 array[i] != i + 1，則 i + 1 即為未出現的最小正整數，如果整個 array 都符合
 * array[i] = i + 1，則回傳 n + 1。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int firstMissingPositive(std::vector<int> &nums) {
        for (int i = 0; i < nums.size(); ++i) {
            // 只關注 1 ~ n 的正整數，其他的不用處理
            while (nums[i] > 0 && nums[i] <= nums.size()) {
                // 當 array[i] 已經在對應的位置上或是 array[i] 對應的 index 的位置上已經有正確的值，則跳過
                if (nums[i] == i + 1 || nums[i] == nums[nums[i] - 1]) {
                    break;
                }
                /// 將 array[i] 放到對應的位置上
                std::swap(nums[i], nums[nums[i] - 1]);
            }
        }

        // 找出第一個 array[i] != i + 1，i + 1 即為未出現的最小正整數
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }

        // 如果整個 array 都符合 array[i] = i + 1，則回傳 n + 1
        return nums.size() + 1;
    }
};

int main() {

    return 0;
}