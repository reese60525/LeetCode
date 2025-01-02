# <center> [2559. Count Vowel Strings in Ranges](https://leetcode.com/problems/count-vowel-strings-in-ranges/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501020944112.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501020944112.png)

給一個只包含小寫英文字母字串陣列 `words` 和 二維整數陣列 `queries`，請回答 `queries` 中的每個查詢，`queries[i] = [a,b]` 表示查詢 `words` 的 index 在 $[a, b]$ 範圍間，有多少字串的開頭是**母音**。

- 母音：指的是英文字母中的 `a`, `e`, `i`, `o`, `u` 。

## 解題思路

### 1. Prefix Sum

計算出 `words` 的合法字串的 `Prefix Sum`，令 `prefix[i]` 表示 `words` 中前 `i` 個字串中合法字串的數量，那麼對於 `queries[i] = [a, b]`，答案就是 `prefix[b+1] - prefix[a]`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> vowelStrings(std::vector<std::string> &words, std::vector<std::vector<int>> &queries) {
        size_t n = words.size(), m = queries.size();
        std::unordered_set<char> letters = {'a', 'e', 'i', 'o', 'u'};

        // 計算 Prefix Sum，prefix_sum[i] 表示前 i 個字串中有多少個合法的字串
        int prefix_sum[n + 1];
        prefix_sum[0] = 0;
        for (size_t i = 1; i <= n; ++i) {
            bool is_valid = letters.contains(words[i - 1].front()) & letters.contains(words[i - 1].back());
            prefix_sum[i] = prefix_sum[i - 1] + is_valid;
        }

        // 回答查詢
        std::vector<int> res(m);
        for (size_t i = 0; i < m; ++i) {
            int a = queries[i][0], b = queries[i][1];
            res[i] = prefix_sum[b + 1] - prefix_sum[a];
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501020956402.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501020956402.png)

時間複雜度： $O(n + m)$ ，其中 $n$ 是 `words` 的長度， $m$ 是 `queries` 的長度。

空間複雜度： $O(n)$ 。
