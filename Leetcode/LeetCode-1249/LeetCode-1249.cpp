/*
 *  Author      : Reese
 *  Created On  : 2025-01-15 19:28
 *  Description : https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/description/
 */

#include <iostream>
#include <stack>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::string minRemoveToMakeValid(std::string &s) {
        // 紀錄要刪除的左括號所在位置 index
        std::stack<int> left;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                left.push(i);
            }
            else if (s[i] == ')') {
                // 當前右括號沒有可以匹配的左括號，將其刪除
                if (left.empty()) {
                    s.erase(s.begin() + i);
                    // 刪除當前位置的字元後，會將後面沒遍歷到的字元補過來
                    // 因此需要將 i - 1，下一輪再 check 一次
                    --i;
                }
                else {
                    left.pop();
                }
            }
        }

        // 刪除多餘的左括號
        while (!left.empty()) {
            s.erase(s.begin() + left.top());
            left.pop();
        }

        return s;
    }
};

int main() {

    return 0;
}