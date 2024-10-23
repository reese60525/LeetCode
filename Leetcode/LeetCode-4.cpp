/*
 * 題目：https://leetcode.com/problems/median-of-two-sorted-arrays/description/
 *
 * 題目解釋：
 * 給兩個已經排序的整數陣列，找出兩陣列合併後的中位數。
 *
 * 思路：
 * 參考該網站：https://leetcode.wang/leetCode-4-Median-of-Two-Sorted-Arrays.html，
 * 該網站中的第四種解法說得很詳細。
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

        // 讓較小的array始終為 nums1
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        // nums1_left 為 nums1 左邊部分的起始index， nums1_right 為 nums1 左邊部分的終點index
        // all_left_size 為 nums1 左邊部分和 nums2 左邊部分合併後的長度
        int nums1_left = 0, nums1_right = n1, all_left_size = (n1 + n2 + 1) >> 1;

        while (nums1_left <= nums1_right) {
            int mid1 = (nums1_left + nums1_right) >> 1; // nums1 的分割點
            int mid2 = all_left_size - mid1;            // nums2 的分割點
            int l1 = INT_MIN, l2 = INT_MIN;             // l1 和 l2 各為 nums1 和 nums2 左邊部分的最大值
            int r1 = INT_MAX, r2 = INT_MAX;             // r1 和 r2 各為 nums1 和 nums2 右邊部分的最小值

            // 設定l1, l2, r1, r2的值，if中的判斷均為邊界條件的判斷，避免index超出vector範圍
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

            // 如果l1 > r2，表示 nums1 左邊部分太大，需要將 nums1 左邊部分縮小，反之則將 nums1 左邊部分放大
            if (l1 > r2) {
                nums1_right = mid1 - 1;
            }
            else if (l2 > r1) {
                nums1_left = mid1 + 1;
            }
            else { // 如果l1 <= r2 && l2 <= r1，
                   // 表示 nums1 左邊部分和 nums2 左邊部分合併後的長度剛好為 all_left_size，表示找到答案
                if (n % 2 == 1) {
                    return static_cast<double>(std::max(l1, l2));
                }
                else {
                    return static_cast<double>(std::max(l1, l2) + std::min(r1, r2)) / 2;
                }
            }
        }

        return -1;
    }
};

int main() {

    return 0;
}