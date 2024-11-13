/*
 * 題目： https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/
 *
 * 題目解釋：
 * 在電話按鍵上每個數字都有相對應的英文字母組合，給一組數字，找出所有的英文字母組合。
 *
 * 思路：
 * 用backtracking algorithm，依序遞迴每個數字的英文字母，當完成一個組合就放入res中。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    void backTracking(std::string cur, std::string &digits, std::vector<std::string> &keypad,
                      std::vector<std::string> &res) {
        if (cur.length() == digits.length()) { // 一個組合完成，放入res
            res.push_back(cur);
            return;
        }

        int n = digits[cur.length()] - '0';              // 當前digit對應到的keypad index
        for (char ch : keypad[n]) {                      // 遍歷當前digit所對應的英文字母
            backTracking(cur + ch, digits, keypad, res); // 進入下一層(個)digit
        }
    }
    std::vector<std::string> letterCombinations(std::string digits) {
        std::vector<std::string> res;
        std::vector<std::string> keypad {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

        if (digits.empty()) {
            return {};
        }
        backTracking("", digits, keypad, res);

        return res;
    }
};

int main() {
    Solution s;
    std::string digits = {"235"};
    std::vector<std::string> res = s.letterCombinations(digits);

    for (std::string &s : res) {
        std::cout << s << std::endl;
    }

    return 0;
}