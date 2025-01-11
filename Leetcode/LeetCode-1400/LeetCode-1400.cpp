/*
 *  Author      : Reese
 *  Created On  : 2025-01-11 09:52
 *  Description : https://leetcode.com/problems/construct-k-palindrome-strings/description/
 */

#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    bool canConstruct(std::string s, int k) {
        // 計算每種字元出現次數是奇數還是偶數
        std::bitset<26> is_odd;
        for (char &c : s) {
            is_odd[c - 'a'] = !is_odd[c - 'a'];
        }

        // 計算字串中奇數個字元的數量
        int cnt = 0;
        for (int i = 0; i < 26; ++i) {
            cnt += is_odd[i] & 1;
        }

        return k >= cnt && k <= s.size();
    }
};

int main() {

    return 0;
}
