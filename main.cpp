/*
 * 題目：https://leetcode.com/problems/string-to-integer-atoi/description/
 *
 * 題目解釋：
 * 給一個string，實做類似Atoi(string s)的function，有以下規則：
 * 1.無視所有前導空白格。 e.g. "   123" => 123
 * 2.若遇到'+'，輸出的數字為正數，若遇到'-'，輸出的數字為負數。 e.g. "  -123" => -123
 * 3.所有前導0都要被無視。 e.g. "  -000032" => 32
 * 4.若得到的數字超出int範圍，正數輸出INT_MAX，負數輸出INT_MIN。 e.g. " -00999999123444" => INT_MIN
 * 5.若遇到非數字字元，則結束。 e.g. "  -000032a" => 32， "  -A32S" => 0
 * 其他範例：" - 0322" => 0 因為正負號後面必須接數字。
 *
 * 思路：
 * 依照題目要求寫一堆if判斷，code內的註解很詳細了，直接看code。
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
    int myAtoi(std::string s) {
        bool sign = false; // sign為正負號
        int i = 0;         // s的index
        long long res = 0;

        while (i < s.length() && s[i] == ' ') { // 跳過前導空白格
            ++i;
        }

        // 判斷正負號，並讓i+1來跳過符號
        if (s[i] == '+') {
            sign = false;
            ++i;
        }
        else if (s[i] == '-') {
            sign = true;
            ++i;
        }

        // 開始讀取數字
        while (i < s.length()) {
            // 判斷當前字元是否為數字
            if (s[i] - '0' < 0 || s[i] - '0' > 9) {
                break;
            }

            res = res * 10 + (s[i] - '0');

            // 判斷res是否超出int範圍
            if ((sign && -res < INT_MIN)) {
                return INT_MIN;
            }
            else if (!sign && res > INT_MAX) {
                return INT_MAX;
            }
            ++i;
        }

        return sign ? -res : res; // 根據正負號回傳res或-res
    }
};

int main() {

    return 0;
}