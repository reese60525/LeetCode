# <center> [916. Word Subsets](https://leetcode.com/problems/word-subsets/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501100911550.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501100911550.png)

給兩個字串陣列 `words1` 和 `words2`，找出所有 `words1` 中滿足 `words1[i]` 是 `words2` 中**所有字串**的父集合的字串。

對於以下字串 $word1 = "wrr"$ ， $word2 = "warrior"$ ， $word3 = "world"$

- `word2` 是 `word1` 的父集合，因為 `word1` 中所有字元都出現在 `word2` 中（每種字元的出現次數也要考量）

- `word3` 不是 `word1` 的父集合，因為 `word1` 中 `r` 出現了兩次，但 `word3` 中只有一次

## 解題思路

### 1. Hash Map

`words1[i]` 要滿足**所有** `words2` 的字串，可以將 `words2` 中所有字串的每個字元出現次數都記錄下來，然後再確認 `words1[i]` 能否滿足 `words2` 中每個字串的每種字元出現次數。

但是這樣做會超時，因此可以進一步優化，要滿足整個 `words2`，也就是要滿足所有在 `words2` 中出現的字元，假如 `'a'` 在 `words2` 中每個字串出現了 `[1, 0, 3, 2]` 次，那麼 `words1[i]` 中 `'a'` 的出現次數必須 $\geq 3$ 才能滿足 `words2`，因此只要記錄 `words2` 中每種字元在各個字串中出現次數最多的值即可。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<std::string> wordSubsets(std::vector<std::string> &words1, std::vector<std::string> &words2) {
        // 計算 words2 中每個字串的字母出現次數，對每個字母取出現次數最多的
        int occurrence[26] {0};
        for (const std::string &word : words2) {
            int temp[26] {0};
            for (const char &c : word) {
                int k = c - 'a';
                ++temp[k];
                // 由於每個字串長度不超過 10，因此在這裡直接比較就好
                // 如果字串最長能遠超 26，建議 temp 算完後再用一個 for 迴圈來遍歷比較
                occurrence[k] = std::max(occurrence[k], temp[k]);
            }
        }

        std::vector<std::string> res;
        res.reserve(words1.size());
        for (const std::string &word : words1) {
            // 計算 words1 的字母出現次數
            int cnt[26] {0};
            for (const char &c : word) {
                ++cnt[c - 'a'];
            }

            // 遍歷 occurrence 進行比較
            int i = 0;
            while (i < 26 && cnt[i] >= occurrence[i]) {
                ++i;
            }
            if (i == 26) {
                res.emplace_back(word);
            }
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501100931396.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501100931396.png)

#### 複雜度分析

令 $n$ 為 `words1` 的長度， $m$ 為 `words2` 的長度， $l_1$ 為 `words1` 中字串的平均長度， $l_2$ 為 `words2` 中字串的平均長度。

- 時間複雜度： $O(m \cdot l_2 + n \cdot l_1)$

- 空間複雜度： $O(1)$ 。
