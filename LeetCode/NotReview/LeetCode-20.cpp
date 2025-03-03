/*
 * 題目： https://leetcode.com/problems/valid-parentheses/description/
 *
 * 題目解釋：
 * 給一個由「大中小括號」組成字串，判斷該字串是否合法。
 * [] is valid, ][] is not valid, ][ is not valid.
 *
 * 思路：
 * 對於該string，從頭開始遍歷每個字元，當遇到第一個右括號時，其左方的字元必須是相對應的
 * 左括號，e.g. 對於"(({["接下來的遇到的右括號得是']'，因此可以建立一個stack，當遇到左
 * 括號時就將其放入stack，若是遇到右括號就判斷stack的top是否為相對應的左括號，是的話就將
 * stack的top pop掉，整個string遍歷後stack應該為空(每個左括號都有對應到一個右括號)。
 */
#include <iostream>
#include <stack>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

/*
 * 題目解釋：
 * 給一個由「大中小括號」組成字串，判斷該字串是否合法。
 * [] is valid, ][] is not valid, ][ is not valid.
 *
 * 思路：
 * 對於該string，從頭開始遍歷每個字元，當遇到第一個右括號時，其左方的字元必須是相對應的
 * 左括號，e.g.
 * 對於"(({["接下來的遇到的右括號得是']'，因此可以建立一個stack，當遇到左
 * 括號時就將其放入stack，若是遇到右括號就判斷stack的top是否為相對應的左括號，是的話就將
 * stack的top
 * pop掉，整個string遍歷後stack應該為空(每個左括號都有對應到一個右括號)。
 */

class Solution {
  public:
    bool isValid(std::string s) {
        std::stack<char> st;

        for (char &c : s) {
            if (c == '(' || c == '[' || c == '{') { // 將左括號放入stack
                st.push(c);
            }
            else {
                // 若stack為空，或是括號不能對應，則return false
                if (st.empty() || (c == ')' && st.top() != '(') || (c == ']' && st.top() != '[') ||
                    (c == '}' && st.top() != '{')) {
                    return false;
                }

                st.pop();
            }
        }

        // 判斷stack是否為空，若為空則代表每個左括號都有對應到一個右括號
        return (st.empty()) ? true : false;
    }
};

int main() {

    return 0;
}