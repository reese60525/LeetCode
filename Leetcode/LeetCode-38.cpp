/*
 * 題目： https://leetcode.com/problems/count-and-say/description/
 *
 * 題目解釋：
 *
 * 思路：
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
    std::string countAndSay(int n) {
        std::string cur {"1"};

        for (int i = 1; i < n; ++i) {
            int count = 1;
            std::string next;

            for (int j = 1; j < cur.length(); ++j) {
                if (cur[j] != cur[j - 1]) {
                    next += std::to_string(count) + cur[j - 1];
                    count = 0;
                }
                ++count;
            }
            next += std::to_string(count) + cur.back();
            cur = std::move(next);
        }

        return cur;
    }
};

int main() {

    return 0;
}