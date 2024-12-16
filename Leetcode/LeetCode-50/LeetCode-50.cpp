/*
 * 題目：
 *
 * 題目解釋：
 *
 * 思路：
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
    double myPow(double x, long long n) {
        // 若 n < 0，將 x = 1/x，n 轉正
        if (n < 0) {
            x = 1 / x;
            n = -n;
        }

        // 遞迴計算次方
        double res = 1;
        while (n > 0) {
            // 判斷 n 最後一個 bit 是 1 還是 0
            if (n & 1) {
                res *= x;
            }
            n >>= 1; // n 往右移一個 bit
            x *= x;
        }

        return res;
    }
};

int main() {

    return 0;
}