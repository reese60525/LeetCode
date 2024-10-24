/*
 * 題目：https://leetcode.com/problems/integer-to-roman/description/
 *
 * 題目解釋：
 * 給一個正整數，轉成羅馬數字。
 *
 * 思路：
 * 建立一組roman_table，從roman_table中最大值開始做轉換。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::string intToRoman(int num) {
        std::pair<int, std::string> roman[] = {
            {1,    "I" },
            {4,    "IV"},
            {5,    "V" },
            {9,    "IX"},
            {10,   "X" },
            {40,   "XL"},
            {50,   "L" },
            {90,   "XC"},
            {100,  "C" },
            {400,  "CD"},
            {500,  "D" },
            {900,  "CM"},
            {1000, "M" }
        };

        std::string res = "";
        int index = 12; // roman的index
        while (num > 0) {
            int n = num / roman[index].first; // 羅馬數字要n次

            while (n--) { // res加上n次羅馬數字
                res += roman[index].second;
            }

            num %= roman[index].first; // num取餘數
            --index;                   // 換下一個羅馬數字
        }

        return res;
    }
};

int main() {

    return 0;
}