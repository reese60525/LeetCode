/*
 * 題目: https://leetcode.com/problems/subarray-sums-divisible-by-k/description/
 *
 * 題目解釋:
 *
 * 思路:
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
    int subarraysDivByK(std::vector<int> &nums, int k) {
        int sum = 0, res = 0;
        int table[10001];

        memset(table, 0, sizeof(table));

        for (const int &n : nums) {
            sum += n;

            int mod = sum % k;
            if (mod < 0) {
                mod += k;
            }

            if (table[mod] > 0) {
                res += table[mod];
            }
            ++table[mod];
        }

        return res + table[0];
    }
};

int main() {

    return 0;
}