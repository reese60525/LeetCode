/*
 * 題目：https://leetcode.com/problems/median-of-two-sorted-arrays/description/
 *
 * 題目解釋：
 * 給兩個已經排序的整數陣列，找出兩陣列合併後的中位數。
 *
 * 思路：
 * 參考該網站：https://leetcode.wang/leetCode-4-Median-of-Two-Sorted-Arrays.html
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
        // 讓較小的array始終為nums1
        if (nums1.size() > nums2.size()) {
            findMedianSortedArrays(nums2, nums1);
        }

        int n1 = nums1.size(), n2 = nums2.size(), n = n1 + n2;
        int low = 0, high = n1, left = (n1 + n2 + 1) >> 1;

        while (low <= high) {
            int mid1 = (low + high) >> 1;
            int mid2 = n1 + n2 - mid1;

            if (mid1 > -1 && mid2 < n2 && nums1[mid1 - 1] > nums2[mid2]) {
                high = mid1 - 1;
            }
            else if (mid2 > -1 && mid1 < n1 && nums2[mid2 - 1] > nums1[mid1]) {
                low = mid1 + 1;
            }
            else {}
        }
    }
};

int main() {

    return 0;
}