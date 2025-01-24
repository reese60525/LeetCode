/*
 * 題目: https://leetcode.com/problems/reverse-string/description/
 *
 * 題目解釋:
 * 將char vector反轉，只能使用O(1)的memory
 *
 * 思路:
 * 用std::swap由左和右而內反轉。
 *
 * 解法:
 * 如上。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    void reverseString(std::vector<char> &s) {
        int n = s.size() - 1;

        for (int i = 0; i < s.size() / 2; ++i) {
            std::swap(s[i], s[n - i]);
        }
    }
};

int main() {

    return 0;
}