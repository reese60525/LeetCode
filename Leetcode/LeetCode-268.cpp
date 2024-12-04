/*
 * 題目： https://leetcode.com/problems/missing-number/description/
 *
 * 題目解釋：
 * 給一個大小為 n 且 element 由相異的 [0, n] 組成的整數 array，找出該 array 中在 [0 , n]
 * 範圍所缺少的整數。
 * 題目要求以 O(n) 時間複雜度 和 O(1) 空間複雜度來完成。
 * e.g.
 * nums = {9, 6, 4, 2, 3, 5, 7, 0, 1}，在 [0, 9] 範圍中缺少了 8。
 *
 * 思路：
 * 前提：此題為 LeetCode p41 的前導題，兩者十分類似。
 * 由於題目要求空間複雜度必須是 O(1)，因此要利用 array 本身的空間來儲存 element 的資訊。
 * 由於 [0, n] 範圍的整數可以將 [0, n - 1] 的整數映射到 array 中 [0, n - 1] 的 index，
 * 所以能將 0 映射到 array[0]、1 映射到 array[1]、...、n-1 映射到 array[n - 1]。
 * 首先遍歷 array，當 array[i] != i 時，將 array[i] 擺放到正確的 index 上，也就是
 * index = array[i] - 1，並把 array[array[i - 1 ]] 的值給 array[i]，直到 array[i] = i，
 * 遍歷完 array 後會發現除了缺少的正整數以外其他所有 element 都擺放到正確的位置上，因此只要再
 * 遍歷一次 array 找出第一個 array[i] != i，i 就是缺少的正整數，若所有 element 都是在正確
 * 位置上，則缺少的正整數為 n。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int missingNumber(std::vector<int> &nums) {
        for (int i = 0; i < nums.size(); ++i) {
            // 當 nums[i] 不是在正確的位置上時，將 nums[i] 擺放到正確的位置上
            while (nums[i] < nums.size() && nums[i] != i) {
                std::swap(nums[i], nums[nums[i]]);
            }
        }

        // 找出缺少的正整數
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != i) {
                return i;
            }
        }

        // 若所有 element 都在正確的位置上，則缺少的正整數為 n
        return nums.size();
    }
};

int main() {

    return 0;
}