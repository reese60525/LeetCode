/*
 * 題目: https://leetcode.com/problems/longest-substring-without-repeating-characters/
 *
 * 題目解釋:
 * 給一個string，找出最長不重複字母的sub string，回傳其長度。
 * e.g. string：abcabcc，所求sub string為abc，return 3。string aaa，所求sub string
 * 為a，return 1。
 * 思路:
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
    int lengthOfLongestSubstring(std::string s) {
        int cur = 0, res = 0;
        int check_table[26]; // 紀錄已出現過的字母的index

        for (int &n : check_table) {
            n = -1;
        }

        for (int i = 0; i < s.length(); i++) {
            if (check_table[s[i] - 'a'] != -1) {
                res = std::max(res, cur);
                cur = 0;
                for (int &n : check_table) {
                    n = n > check_table[s[i] - 'a'] ? n : -1;
                }
            }
            else {
                check_table[s[i] - 'a'] = i;
                cur++;
            }
        }

        return std::max(res, cur);
    }
};

int main() {

    return 0;
}