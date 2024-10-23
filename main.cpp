/*
 * 題目：https://leetcode.com/problems/reverse-integer/description/
 *
 * 題目解釋：
 * 將整數反轉，如果反轉後超出int範圍，則回傳0。
 * e.g. 123 -> 321，-123 -> -321，120 -> 21
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
    int reverse(int x) {
        bool zero_check = true;
        int sign = 1;
        long long X = x;
        std::vector<int> reverseNum;

        if (X < 0) {
            sign = -1;
            X *= -1;
        }

        while (X > 0) {
            int n = X % 10;

            if (n != 0 || !zero_check) {
                zero_check = false;
                reverseNum.push_back(X % 10);
            }

            X /= 10;
        }

        int n = reverseNum.size();
        long long res = 0;
        for (int i = 0; i < n; ++i) {
            res += reverseNum[n - i - 1] * std::pow(10, i);
        }

        if (res > INT_MAX || res < INT_MIN) {
            return 0;
        }
        else {
            return res * sign;
        }
    }
};

int main() {

    return 0;
}