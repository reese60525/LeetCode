/*
 * 題目：https://leetcode.com/problems/palindrome-number/description/
 *
 * 題目解釋：
 * 給一個整數，以string的形式來看該整數是不是一個迴文。
 * e.g. 121 => true， -121 => false，123 => false， 1230 => false。
 *
 * 思路：
 * 方法1.首先負數一定不是迴文，以input number的bit數來進行奇數迴文或是偶數迴文的判斷。
 * 方法2.首先負數和不為零而個位數是0(反轉後會有前導0)的一定不是迴文，然後將數字拆成兩半，
 * 將前半段與反轉後的後半段比較，若相同則為迴文。
 * e.g. 1221拆成12和21的反轉(也就是12)，判斷為迴文。 12321拆成12和321的反轉(也就是123)，
 * 此為奇數迴文，12 = (123 / 10)。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 方法1
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

// // 方法2
// class Solution {
// public:
//     bool isPalindrome(int x) {
//         // 負數或不為零而個位數是0的一定不是迴文
//         if (x < 0 || (x != 0 && x % 10 == 0)) {
//             return false;
//         }

//         int reversed = 0;
//         while (x > reversed) {
//             reversed = reversed * 10 + x % 10;
//             x /= 10;
//         }
//
//         // 偶數迴文和奇數迴文的判斷
//         return (x == reversed) || (x == reversed / 10);
//     }
// };

int main() {

    return 0;
}