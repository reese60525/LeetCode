/*
 *  Author      : Reese
 *  Created On  : 2025-01-10 08:29
 *  Description : https://leetcode.com/problems/word-subsets/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<std::string> wordSubsets(std::vector<std::string> &words1, std::vector<std::string> &words2) {
        // 計算 words2 中每個字串的字母出現次數，對每個字母取出現次數最多的
        int occurrence[26] {0};
        for (const std::string &word : words2) {
            int temp[26] {0};
            for (const char &c : word) {
                int k = c - 'a';
                ++temp[k];
                // 由於每個字串長度不超過 10，因此在這裡直接比較就好
                // 如果字串最長能遠超 26，建議 temp 算完後再用一個 for 迴圈來遍歷比較
                occurrence[k] = std::max(occurrence[k], temp[k]);
            }
        }

        std::vector<std::string> res;
        res.reserve(words1.size());
        for (const std::string &word : words1) {
            // 計算 words1 的字母出現次數
            int cnt[26] {0};
            for (const char &c : word) {
                ++cnt[c - 'a'];
            }

            // 遍歷 occurrence 進行比較
            int i = 0;
            while (i < 26 && cnt[i] >= occurrence[i]) {
                ++i;
            }
            if (i == 26) {
                res.emplace_back(word);
            }
        }

        return res;
    }
};

int main() {

    return 0;
}