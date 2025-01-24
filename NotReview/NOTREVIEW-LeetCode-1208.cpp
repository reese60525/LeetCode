/*
 * 題目: https://leetcode.com/problems/get-equal-substrings-within-budget/description/
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
    int equalSubstring(std::string s, std::string t, int maxCost) {
        int res = 0, cur_len = 0, sum = 0, n = s.length();
        int begin = 0, end = 0;

        while (begin < n && end < n) {
            sum += std::abs(s[end] - t[end]);
            if (sum > maxCost) {
                if (end > begin)
                    sum -= std::abs(s[end] - t[end]);
                sum -= std::abs(s[begin] - t[begin]);
                res = std::max(res, cur_len);
                --cur_len;
                ++begin;
                if (end < begin) {
                    end = begin;
                }
            }
            else {
                ++cur_len;
                ++end;
            }
        }

        return std::max(res, cur_len);
    }
};

int main() {

    return 0;
}