/*
 * 題目：
 *
 * 題目解釋：
 *
 * 思路：
 *
 */
#include <functional>
#include <iostream>
#include <map>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::string repeatLimitedString(std::string s, int repeatLimit) {
        std::map<char, int, std::greater<char>> freq;
        for (auto c : s) {
            ++freq[c];
        }

        auto it = freq.begin();
        std::string res;
        while (it != freq.end()) {
            it = freq.begin();                           // 當前的最大字母
            int cnt = std::min(it->second, repeatLimit); // 當前字母的可用數量

            // 將字母累加至 res
            res.append(cnt, it->first);
            it->second -= cnt;

            // 如果已用完該字母，從 map 中刪除
            if (it->second == 0) {
                freq.erase(it->first);
            }
            else {
                // 如果還有剩餘字母，要插入第二大的字母
                auto next_it = std::next(it);
                // 如果已經沒有第二大的字母，則結束迴圈
                if (next_it == freq.end()) {
                    break;
                }
                res += next_it->first;
                if (--next_it->second == 0) {
                    freq.erase(next_it->first);
                }
            }
        }

        return res;
    }
};

int main() {

    return 0;
}