/*
 *  Author      : Reese
 *  Created On  : 2025-01-01 10:43
 *  Description : https://leetcode.com/problems/maximum-score-after-splitting-a-string/description/
 */

#include <algorithm>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int maxScore(std::string s) {
        int score = std::ranges::count(s, '1');

        int res = 0;
        for (int i = 0; i < s.size() - 1; ++i) {
            score += s[i] == '0' ? 1 : -1;
            res = std::max(res, score);
        }

        return res;
    }
};

// class Solution {
//   public:
//     int maxScore(std::string s) {
//         int cnt_ones = 0;
//         for (char &c : s) {
//             cnt_ones += c == '1';
//         }

//         int res = 0, cnt_zeros = 0;
//         // 因為兩個字串不為空，所以最多只能遍歷到倒數第二個字元
//         for (int i = 0; i < s.size() - 1; ++i) {
//             cnt_zeros += s[i] == '0';
//             cnt_ones -= s[i] == '1';
//             res = std::max(res, cnt_zeros + cnt_ones);
//         }

//         return res;
//     }
// };

int main() {

    return 0;
}