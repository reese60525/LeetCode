/*
 * 題目：https://leetcode.com/problems/roman-to-integer/description/
 *
 * 題目解釋：
 * 給一組羅馬數字，轉成阿拉伯數字。
 *
 * 思路：
 * 創建roman_table用於將羅馬數字轉成阿拉伯數字。遍歷string，如果當前的s[i]其阿拉伯數值小於s[i+1]，
 * 則res要減掉s[i]的阿拉伯數值，反之則為相加。
 */
#include <iostream>
#include <unordered_map>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int romanToInt(std::string s) {
        // 將roman宣告為靜態成員，這樣每次使用時就不會就不會重新創建和銷毀了
        // 這樣做能提升執行效率和降低空間使用，vector和array都能這樣做
        // 當變數同時為static和const時，[]operator無法使用，要改用at()
        static const std::unordered_map<char, int> roman = {
            {'I', 1   },
            {'V', 5   },
            {'X', 10  },
            {'L', 50  },
            {'C', 100 },
            {'D', 500 },
            {'M', 1000}
        };

        int res = 0, n = s.length();
        for (int i = 0; i < n - 1; ++i) { // 邊界條件為i < s.length() - 1，這樣就不用怕i+1超出邊界
            res += roman.at(s[i]) < roman.at(s[i + 1]) ? -roman.at(s[i]) : roman.at(s[i]);
        }

        return res + roman.at(s[n - 1]); // 最後一個羅馬數字要記得加上去
    }
};

int main() {

    return 0;
}