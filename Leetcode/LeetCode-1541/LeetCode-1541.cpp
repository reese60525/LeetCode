/*
 *  Author      : Reese
 *  Created On  : 2025-01-14 13:17
 *  Description : https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/description/
 */

#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int minInsertions(std::string &s) {
        int left = 0, res = 0, n = s.size();
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                ++left;
            }
            else {
                (i < n - 1 && s[i + 1] == ')') ? ++i : ++res;
                (left == 0) ? ++res : --left;
            }
        }

        return res + left * 2;
    }
};

int main() {

    return 0;
}