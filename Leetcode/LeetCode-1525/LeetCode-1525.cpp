/*
 *  Author      : Reese
 *  Created On  : 2024-12-26 21:00
 *  Description : https://leetcode.com/problems/number-of-good-ways-to-split-a-string/description/
 */

#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int numSplits(std::string s) {
        int left_freq[26] = {0}, right_freq[26] = {0};
        int left_cnt = 0, right_cnt = 0;

        // 計算 s 中所有字元出現頻率
        for (auto &c : s) {
            if (++right_freq[c - 'a'] == 1) {
                ++right_cnt;
            }
        }

        // 從頭開始分割，並更新當前左右兩個 substring 的不同字元數量
        int res = 0;
        for (auto &c : s) {
            int cur = c - 'a';

            if (++left_freq[cur] == 1) {
                ++left_cnt;
            }
            if (--right_freq[cur] == 0) {
                --right_cnt;
            }

            res += left_cnt == right_cnt;
        }

        return res;
    }
};

int main() {

    return 0;
}