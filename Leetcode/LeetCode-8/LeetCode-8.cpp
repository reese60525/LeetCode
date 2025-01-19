/*
 *  Author      : Reese
 *  Created On  : 2025-01-18 20:08
 *  Description : https://leetcode.com/problems/string-to-integer-atoi/description/
 */

#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// DFA
class DFA {
  private:
    std::string state = "start";
    // 狀態轉移表
    const std::unordered_map<std::string, std::vector<std::string>> table {
        {"start",     {"start", "signed", "in_number", "end"}},
        {"signed",    {"end", "end", "in_number", "end"}     },
        {"in_number", {"end", "end", "in_number", "end"}     },
        {"end",       {"end", "end", "end", "end"}           }
    };

    // 根據輸入字元，取得狀態轉移表的欄位
    int getCol(const char &c) {
        if (c == ' ') {
            return 0;
        }
        else if (c == '+' || c == '-') {
            return 1;
        }
        else if (isdigit(c)) {
            return 2;
        }
        else {
            return 3;
        }
    }

  public:
    int sign = 1, res = 0;

    // 根據狀態來執行不同任務
    void get(const char &c) {
        state = table.at(state)[getCol(c)];
        if (state == "signed") {
            sign = (c == '+') ? 1 : -1;
        }
        else if (state == "in_number") {
            if (res > (INT_MAX - (c - '0')) / 10) {
                res = (sign == 1) ? INT_MAX : INT_MIN;
                sign = 1; // 避免 INT_MIN 被轉成正數
                state = "end";
                return;
            }
            res = res * 10 + (c - '0');
        }
    }

    std::string getState() {
        return state;
    }

    int getRes() {
        return res * sign;
    }
};

class Solution {
  public:
    int myAtoi(std::string &s) {
        DFA dfa;
        for (const char &c : s) {
            if (dfa.getState() == "end") {
                break;
            }
            dfa.get(c);
        }

        return dfa.getRes();
    }
};

// IF ELSE
// class Solution {
//   public:
//     int myAtoi(std::string &s) {
//         int i = 0, n = s.size(), sign = 1;

//         // 處理前導空白
//         while (i < n && s[i] == ' ') {
//             ++i;
//         }
//         // 判斷正負號
//         if (i < n && (s[i] == '+' || s[i] == '-')) {
//             sign = (s[i++] == '+') ? 1 : -1;
//         }
//         // 處理數字
//         int res = 0;
//         while (i < n && s[i] - '0' >= 0 && s[i] - '0' <= 9) {
//             int temp = s[i] - '0';
//             // 判斷是否 overflow
//             if (res > (INT_MAX - temp) / 10) {
//                 return (sign == 1) ? INT_MAX : INT_MIN;
//             }
//             res = res * 10 + temp;
//             ++i;
//         }
//         return res * sign;
//     }
// };

int main() {

    return 0;
}