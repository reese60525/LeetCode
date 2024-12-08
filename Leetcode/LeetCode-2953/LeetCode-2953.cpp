/*
 * 題目：
 *
 * 題目解釋：
 *
 * 思路：
 *
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int slidingWindow(std::string_view s, int k) {
        int res = 0, n = s.size();

        // 共有 1 ~ 26 個小寫字母，所以 window 的 size 共有 26 種，size = i * k
        // i 代表當前 window 只可以有 i 種字母出現
        for (int i = 1; i <= 26 && i * k <= n; ++i) {
            // valid_count 紀錄 window 內正好出現 k 次的字母數量
            int valid_count = 0, window_size = i * k;
            // freq 紀錄 window 內每個字母出現的次數
            int freq[26] = {0};

            for (int j = 0; j < n; ++j) {
                // 將字母出現次數 + 1，如果字母出現次數等於 k，valid_count 加 1
                if (++freq[s[j] - 'a'] == k) {
                    ++valid_count;
                }
                // 當目前的 window 內字母數量有 >= window_size 時才可以開始判斷
                if (j + 1 >= window_size) {
                    // 如果 valid_count 等於 i，代表 window 內正好有 i
                    // 種字母出現 k 次，res + 1
                    if (valid_count == i) {
                        ++res;
                    }
                    // 將 window 往右移動，window 最左邊的字母出現次數 - 1
                    // 如果該字母出現次數 - 1 後會等於 k - 1，表示原本是 valid
                    // 字母(出現 k 次) 所以 valid_count 要 - 1
                    if (--freq[s[j - window_size + 1] - 'a'] == k - 1) {
                        --valid_count;
                    }
                }
            }
        }

        return res;
    }

    int countCompleteSubstrings(std::string word, int k) {
        int res = 0;
        // 將 word 轉換成 string_view，對於將 word 切成 substring 的操作
        // string_view 不會複製字串內容，僅存儲指針和長度，因此能提高效能
        std::string_view w(word);

        // 遍歷 word，將 word 切成許多個 substring，每個 substring
        // 內的相鄰字元絕對值差值 <= 2
        for (int i = 0; i < word.size(); ++i) {
            int begin = i; // substring 的起始位置
            // 找出 substring 的結束位置
            while (i < word.size() - 1 && std::abs(word[i] - word[i + 1]) <= 2) {
                ++i;
            }
            // 將 substring 傳入 slidingWindow 函式，計算符合 "complete"
            // 第一個條件的 substrings 數量
            res += slidingWindow(w.substr(begin, i - begin + 1), k);
        }

        return res;
    }
};

int main() {

    return 0;
}