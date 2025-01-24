/*
 * 題目： https://leetcode.com/problems/longest-valid-parentheses/description/
 *
 * 題目解釋：
 * 給一個由 '('、')' 組成的string，找出最長的有效括號子字串。
 * e.g. "(()()()((())" 的最長有效子字串是 "()()()"。
 *
 * 思路：
 * 方法 1:
 * 將所有配對成功的 "()" 的所在位置設為 "1"，表示該位置的括號配對成功，以上面的範例來看，s 會變成：
 * "(111111(1111"，然後從 s 中找出最長的連續 1 的長度即為答案。
 *
 * 方法 2:
 * 初始 stack = {-1} ，-1 當作邊界用以計算當前配對到的子字串長度，每當遇到 '(' 就將其 index push到
 * stack 中，如果遇到 ')' 則將stack pop，由於 stack 中存放的都是尚未配對到的括號，因此可以將這些沒有
 * 配對到的括號當作已經配對到的括號子字串的起始點，子字串長度 = index - stack.top()。如果 stack為空
 * 表示這個 ')' 沒有對應的 '(' 和它配對，則將該 ')' 的 index 放入 stack 中當作邊界。
 *
 * e.g.：s = "())()()"，一開始將 -1 push 進 stack 中表示邊界，開始遍歷 s。
 * index = 0，push '(' 的 index，stack = {-1, 0}，
 * index = 1，pop stack，stack = {-1}，子字串 = "()"，長度 = i - stack.top() = 1 - (-1) = 2，
 * index = 2，pop stack，stack = {}， ')' 沒有配對到 '('，子字串長度 = 0，
 * 將 ')' 的 index 放入 stack 中當作新的邊界，stack = {2}，
 * index = 3，push '(' 的 index，stack = {2, 3}，
 * index = 4，pop stack，stack = {2}，子字串 = "()"，長度 = i - stack.top() = 4 - 2 = 2，
 * index = 5，push '(' 的 index，stack = {2, 5}，
 * index = 6，pop stack，stack = {2}，子字串 = "()()"，長度 = i - stack.top() = 6 - 2 = 4。
 * 得到最長有效子字串長度為 4。
 *
 * 方法 3：
 * 以dp來解，創建 integer dp[]，dp[i] 表示以 s[i] 為結尾的最長有效子字串長度。
 * 觀察 s = "()(())"，s[i] = '('，以 '(' 為結尾的子字串不可能是 valid，因此 dp[i] = 0。
 * index = 0，dp[0] = 0，
 * index = 1，有一對括號配對，子字串 = "()"，dp[1] = 2，
 * index = 2，dp[2] = 0，
 * index = 3，dp[3] = 0，
 * index = 4，有一對括號配對，子字串 = "()"，dp[4] = 2
 * index = 5，有一對括號配對，子字串 = "()" + "(())" = "()(())"，dp[5] = 6
 * 由以上觀察可以得到以下規則：
 * 1. 如果 s[i] == '('，dp[i] = 0。
 * 2. 如果 s[i] == ')'，則：
 *    2-1. 如果 s[i - 1] == '('，配對的是一組最小的 "()"，要再加上 dp[i - 2] 的子字串，
 *         也就是 子字串 = "_ _ ... ()"，dp[i] = dp[i - 2] + 2。
 *                           |     |
 *     dp[i - 2] 的子字串 <--|     |--> 配對的 "()"
 *     長度可以是 0 ~ 2*n
 *
 *    2-2. 如果 s[i - 1] == ')'，配對的字串是 "((_ _ ...))"，dp[i] = 配對的 "()" + "()" 之間的子字串，
 *                                           ^    ^    ^
 *                             配對的 '(' <--|    |    |--> 配對的 ')'
 *                                               |--> dp[i - 1] 的子字串，長度可以是 0 ~ 2*n
 *
 *         此外還要加上 "((_ _ ...))" 前面的子字串，也就是 "_ _ ...((_ _ ...))"
 *                                                          |       |
 *                         dp[i - dp[i - 1] - 2]的子字串 <--|       |--> 配對的 "()" 所形成的子字串
 *
 *         其中 dp[i - 1] + 2 是 "((_ _ ...))" 的子字串長度，i - (dp[i - 1] + 2) 是 "()" 形成的子字串的前一格 index
 *         也就是 "_ _ ...((_ _ ...))"，因此 dp[i] = (dp[i - 1] + 2) + dp[i - dp[i - 1] - 2]。
 *                      ^ i - (dp[i - 1] + 2) 是這個位置的index
 *
 * 總結：dp轉移狀態是由配對 "()" 形成的子字串長度 + 該子字串前的子字串長度。
 */

#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 方法 1：
class Solution {
  public:
    int longestValidParentheses(std::string s) {
        std::stack<int> st;
        for (int i = 0; i < s.size(); ++i) {
            // 配對一組 "()"，將其在 s 中的值設為 "1"
            if (s[i] == ')' && !st.empty()) {
                s[st.top()] = '1';
                s[i] = '1';
                st.pop();
            }

            // 將 '(' 的 index 放入 stack 中
            if (s[i] == '(') {
                st.push(i);
            }
        }

        // 遍歷 s，找出最長的連續 1 的長度
        int res = 0, count = 0;
        for (char c : s) {
            if (c != '1') {
                count = 0;
                continue;
            }
            ++count;
            res = std::max(res, count);
        }

        return res;
    }
};

// // 方法 2：
// class Solution {
//   public:
//     int longestValidParentheses(std::string s) {
//         int res = 0;
//         std::stack<int> st;
//         st.push(-1); // 初始邊界

//         for (int i = 0; i < s.size(); ++i) {
//             if (s[i] == '(') {
//                 st.push(i);
//             }
//             else {
//                 st.pop();

//                 if (st.empty()) { // 沒有配對到的 ')'，將其 index 當作邊界
//                     st.push(i);
//                 }
//                 else {
//                     res = std::max(res, i - st.top());
//                 }
//             }
//         }

//         return res;
//     }
// };

// // 方法 3：
// class Solution {
//   public:
//     int longestValidParentheses(std::string s) {
//         std::vector<int> dp(s.size(), 0);

//         int res = 0, count_left_bracket = 0; // count_left_bracket 用來計算 '(' 的數量
//         for (int i = 0; i < s.size(); ++i) {
//             if (s[i] == '(') {
//                 ++count_left_bracket;
//             }
//             if (count_left_bracket > 0 && s[i] == ')') {
//                 dp[i] = 2; // 先設定為 2，因為配對到的 "()" 的長度為 2

//                 if (i > 2 && s[i - 1] == '(') {
//                     dp[i] += dp[i - 2];
//                 }
//                 else {
//                     dp[i] += dp[i - 1];
//                     if (i - dp[i] > 0) {
//                         dp[i] += dp[i - dp[i]];
//                     }
//                 }
//                 --count_left_bracket;
//             }
//             res = std::max(res, dp[i]);
//         }

//         return res;
//     }
// };

int main() {

    return 0;
}