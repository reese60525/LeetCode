/*
 * 題目： https://leetcode.com/problems/search-insert-position/description/
 *
 * 題目解釋：
 * 給一個 ascending order integer array 和 integer target，求該 target 在 array
 * 中的 index，若 target 不存在於 array 中，則 return target 在此 array 應該所在的
 * index。
 * e.g.
 * array = {1, 2, 3}，target = 4，return index = 4 because if 4 in array，
 * array will be {1, 2, 3, 4}，and index of 4 is 4。
 * array = {1, 2, 4, 5}，target = 3，return index = 2。
 * array = {1, 3, 4, 5, 6}，target = 5，return index = 3。
 *
 * 思路：
 * binary search 去搜索，若找到直接 return index，找不到則 binary search 結束後，l 的
 * 位置就是 target 應該在的位置。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int searchInsert(std::vector<int> &nums, int target) {
        int l = 0, r = nums.size() - 1;
        // 要用小於等於，這樣 l = r 時，mid = l = r
        // 因此不管 nums[mid] 是大於或小於 target，l 都會是 target 應該在的位置
        while (l <= r) {
            int mid = l + (r - l) / 2;

            if (nums[mid] == target) {
                return mid;
            }
            if (nums[mid] < target) {
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }

        return l;
    }
};

int main() {

    return 0;
}