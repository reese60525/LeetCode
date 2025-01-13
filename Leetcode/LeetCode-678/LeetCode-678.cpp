/*
 *  Author      : Reese
 *  Created On  : 2025-01-13 14:02
 *  Description : https://leetcode.com/problems/valid-parenthesis-string/description/
 */

#include <iostream>
#include <stack>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// Greedy
class Solution {
  public:
    bool checkValidString(std::string &s) {
        int min_l = 0, max_l = 0;
        for (const char &c : s) {
            min_l += c == '(';
            min_l -= c == ')';
            min_l -= c == '*';
            max_l += c == '(';
            max_l -= c == ')';
            max_l += c == '*';
            if (max_l < 0) {
                return false;
            }
            if (min_l < 0) {
                min_l = 0;
            }
        }

        return min_l == 0;
    }
};

// Greedy
// class Solution {
//   public:
//     bool checkValidString(std::string &s) {
//         int l_balance = 0, r_balance = 0, n = s.size();

//         for (int i = 0; i < n; ++i) {
//             // 計算由左往右的括號 balance
//             l_balance += s[i] == '*';
//             l_balance += s[i] == '(';
//             l_balance -= s[i] == ')';
//             // 計算由右往左的括號 balance
//             r_balance += s[n - i - 1] == '*';
//             r_balance += s[n - i - 1] == ')';
//             r_balance -= s[n - i - 1] == '(';
//             // 如果有任一個無法保持 balance，則該字串不是合法的括號字串
//             if (l_balance < 0 || r_balance < 0) {
//                 return false;
//             }
//         }

//         return true;
//     }
// };

// Stack
// class Solution {
//   public:
//     bool checkValidString(std::string s) {
//         // 記錄左括號和星號的 index，並匹配所有右括號
//         std::stack<int> left, star;
//         for (int i = 0; i < s.size(); ++i) {
//             if (s[i] == '(') {
//                 left.push(i);
//             }
//             else if (s[i] == '*') {
//                 star.push(i);
//             }
//             else {
//                 if (!left.empty()) {
//                     left.pop();
//                 }
//                 else if (!star.empty()) {
//                     star.pop();
//                 }
//                 else {
//                     return false;
//                 }
//             }
//         }

//         // 檢查剩餘的左括號和星號
//         while (!left.empty() && !star.empty()) {
//             // 如果左括號的 index > 星號的 index，代表左括號右邊沒有星號能匹配
//             if (left.top() > star.top()) {
//                 return false;
//             }
//             left.pop();
//             star.pop();
//         }

//         // 最後確認左括號是否都已經匹配完
//         return left.empty();
//     }
// };

// DP
// class Solution {
//   public:
//     bool checkValidString(std::string s) {
//         int n = s.size();

//         // 初始化 dp
//         bool dp[n][n];
//         for (int i = 0; i < n; ++i) {
//             dp[i][i] = s[i] == '*';
//         }
//         for (int i = 1; i < n; ++i) {
//             char c1 = s[i - 1], c2 = s[i];
//             dp[i - 1][i] = (c1 == '(' || c1 == '*') && (c2 == ')' || c2 == '*');
//         }

//         // 從 dp 矩陣的右下角開始，從右往左，從下往上
//         // 因為 dp[i][j] 會用到 dp[i + 1][j - 1] 和 dp[i][k] && dp[k + 1][j]
//         for (int i = n - 3; i >= 0; --i) {
//             for (int j = i + 2; j < n; ++j) {
//                 dp[i][j] = false;
//                 if ((s[i] == '(' || s[i] == '*') && (s[j] == ')' || s[j] == '*')) {
//                     dp[i][j] = dp[i + 1][j - 1];
//                 }
//                 // !dp[i][j] 表示只有 dp[i][j] 為 false 才會進去迴圈來檢查
//                 for (int k = i; k < j && !dp[i][j]; ++k) {
//                     dp[i][j] = dp[i][k] && dp[k + 1][j];
//                 }
//             }
//         }

//         return dp[0][n - 1];
//     }
// };

int main() {

    return 0;
}