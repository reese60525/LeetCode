/*
 * 題目: https://leetcode.com/problems/height-checker/description/
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
    int heightChecker(std::vector<int> &heights) {
        int res = 0, table[101];
        memset(table, 0, sizeof(table));

        for (const int &h : heights) {
            ++table[h];
        }

        int index = 0;
        for (int i = 0; i < 101; ++i) {
            while (table[i]--) {
                if (heights[index] != i) {
                    ++res;
                }
                ++index;
            }
        }

        return res;
    }
};

int main() {

    return 0;
}