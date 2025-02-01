/*
 * 題目:
 * https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/description/
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
    int numSteps(std::string s) {
        int res = 0, carry = 0;

        while (s.length() > 1) {
            if ((s[s.length() - 1] - '0') + carry == 1) {
                carry = 1;
                ++res;
            }
            s.pop_back();
            ++res;
        }
        if (carry)
            ++res;

        return res;
    }
};

int main() {
    return 0;
}