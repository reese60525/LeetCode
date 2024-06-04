/*
 * 題目: https://leetcode.com/problems/first-missing-positive/description/
 *
 * 題目解釋:
 *
 * 思路:
 *
 * 解法:
 *
 */
#include <iostream>
#include <unordered_map>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int firstMissingPositive(std::vector<int> &nums) {
        std::unordered_map<int, bool> table;

        for (int i : nums) {
            if (i > 0) {
                table[i] = true;
            }
        }

        int res = 1;
        while (table[res]) {
            ++res;
        }

        return res;
    }
};

int main() {

    return 0;
}