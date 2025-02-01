/*
 * 題目: https://leetcode.com/problems/find-common-characters/description/
 *
 * 題目解釋:
 * 給一組string，請找出在所有string都出現過的lowercase letter，若有重複的字母也要計算。
 * ex: {"bella", "label", "roller"}，'e'在每個string都出現過1次，'l'則是在每個string
 * 都出現過2次，應該要回傳{"e", "l", "l"}。
 *
 * 思路:
 * 由於要找到在"每個string"都存在的字母，可以透過計算每個string所有字母的出現次數，再把每個
 * string的字母出現次數做比較，取較小的出現次數就可得到答案。
 *
 * 解法:
 * 使用兩個array，main_table和sub_table，main_table是最終每個string所有字母出現次數的最
 * 小值，sub_table則是用來計算目前string的字母出現次數，每當sub_table計算完之後，把main_table
 * 和sub_table一一做比較，取較小值。所有string都check完後，再根據main_table來build res。
 * 在這個題目，table用array會比vector省1mb的空間。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<std::string> commonChars(std::vector<std::string> &words) {
        int main_table[26] = {0};
        memset(main_table, 0x3f, sizeof(main_table));
        std::vector<std::string> res;

        // check other words
        for (std::string w : words) {
            int sub_table[26] = {0};
            memset(sub_table, 0, sizeof(sub_table));
            // build sub_table
            for (char c : w) {
                ++sub_table[c - 'a'];
            }
            // 比較main_table 和 sub_table各自每個字母出現次數，取較小值
            for (int j = 0; j < 26; ++j) {
                main_table[j] = std::min(main_table[j], sub_table[j]);
            }
        }
        // build res
        for (int i = 0; i < 26; ++i) {
            while (main_table[i]--) {
                res.push_back(std::string(1, (i + 'a')));
            }
        }

        return res;
    }
};

int main() {

    return 0;
}