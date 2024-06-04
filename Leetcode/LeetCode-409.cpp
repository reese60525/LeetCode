/*
 * 題目: https://leetcode.com/problems/longest-palindrome/description/
 *
 * 題目解釋:
 * 給一個string s，算出利用該string做出來的回文最長能多長，每個char不可重複使用。
 *
 * 思路:
 * 用array計算每個字母出現次數，假設c出現5次，那只能使用其中4個字母，若為6則6個都能用，換言
 * 之偶數可以直接加，奇數要減1，其中aba也是合法回文，因此還要判斷如果有任意一個字母是奇數，則
 * res要額外+1。
 *
 * 解法:
 * 如上述，用 &1 來判斷奇數偶數比 % 快。
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
    int longestPalindrome(std::string s) {
        int res = 0, odd = 0; // odd計算奇數次數的字母有幾個
        int table['z' - 'A' + 1];

        memset(table, 0, sizeof(table));
        for (char c : s) {
            ++table[c - 'A'];
        }
        for (int t : table) {
            if (t & 1) { // 若為奇數則odd+1
                ++odd;
            }
            res += t;
        }

        return res - odd + (odd > 0); // odd > 0 用來判斷是否有任意字母是奇數次數
    }
};

int main() {

    return 0;
}