/*
 * 題目：https://leetcode.com/problems/reverse-integer/description/
 *
 * 題目解釋：
 * 將整數反轉，如果反轉後超出int範圍，則回傳0。整個code不可用到超過32bit以上的變數。
 * e.g. 123 -> 321，-123 -> -321，120 -> 21
 *
 * 思路：
 * 紀錄input number的正負，若為負數則先轉正，因為INT_MIN轉換成正數會overflow，所以要
 * 先判斷x是否等於INT_MIN。在res添加新的digit之前先判斷當前res有沒有超出int範圍，透過
 * (res * 10 + digit) <= INT_MAX，可得 res <= (INT_MAX - digit) / 10 此判斷條件。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int reverse(int x) {
        if (x == INT_MIN) { // 若x為INT_MIN，其-x和反轉x都會超出int範圍，故直接回傳0
            return 0;
        }

        bool sign = 0; // 用於紀錄x的正負
        int res = 0;

        if (x < 0) {  // 若x為負數則先轉正
            sign = 1; // sign = 1 表示x為負數
            x *= -1;
        }

        while (x > 0) { // 反轉x
            int digit = x % 10;
            x /= 10;

            if (res > (INT_MAX - digit) / 10) {
                return 0;
            }
            res = res * 10 + digit;
        }

        return sign ? -res : res; // 若x為負數則回傳-res，否則回傳res
    }
};

int main() {

    return 0;
}