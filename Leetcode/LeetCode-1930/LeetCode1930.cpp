/*
 *  Author      : Reese
 *  Created On  : 2025-01-04 15:48
 *  Description : https://leetcode.com/problems/unique-length-3-palindromic-subsequences/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int countPalindromicSubsequence(std::string s) {
        int n = s.size();

        // prefix[i] 和 suffix[i] 分別紀錄 [0, i] 和 [i, n-1] 之間有幾種不同字元
        std::vector<int> prefix(n), suffix(n);
        for (int i = 0; i < n; ++i) {
            prefix[i] = ((i > 0) ? prefix[i - 1] : 0) | (1 << (s[i] - 'a'));
            suffix[n - i - 1] = ((i > 0) ? suffix[n - i] : 0) | (1 << (s[n - i - 1] - 'a'));
        }

        // 遍歷 s 中每個字元，計算以該字元為中心點時左右兩邊共同擁有的字元數量，並將這些不重複的共同字元累加
        int cnt[26];
        for (int i = 1; i < n - 1; ++i) {
            cnt[s[i] - 'a'] |= (prefix[i - 1] & suffix[i + 1]);
        }

        // 計算 cnt[i] 中 bit = 1 數量
        int res = 0;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                res += cnt[i] & 1;
                cnt[i] >>= 1;
            }
        }

        return res;
    }
};

int main() {

    return 0;
}