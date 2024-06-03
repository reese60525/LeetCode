/*
 * 題目: https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/description
 *
 * 題目解釋:
 * 給兩個字串s和t，全都由小寫字母組成，要在s後面加上多少字母才能讓t成為s的subsequence。
 * subsequence:在不改變每個element的order下，刪除任意個(0到n個)element所形成的子集，例如abcd刪除b
 * 變成acd，則acd為abcd的subsequence。
 * 題目範例:s = abcd，t = bcdg，要在s後方加上一個'g'變成abcdg才能使t為s的subsequence。
 *
 * 思路:
 * 遍歷s，若s當前element和t當前的element相同表示t目前這個element被s滿足，t往後一個，繼續查找，直到t
 * 全部都符合或是s已經遍歷完，這時再判斷t有幾個element被滿足，把t的size扣去被滿足的數量就是要在s後添加
 * 的字母數量。
 *
 * 解法:
 * 如上述，用two pointer紀錄當前s和t的index，如果t當前的element被滿足了則index+1。結束while迴圈後
 * 再依照t被滿足的element數量計算s要添加多少字母。
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
    int appendCharacters(std::string s, std::string t) {
        int s_len = s.length(), t_len = t.length();
        int s_index = 0, t_index = 0;

        while (s_index < s_len && t_index < t_len) {
            if (s[s_index] == t[t_index]) {
                ++t_index;
            }
            ++s_index;
        }
        return t_len - t_index;
    }
};

int main() {

    return 0;
}