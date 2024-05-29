/*
 * 題目:
 * https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/description
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
    int specialArray(std::vector<int> &nums) {
        int table[1001];
        memset(table, 0, sizeof(table));

        for (int &i : nums) {
            ++table[i];
        }

        for (int i = 999; i > -1; --i) {
            table[i] += table[i + 1];
            if (table[i] == i)
                return i;
        }

        return -1;
    }
};

int main() {

    return 0;
}