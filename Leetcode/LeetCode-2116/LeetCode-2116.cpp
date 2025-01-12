/*
 *  Author      : Reese
 *  Created On  : 2025-01-12 09:52
 *  Description : https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/description/
 */

#include <iostream>
#include <stack>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// Greedy and Counting
class Solution {
  public:
    bool canBeValid(std::string &s, std::string &locked) {
        // 奇數個括號不可能有合法的括號字串，回傳 false
        int n = s.size();
        if (s.size() & 1) {
            return false;
        }

        // 檢查 locked[i] = 1 的左右括號是否能滿足當前 substring 的括號平衡
        int l_balance = 0, r_balance = 0;
        for (int i = 0; i < n; ++i) {
            l_balance += (s[i] == ')' && locked[i] == '1') ? -1 : 1;
            r_balance += (s[n - i - 1] == '(' && locked[n - i - 1] == '1') ? -1 : 1;
            // 如果當前 substring 的括號不平衡，回傳 false
            if (l_balance < 0 || r_balance < 0) {
                return false;
            }
        }

        return true;
    }
};

// Greedy and Stack
// class Solution {
//   public:
//     bool canBeValid(std::string &s, std::string &locked) {
//         // 奇數個括號不可能有合法的括號字串，回傳 false
//         if (s.size() & 1) {
//             return false;
//         }

//         // 處理 locked[i] = 1 的左括號
//         std::stack<int> st_unlocked, st_locked;
//         for (int i = 0; i < s.size(); ++i) {
//             if (locked[i] == '0') {
//                 st_unlocked.push(i);
//             }
//             else if (s[i] == '(') {
//                 st_locked.push(i);
//             }
//             else {
//                 if (!st_locked.empty()) {
//                     st_locked.pop();
//                 }
//                 else if (!st_unlocked.empty()) {
//                     st_unlocked.pop();
//                 }
//                 else {
//                     return false;
//                 }
//             }
//         }

//         // 處理 locked[i] = 1 的右括號
//         while (!st_locked.empty() && !st_unlocked.empty()) {
//             // locked[i] = 1 的右括號必須在 locked[i] = 0 的括號之後才能匹配
//             if (st_locked.top() > st_unlocked.top()) {
//                 return false;
//             }
//             st_locked.pop();
//             st_unlocked.pop();
//         }

//         // 若 st_locked 還有剩下，表示無法將 locked[i] = 1 的左括號全都匹配，回傳 false
//         // 反之 st_locked 為空，則剩下的 locked[i] = 0 的括號能夠互相匹配，回傳 true
//         return st_locked.size() == 0;
//     }
// };

int main() {

    return 0;
}