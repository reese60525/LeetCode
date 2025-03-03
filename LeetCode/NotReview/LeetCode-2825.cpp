/*
 * 題目： https://leetcode.com/problems/make-string-a-subsequence-using-cyclic-increments/description/
 *
 * 題目解釋：
 * 給兩個由小寫英文字母組成的 string s1 and s2，對於 s1[i] 進行最多一次 +1 的操作，
 * 使 s1[i] 變成下個字母，如果 s[i] = 'z' 則變成 'a'。判斷 s1 經過這樣的操作後，s2
 * 是否能成為 s1 的 subsequence。
 * subsequence：刪除字串 s 的某些(可以不刪) element 後所形成的字串。
 *
 * 思路：
 * 遍歷 s1，如果 s1[i] = s2[j] 或是 s1[i] 的下個字母等於 s2[j]，則 s2往後一個element，
 * 如果都不是則繼續找 s1 中能符合條件的字母。當 s2 先遍歷完，則表示 s2 是 s1 的 subsequence。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    bool canMakeSubsequence(std::string str1, std::string str2) {
        int i = 0, j = 0;

        for (; i < str1.size(); ++i) {
            // 如果 s1 的字母經過操作(或沒有操作)等於 s2 的字母，s2 index 往後
            if (str1[i] == str2[j] || str1[i] + 1 == str2[j] || str1[i] == 'z' && str2[j] == 'a') {
                ++j;
            }

            // s2 全部的字母都能在 s1 中依序找到
            if (j == str2.size()) {
                return true;
            }
        }

        return false;
    }
};

int main() {

    return 0;
}