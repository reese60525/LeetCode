/*
 * 題目：https://leetcode.com/problems/palindrome-number/description/
 *
 * 題目解釋：
 * 給一個整數，以string的形式來看該整數是不是一個迴文。
 * e.g. 121 => true， -121 => false，123 => false。
 *
 * 思路：
 * 首先負數一定不是迴文，以input number的bit數來進行奇數迴文或是偶數迴文的判斷。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }

        std::string s = std::to_string(x);
        int l = 0, r = s.length() - 1;

        while (l <= r) {
            if (s[l] != s[r]) {
                return false;
            }
            ++l;
            --r;
        }

        return true;
    }
};

int main() {

    return 0;
}