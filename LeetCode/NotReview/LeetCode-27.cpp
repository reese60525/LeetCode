/*
 * 題目： https://leetcode.com/problems/remove-element/description/
 *
 * 題目解釋：
 * 給一個 integer array 和整數 val，將 array 中所有不是 val 的 element 移到 array
 * 的前面，並回傳排除 val 後 array 的長度。
 * e.g. _表示不在乎數字是多少
 * array = {1}、val = 1，new array = {_}，return 0。
 * array = {1, 1}、val = 1，new array = {_, _}，return 0。
 * array = {1, 2, 1}、val = 1，new array = {2, _, _}，return 1。
 * array = {3, 2, 2, 3}、val = 3，new array = {2, 2, _, _}，return 2。
 *
 * 思路：
 * 用 two pointer: l = 0、r = array size -1，如果 array[l] 是 val，則以 array[r]
 * 向左遍歷，將 array[r] 的 value 放到 array[l]，直到 array[r] 不是 val。每當 r 往左
 * 移一格，代表遇到一次 val，因此 array 中 val 的數量 = r 的變化量 = (array_size - 1) - r，
 * 非 val 的整數數量 = array_size - ((array_size - 1) - r) = r + 1。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int removeElement(std::vector<int> &nums, int val) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) { // 兩個 while 都必須用 l <= r
            while (l <= r && nums[l] == val) {
                nums[l] = nums[r];
                --r;
            }
            ++l;
        }

        return r + 1;
    }
};

int main() {

    return 0;
}