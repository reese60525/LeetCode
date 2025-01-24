# <center> [LeetCode - 2953. Count Complete Substrings](https://leetcode.com/problems/count-complete-substrings/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210161329090.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210161329090.png)

給一個只包含小寫英文字母的字串 `word` 和一個整數 `k`，找出 `word` 中所有是 `complete` 的 substring 的數量。

complete substring 的定義為：

1. 每個字母在 substring 中都正好出現 `k` 次。

2. substring 中每個相鄰的字元的絕對值差要小於等於 2，也就是 $abs(word[i] - word[i+1]) \leq 2$ 。

e.g.

1. `word` = "igigee"，`k` = 2

    符合條件的 complete substring 有 {"ee", "igig", "igigee"}，所以答案是 3。

2. `word` = "aaabbbccc"，`k` = 3

    符合條件的 complete substring 有 {"aaa", "bbb", "ccc", "aaabbb", "bbbccc", "aaabbbccc"}，所以答案是 6。

## 解題思路

### 1. Grouped Loop（分組循環） and Sliding Window

先處理 `complete` 中的第二個條件，也就是相鄰字元的絕對值差要小於等於 2。對於這個條件，我們可以遍歷 `word` 中的每個字元，將其進行分組，令 `begin` 為記錄當前 `word` index 的起始點，從 `begin` 開始遍歷 `word`，當遇到 $abs(word[i] - word[i+1]) > 2$ 時，可得到 $index = [begin, i]$ 的 substring，該 substring 能夠滿足 `complete` 中的第二個條件。

接著處理 `complete` 中的第一個條件，也就是每個字母在 substring 中都正好出現 `k` 次。`word` 是由 26個 小寫字母所組成的，因此能滿足第一個條件的所有 substring 的可能長度為 $[1 \cdot k,26 \cdot k]$ 。舉例來說，如果 $k = 3$ 則長度為 9 的 `complete` substring 一定正好包含三種不同的字母，如果不是剛好包含三種字母的話，則一定不會是 `complete`。同理，若是 $k = 3$ ，則長度為 11 的 substring 必不可能是`complete`，因為包含三種字母的 `complete` substring 長度為 9，而包含四種字母的 `complete` substring 長度為 12。

#### 程式碼

```c++ {.line-numbers}
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
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241209003727921.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241209003727921.png)

#### 複雜度分析

令 $n$ 為字串 `word` 的長度。

- 時間複雜度： $O(26 \cdot n)$ = $O(n)$

- 空間複雜度： $O(1)$
