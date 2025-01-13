/*
 *  Author      : Reese
 *  Created On  : 2025-01-13 18:17
 *  Description : https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/description/
 */

#include <iostream>
#include <stack>
#include <string>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// Greedy
class Solution {
  public:
    int minAddToMakeValid(std::string &s) {
        int balance = 0, res = 0;

        for (const char &c : s) {
            balance += c == '(';
            balance -= c == ')';
            if (balance < 0) {
                balance = 0;
                ++res;
            }
        }

        return res + balance;
    }
};

// Stack
// class Solution {
//   public:
//     int minAddToMakeValid(std::string &s) {
//         int res = 0;
//         std::stack<int> st;
//         for (const char &c : s) {
//             if (c == '(') {
//                 st.push(c);
//             }
//             else if (!st.empty()) {
//                 st.pop();
//             }
//             else {
//                 ++res;
//             }
//         }

//         return res + st.size();
//     }
// };

int main() {

    return 0;
}