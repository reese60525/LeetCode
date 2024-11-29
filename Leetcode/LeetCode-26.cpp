/*
 * 題目： https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
 *
 * 題目解釋：
 * 給一組升序 integer array，將所有不重複的整數存到該 array 的前端，並回傳不重複整數的數量。
 * e.g. {1, 1, 2, 3, 4, 4, 5} => {1, 2, 3, 4, 5, _, _}，_為不在乎其值，return 5。
 *
 * 思路：
 * 設 idx 表示當前不重複的整數數量，從 index = 1 開始遍歷 array，利用升序 array 的特性，
 * 如果 array[i] != array[i - 1]，表示 array[i] 是新遇到的不重複整數，將該數存到 array[idx]
 * ，並將 idx + 1。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int removeDuplicates(std::vector<int> &nums) {
        int idx = 1;

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1]) {
                nums[idx] = nums[i];
                ++idx;
            }
        }

        return idx;
    }
};

int main() {

    return 0;
}