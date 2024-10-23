/*
 * 題目：https://leetcode.com/problems/median-of-two-sorted-arrays/description/
 *
 * 題目解釋：
 * 給兩個已經排序的整數陣列，找出兩陣列合併後的中位數。
 *
 * 思路：
 * 參考該網站：https://leetcode.wang/leetCode-4-Median-of-Two-Sorted-Arrays.html
 */
#include <climits>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
        int n1 = nums1.size(), n2 = nums2.size(), n = n1 + n2;

        // 讓較小的array始終為nums1
        if (nums1.size() > nums2.size()) {
            findMedianSortedArrays(nums2, nums1);
        }

        // nums1_left為nums1左邊部分的起始index，nums1_right為nums1左邊部分的終點index
        // all_left_size為nums1左邊部分和nums2左邊部分合併後的長度
        int nums1_left = 0, nums1_right = n1, all_left_size = (n1 + n2 + 1) >> 1;

        while (nums1_left <= nums1_right) {
            int mid1 = (nums1_left + nums1_right) >> 1; // nums1的分割點
            int mid2 = all_left_size - mid1;            // nums2的分割點
            int l1 = INT_MIN, l2 = INT_MIN;             // nums1和nums2左邊部分的最大值
            int r1 = INT_MAX, r2 = INT_MAX;             // nums1和nums2右邊部分的最小值

            if (mid1 > 0) {
                l1 = nums1[mid1 - 1];
            }
            if (mid2 > 0) {
                l2 = nums2[mid2 - 1];
            }
            if (mid1 < n1) {
                r1 = nums1[mid1];
            }
            if (mid2 < n2) {
                r2 = nums2[mid2];
            }
        }
    }
};

int main() {

    return 0;
}