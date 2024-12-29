/*
 *  Author      : Reese
 *  Created On  : 2024-12-29 16:26
 *  Description : https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/description/
 */

#include <iostream>
#include <string>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// DP Optimize
const int N = 1000000007;
int freq[1000][26];

class Solution {
  public:
    int numWays(std::vector<std::string> &words, std::string target) {
        int n = words.size(), m = words[0].size(), k = target.size();

        // 計算每層的字母出現次數
        std::memset(freq, 0, sizeof(freq));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int c = words[j][i] - 'a';
                ++freq[i][c];
            }
        }

        // 初始化 dp
        long long dp[k + 1];
        std::memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        // 填表計算答案
        for (int i = 1; i < m + 1; ++i) {
            for (int j = k; j > 0; --j) {
                int cnt = freq[i - 1][target[j - 1] - 'a'];
                if (cnt > 0) {
                    dp[j] += dp[j - 1] * cnt;
                    dp[j] %= N; // 避免 overflow
                }
            }
        }

        return dp[k];
    }
};

// DP
// const int N = 1000000007;
// std::vector<std::vector<int>> freq(1000, std::vector<int>(26));

// class Solution {
//   public:
//     int numWays(std::vector<std::string> &words, std::string target) {
//         int n = words.size(), m = words[0].size(), k = target.size();

//         // 初始化 freq
//         for (auto &f : freq) {
//             std::fill(f.begin(), f.end(), 0);
//         }
//         // 計算每層的字母出現次數
//         for (int i = 0; i < m; ++i) {
//             for (int j = 0; j < n; ++j) {
//                 int c = words[j][i] - 'a';
//                 ++freq[i][c];
//             }
//         }

//         // 初始化 dp
//         // dp[m][k] 表示前 m 個字母中，能夠組成 target 前 k 個字符的組合數
//         long long dp[m + 1][k + 1];
//         std::memset(dp, 0, sizeof(dp));
//         for (int i = 0; i < m + 1; ++i) {
//             dp[i][0] = 1;
//         }
//         // 填表計算答案
//         for (int i = 1; i < m + 1; ++i) {
//             for (int j = 1; j < k + 1; ++j) {
//                 int cnt = freq[i - 1][target[j - 1] - 'a'];
//                 if (cnt > 0) {
//                     dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] * cnt) % N;
//                 }
//                 else {
//                     dp[i][j] = dp[i - 1][j] % N;
//                 }
//             }
//         }

//         return dp[m][k];
//     }
// };

int main() {

    return 0;
}