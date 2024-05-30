/*
 * 題目: https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/description/
 *
 * 題目解釋:
 *
 * 思路:
 * 若a = b，則a^b = 0，因此從index_i到index_k的這整個substring中，j從i+1到k都能使a ^ b = 0，
 * 因此可以用一個雙迴圈，begin為i，end為k，遍歷所有substring找arr[i]^arr[i+1]^...^arr[k] = 0，
 * 若找到則該substring有k - i種組合符合題目要求。
 *
 * 解法:
 *
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int countTriplets(std::vector<int> &arr) {
        int res = 0;
        for (int i = 0; i < arr.size() - 1; ++i) {
            int cur = arr[i];
            for (int k = i + 1; k < arr.size(); ++k) {
                cur ^= arr[k];
                if (cur == 0) {
                    res += k - i;
                }
            }
        }

        return res;
    }
};

int main() {

    return 0;
}