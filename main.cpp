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
 * 遇到 '(' 將其在 s 的 index push 到 stack，遇到 ')' 則將 stack pop 並算出該 '(' 和
 * stack top 的距離，這個距離就是當前有效子字串的長度。
 * 以上面的範例來說，一開始將 -1 push 進 stack 中表示邊界，開始遍歷 s，idx = 0 時 stack = {-1, 0}，
 * idx = 1 時 stack = {-1, 0, 1}，idx = 2 時將 stack pop，stack 變成 {-1, 0}，此時
 * stack 的 top 為該組有效子字串的邊界，該組有效子字串的長度為 i - stack.top() = 2 - 0 = 2，
 * idx = 3 時 stack = {-1, 0, 3}，idx = 4 時將 stack pop，stack 變成 {-1, 0}，該子字串的長度為
 * i - stack.top() = 4 - 0 = 4。
 * 假如 s = "())()()"，idx = 1 時將 stack pop，stack = {-1}，子字串長度為 1 - (-1) = 2，
 * idx = 2 時將 stack pop，stack = {}，此時 ')' 沒有配對到 '('，子字串長度 = 0，
 * 將該 ')' 的index 放入 stack 中當作新的邊界，idx = 3 時，stack = {2, 3}，idx = 4 時將 stack pop，
 * stack 變成 {2}，子字串長度為 4 - 2 = 2。以此類推，這些有效子字串的長度中最大者即為答案。
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

            // 將 "(" 的 index 放入 stack 中
            if (s[i] == '(') {
                st.push(i);
            }
        }

        // 遍歷 s，找出最長的連續 1 的長度
        int longest = 0;
        for (int i = 0; i < s.size(); ++i) {
            int temp = 0;

            while (i < s.size() && s[i] == '1') {
                ++temp;
                ++i;
            }

            longest = std::max(longest, temp);
        }

        return longest;
    }
};

// 方法 2：
class Solution2 {
  public:
    int longestValidParentheses(std::string s) {
        std::stack<int> st;
    }
};

int main() {

    return 0;
}