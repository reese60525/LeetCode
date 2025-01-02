/*
 *  Author      : Reese
 *  Created On  : 2025-01-02 09:04
 *  Description : https://leetcode.com/problems/count-vowel-strings-in-ranges/description/
 */

#include <iostream>
#include <unordered_set>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<int> vowelStrings(std::vector<std::string> &words, std::vector<std::vector<int>> &queries) {
        size_t n = words.size(), m = queries.size();
        std::unordered_set<char> letters = {'a', 'e', 'i', 'o', 'u'};

        // 計算 Prefix Sum，prefix_sum[i] 表示前 i 個字串中有多少個合法的字串
        int prefix_sum[n + 1];
        prefix_sum[0] = 0;
        for (size_t i = 1; i <= n; ++i) {
            bool is_valid = letters.contains(words[i - 1].front()) & letters.contains(words[i - 1].back());
            prefix_sum[i] = prefix_sum[i - 1] + is_valid;
        }

        // 回答查詢
        std::vector<int> res(m);
        for (size_t i = 0; i < m; ++i) {
            int a = queries[i][0], b = queries[i][1];
            res[i] = prefix_sum[b + 1] - prefix_sum[a];
        }

        return res;
    }
};

int main() {

    return 0;
}