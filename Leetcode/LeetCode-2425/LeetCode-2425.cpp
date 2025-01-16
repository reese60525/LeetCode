/*
 *  Author      : Reese
 *  Created On  : 2025-01-16 14:18
 *  Description : https://leetcode.com/problems/bitwise-xor-of-all-pairings/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int xorAllNums(std::vector<int> &nums1, std::vector<int> &nums2) {
        int res = 0;

        if (nums2.size() & 1) {
            for (const int &n : nums1) {
                res ^= n;
            }
        }

        if (nums1.size() & 1) {
            for (const int &n : nums2) {
                res ^= n;
            }
        }

        return res;
    }
};

int main() {

    return 0;
}