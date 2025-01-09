/*
 *  Author      : Reese
 *  Created On  : 2025-01-07 12:53
 *  Description : https://leetcode.com/problems/string-matching-in-an-array/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// KMP
class Solution {
  public:
    // 計算 s 的 LPS table
    std::vector<int> getNext(std::string &s) {
        int j = 0, n = s.size();
        // next[i] = j 表示長度為 i 的字串其 LPS 長度為 j
        std::vector<int> next(n + 1, 0);
        for (int i = 1; i < n; ++i) {
            // 若當前字元不匹配，用 next 表找出能匹配的 s[j]
            while (j > 0 && s[i] != s[j]) {
                j = next[j];
            }
            // 如果 s[i] = s[j]，j 要 +1 往後一個字元來繼續檢查，否則保持為 0
            j += s[i] == s[j];
            next[i + 1] = j;
        }

        return next;
    }

    std::vector<std::string> stringMatching(std::vector<std::string> &words) {
        std::vector<std::string> res;
        for (int i = 0; i < words.size(); ++i) {
            bool isSubstringFound = false;
            std::vector<int> next = getNext(words[i]); // 取得 LPS table

            for (int j = 0; j < words.size(); ++j) {
                // 用於確認 words[i] 是否被添加至 res 中，避免重複添加答案
                if (isSubstringFound) {
                    break;
                }
                // 若 words[i] 的長度大於 words[j]，那麼前者不可能是後者的 substring
                if (i == j || words[i].size() > words[j].size()) {
                    continue;
                }

                // 匹配 words[i] 和 words[j] 的做法和 getNext() 一樣，
                int m = 0; // m 為 words[i] 當前 index
                for (int n = 0; n < words[j].size(); ++n) {
                    while (m > 0 && words[i][m] != words[j][n]) {
                        m = next[m];
                    }
                    m += words[i][m] == words[j][n];
                    if (m == words[i].size()) {
                        res.emplace_back(words[i]);
                        isSubstringFound = true; // 設為 true 用以跳出 j 迴圈
                        break;
                    }
                }
            }
        }

        return res;
    }
};

// // 暴力解
// class Solution {
//   public:
//     std::vector<std::string> stringMatching(std::vector<std::string> &words) {
//         int n = words.size();

//         // 檢查 words 中有沒有某個字串的 substring 和 word[i] 相同
//         std::vector<std::string> res;
//         for (int i = 0; i < n; ++i) {
//             for (int j = 0; j < n; ++j) {
//                 if (i != j && words[j].find(words[i]) != std::string::npos) {
//                     res.emplace_back(words[i]);
//                     break;
//                 }
//             }
//         }

//         return res;
//     }
// };

// int main() {

//     return 0;
// }