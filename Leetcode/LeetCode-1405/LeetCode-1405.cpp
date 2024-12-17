/*
 *  File        : LeetCode-1405.cpp
 *  Author      : Reese
 *  Created On  : 2024-12-17 15:13
 *  Description : https://leetcode.com/problems/longest-happy-string/
 */

#include <cstddef>
#include <iostream>
#include <queue>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::string longestDiverseString(int a, int b, int c) {
        // 若出現次數為 0 則不用加入 pq
        std::priority_queue<std::pair<int, char>> pq;
        a > 0 ? pq.push({a, 'a'}) : void();
        b > 0 ? pq.push({b, 'b'}) : void();
        c > 0 ? pq.push({c, 'c'}) : void();

        std::string res;
        res.reserve(a + b + c);
        while (!pq.empty()) {
            // 取出出現次數最多的字元
            auto [cnt, ch] = pq.top();
            pq.pop();

            // 若前兩個字元與當前字元相同，則加入出現次數第二多的字元
            if (res.size() > 1 && res[res.size() - 1] == ch && res[res.size() - 2] == ch) {
                // 若沒有第二多的字元，則離開迴圈
                if (pq.empty()) {
                    break;
                }

                auto [cnt2, ch2] = pq.top();
                pq.pop();
                res.push_back(ch2);
                // 如果出現次數變成 0 就不用放回 pq
                if (--cnt2 > 0) {
                    pq.push({cnt2, ch2});
                }
            }
            else {
                res.push_back(ch);
                --cnt;
            }
            // 如果出現次數變成 0 就不用放回 pq
            if (cnt > 0) {
                pq.push({cnt, ch});
            }
        }

        return res;
    }
};

int main() {

    return 0;
}