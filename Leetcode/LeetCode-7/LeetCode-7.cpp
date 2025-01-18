/*
 *  Author      : Reese
 *  Created On  : 2025-01-18 17:23
 *  Description : https://leetcode.com/problems/reverse-integer/description/
 */

#include <climits>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int reverse(int x) {
        // 紀錄正負號並將 x 一律轉為負數，因為 INT_MIN 轉正數會 overflow
        bool sign = true;
        if (x > 0) {
            sign = false;
            x *= -1;
        }

        int res = 0;
        while (x != 0) {
            // 判斷 res 是否會 overflow
            if (res < (INT_MIN - x % 10) / 10) {
                return 0;
            }
            res = res * 10 + x % 10;
            x /= 10;
        }

        // 根據輸入的正負號來輸出答案
        return (sign == 1) ? res : -res;
    }
};

int main() {

    return 0;
}