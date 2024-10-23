/*
 * 題目：https://leetcode.com/problems/longest-palindromic-substring/description/
 *
 * 題目解釋：
 * 給一個string，只包含數字和英文字母，回傳最大長度的 palindromic substring (回文子字串)
 * 回文是指一個string從前面讀和從後面讀一模一樣，e.g. abba。
 * 思路：
 * 把string中每個字元當作中心點往兩側尋找迴文，其中又分為奇數迴文和偶數迴文，遍歷string來找到
 * 最長的迴文。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::string longestPalindrome(std::string s) {
        std::pair<int, int> res_index = {0, 0}; // 最長迴文子字串的起始index和終點index

        for (int i = 0; i < s.length(); ++i) {
            std::pair<int, int> sub_odd = findPalindromic(i, i, s);      // 奇數回文
            std::pair<int, int> sub_even = findPalindromic(i, i + 1, s); // 偶數回文

            // 若sub_odd比res_index長，則更新res_index
            if ((res_index.second - res_index.first) < (sub_odd.second - sub_odd.first)) {
                res_index = sub_odd;
            }
            // 若sub_even比res_index長，則更新res_index
            if ((res_index.second - res_index.first) < (sub_even.second - sub_even.first)) {
                res_index = sub_even;
            }
        }

        // 將res_index轉成string
        std::string res = "";
        for (int i = res_index.first; i <= res_index.second; ++i) {
            res += s[i];
        }

        return res;
    }

  private:
    //  尋找以left和right為中心點的回文
    std::pair<int, int> findPalindromic(int left, int right, std::string &s) {
        int len = s.length();

        // 判斷邊界條件和兩側字元是否相等
        while (left > -1 && right < len && s[left] == s[right]) {
            --left;
            ++right;
        }

        // 因為while loop最後會多執行一次，所以left和right要各往中心退一格
        return {left + 1, right - 1};
    }
};

int main() {

    return 0;
}