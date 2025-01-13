/*
 *  Author      : Reese
 *  Created On  : 2025-01-12 15:32
 *  Description : https://leetcode.com/problems/remove-invalid-parentheses/description/
 */

#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// DFS + 剪枝
// class Solution {
//   public:
//     std::vector<std::string> removeInvalidParentheses(std::string s) {
//         // 計算需要刪除的左右括號數量，確保最長的合法括號字串
//         int l_to_delete = 0, r_to_delete = 0, n = s.size();
//         for (char &c : s) {
//             if (c == '(') { // 遇到左括號，增加未匹配的左括號數量
//                 ++l_to_delete;
//             }
//             else if (c == ')') {
//                 if (l_to_delete > 0) { // 若有左括號可以匹配，則匹配左括號
//                     --l_to_delete;
//                 }
//                 else { // 沒有可匹配的左括號，右括號需要移除的數量 +1
//                     ++r_to_delete;
//                 }
//             }
//         }

//         std::vector<std::string> res;
//         auto dfs = [&](auto &&dfs, int l, int r, int balance, int skipped, int index, std::string &cur) {
//             if (balance < 0) { // 左括號數量小於右括號數量，無效括號字串
//                 return;
//             }
//             if (index == n) { // 已遍歷完字串，檢查是否為最長的合法括號字串
//                 if (balance == 0 && l == 0 && r == 0) {
//                     res.emplace_back(cur);
//                 }
//                 return;
//             }

//             if (s[index] == '(') {
//                 // skipped 最低位 bit 為 0 表示前面沒有丟棄左括號，因此可以選擇當前左括號
//                 if (!(skipped & 0b1)) {
//                     cur += '(';
//                     dfs(dfs, l, r, balance + 1, 0, index + 1, cur); // 將 skipped 重置為 0
//                     cur.pop_back();
//                 }
//                 // 檢查是否還有左括號可以刪除，若有則刪除左括號，並且 skipped 最低位設為 1 表示 "不選擇左括號"
//                 if (l > 0) {
//                     dfs(dfs, l - 1, r, balance, skipped | 0b1, index + 1, cur);
//                 }
//             }
//             else if (s[index] == ')') {
//                 // skipped 次低位 bit 為 0 表示前面沒有丟棄右括號，因此可以選擇當前右括號
//                 if (!(skipped & 0b10)) {
//                     cur += ')';
//                     dfs(dfs, l, r, balance - 1, 0, index + 1, cur); // 將 skipped 重置為 0
//                     cur.pop_back();
//                 }
//                 // 檢查是否還有右括號可以刪除，若有則刪除右括號，並且 skipped 次低位設為 1 表示 "不選擇右括號"
//                 if (r > 0) {
//                     dfs(dfs, l, r - 1, balance, skipped | 0b10, index + 1, cur);
//                 }
//             }
//             else { // 若為其他字元，直接加入字串
//                 cur += s[index];
//                 dfs(dfs, l, r, balance, 0, index + 1, cur);
//                 cur.pop_back();
//             }
//         };

//         std::string cur;
//         dfs(dfs, l_to_delete, r_to_delete, 0, 0, 0, cur);

//         return res;
//     }
// };

// BFS
class Solution {
  public:
    std::vector<std::string> removeInvalidParentheses(std::string s) {
        // 若字串本身為合法括號字串，則直接返回
        if (isValid(s)) {
            return {s};
        }

        std::queue<std::string> q;
        q.push(s);

        while (!q.empty()) {
            // non_repeat_res 用來儲存當前層的合法括號字串，children 用來儲存下一層的合法括號字串
            // 必須要用 std::unordered_set 來儲存，不然大量的重複字串會導致 MLE
            std::unordered_set<std::string> non_repeat_res, children;
            int n = q.size();
            // 遍歷當前層的括號字串
            for (int i = 0; i < n; ++i) {
                std::string cur = q.front();
                q.pop();

                // 刪減該字串某個字元，並檢查是否為合法括號字串，若是則加入 non_repeat_res 中
                for (int j = 0; j < cur.size(); ++j) {
                    // 剪枝，若當前字元與前一個字元相同則跳過
                    if (j > 0 && cur[j] == cur[j - 1]) {
                        continue;
                    }
                    // 跳過非括號字元
                    if (cur[j] != '(' && cur[j] != ')') {
                        continue;
                    }

                    std::string tmp = cur;
                    tmp.erase(tmp.begin() + j);
                    !isValid(tmp) ? children.insert(tmp) : non_repeat_res.insert(tmp);
                }
            }

            // 若當前層的合法括號字串數量 > 0，則返回當前層的合法括號字串
            // 這樣所得到的括號字串是刪除最少字元數的合法括號字串
            if (non_repeat_res.size() > 0) {
                return {non_repeat_res.begin(), non_repeat_res.end()};
            }
            else {
                for (auto &child : children) {
                    q.push(child);
                }
            }
        }

        return {""};
    }

    // 檢查括號字串是否合法
    bool isValid(const std::string &s) {
        int balance = 0;

        for (const char &c : s) {
            balance += c == '(';
            balance -= c == ')';
            if (balance < 0) {
                return false;
            }
        }

        return balance == 0;
    }
};

int main() {

    return 0;
}