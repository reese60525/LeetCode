/*
 * 題目: https://leetcode.com/problems/score-of-a-string/description/
 *
 * 題目解釋:
 * 把字串內每個字元和其下個字元的ascii差絕對值累加，若為最後一個字元則不用(會overflow)
 *
 * 思路:
 * 就累加。
 *
 * 解法:
 * 如上。
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
    int scoreOfString(std::string s) {
        int res = 0;

        for (int i = 0; i < s.length() - 1; ++i) {
            res += std::abs(s[i] - s[i + 1]);
        }

        return res;
    }
};

int main() {

    return 0;
}