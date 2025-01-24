/*
 * 題目： https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/
 *
 * 題目解釋：
 * 給一個 non-decreasing order(非嚴格升序，element 可重複) integer array 和 integer target，
 * 找出 target 在 array 中最左邊和最右邊的 index，如果 index 不存在則回傳 {-1, -1}。
 * 題目要求時間複雜度必須要為 O(log n)。
 * e.g.
 * nums = {5, 7, 7, 8, 8, 10}，target = 8，return {3, 4}
 * nums = {5, 7, 7, 8, 8, 10}，target = 6，return {-1, -1}
 *
 * 思路：
 * 做兩次 binary search，一次往左找一次往右找。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<int> searchRange(std::vector<int> &nums, int target) {
        int target_l = binarySearch(nums, target, true);
        int target_r = binarySearch(nums, target, false);

        // 如果 target 不在 nums 中，則 target_l and target_r 都必定是 -1，判斷一個就好
        if (target_l == -1) {
            return {-1, -1};
        }
        return {target_l, target_r};
    }

  private:
    // binary search 找 target 的 最左邊 或 最右邊 的 index
    int binarySearch(const std::vector<int> &nums, int target, bool is_find_left) {
        int l = 0, r = nums.size() - 1, result = -1;

        while (l <= r) {
            int mid = l + (r - l) / 2;

            if (nums[mid] == target) {
                result = mid; // 更新結果
                if (is_find_left) {
                    r = mid - 1; // 繼續向左搜索
                }
                else {
                    l = mid + 1; // 繼續向右搜索
                }
            }
            else if (nums[mid] > target) {
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }

        return result;
    }
};

int main() {

    return 0;
}