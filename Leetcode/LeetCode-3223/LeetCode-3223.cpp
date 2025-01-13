/*
 *  Author      : Reese
 *  Created On  : 2025-01-13 10:34
 *  Description : https://leetcode.com/problems/minimum-length-of-string-after-operations/description/
 */

#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int minimumLength(std::string &s) {
        // 計算每個字元出現次數
        int cnt[26] {0};
        for (const char &c : s) {
            ++cnt[c - 'a'];
        }

        // 若出現奇數次，則最多可以刪減到剩下 1 個字元，偶數則是 2 個字元
        int res = 0;
        for (const int &n : cnt) {
            // 若該字元出現次數為 0，則跳過
            if (n == 0) {
                continue;
            }
            res += (n & 1) ? 1 : 2;
        }

        return res;
    }
};

int main() {

    return 0;
}