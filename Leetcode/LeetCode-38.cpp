/*
 * 題目： https://leetcode.com/problems/count-and-say/description/
 *
 * 題目解釋：
 * 給一個整數 n，return 經過 `countAndSay` 之後的結果。
 * countAndSay 的定義：
 * countAndSay(1) = "1"
 * countAndSay(n) = countAndSay(n - 1) 的 Run-length encoding。
 * Run-length encoding(RLE) 的定義:
 * 這是一種無損壓縮資料的方式。假設有字串 s = "112232244421"，可以將其依照連續相同字
 * 分組成 {"11", "22", "3", "22", "444", "2", "1"}，計算每組相同字的數量，分別為
 * {2, 2, 1, 2, 3, 1, 1}，而該字串的 RLE 為 {{數量 + 字1}, {數量 + 字2}...}，
 * 也就是 兩個1 + 兩個2 + 一個3 +兩個2 + 三個4 + 一個2 + 一個1，RLE of s =
 * "21" + "22" + "13" + "22" + "34" + "12" + "11" = "21221322341211"。
 *
 * 思路：
 * 從本質上來說這是一個遞迴問題，因此只要從 k = 1 時的狀態開始迭代到 k = n 的狀態即可得到答案。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::string countAndSay(int n) {
        // 初始狀態，countAndSay(1) = "1"
        std::string cur {"1"};

        // 從 n = 2 開始迭代
        for (int i = 1; i < n; ++i) {
            int count = 1;
            std::string next;

            // 計算 k = i 的字串，也就是 k = i-1 字串的 RLE
            for (int j = 1; j < cur.length(); ++j) {
                if (cur[j] != cur[j - 1]) {
                    // 出現次數 + 字元
                    next += std::to_string(count) + cur[j - 1];
                    count = 0;
                }
                ++count;
            }
            // 加上最後一個字元
            next += std::to_string(count) + cur.back();
            // 更新當前字串
            cur = std::move(next);
        }

        return cur;
    }
};

int main() {

    return 0;
}