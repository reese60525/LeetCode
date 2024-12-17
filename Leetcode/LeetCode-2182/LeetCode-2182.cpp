/*
 * 題目：
 *
 * 題目解釋：
 *
 * 思路：
 *
 */
#include <iostream>
#include <string>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::string repeatLimitedString(std::string s, int repeatLimit) {
        // 紀錄字母的出現次數
        int freq[26] = {0};
        for (char c : s) {
            ++freq[c - 'a'];
        }

        int cur = 25, next = 25; // cur: 當前最大字母，next: 當前次大字母
        s.clear();               // 使用原先題目給的 s 來存放答案
        while (cur >= 0) {
            // 找出當前最大字母與次大字母
            if (freq[cur] == 0) {
                --cur;
                continue;
            }
            if (next >= 0 && (next >= cur || freq[next] == 0)) {
                --next;
                continue;
            }

            // 將當前最大字母加入 s 中
            int cnt = std::min(freq[cur], repeatLimit); // 最多只能連續 repeatLimit 次，若不足則全部加入
            s.append(cnt, ('a' + cur));
            freq[cur] -= cnt;

            // 如果當前最大字母用完，則將其變成次大字母
            if (freq[cur] == 0) {
                cur = next;
            }
            // 若還有次大字母，則將一個次大字母加入 s 中
            else if (next >= 0) {
                s.push_back(('a' + next));
                --freq[next];
            }
            // 如果沒有次大字母了，無須再添加字母到 s 中，結束迴圈
            else {
                break;
            }
        }

        return s;
    }
};

int main() {

    return 0;
}