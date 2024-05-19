/*
 * 題目: https://leetcode.com/problems/search-in-rotated-sorted-array/description/
 * 題目解釋:
 * 思路:
 * 解法:
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int search(std::vector<int> &nums, int target) {
        int n = nums.size(), l = 0, r = nums.size() - 1;

        while (l < r) { // binary search 找最小值，也就是原本array的開頭
            int mid = l + (r - l) / 2;

            if (nums[mid] > nums[r]) {
                l = mid + 1;
            }
            else {
                r = mid;
            }
        }

        int pivot_index = l;
        l = 0, r = n - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            int real_mid = (mid + pivot_index) % n;

            if (nums[real_mid] == target) {
                return real_mid;
            }
            else if (nums[real_mid] > target) {
                r = real_mid - 1;
            }
            else {
                l = real_mid + 1;
            }
        }
        return -1;
    }
};

int main() {

    return 0;
}