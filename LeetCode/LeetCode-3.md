# <center> [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/description/) </center>

## 題目敘述

[![](https://i.imgur.com/vqSnN6G.png)](https://i.imgur.com/vqSnN6G.png)

給一個字串 `s`，找出最長不重複字元的 substring，回傳其長度。

**`s` 的內容只包含 ascii code 範圍內的字元。**

e.g.

1. $s = "abcabcc"$

    最長不重複的 substring 為 `"abc"`，長度為 3，return 3。

2. $s = "aaa"$

    最長不重複的 substring 為 `"a"`，長度為 1，return 3。

## 解題思路

### 1. Sliding Window and Hash Table

用 hash table 紀錄每個字元最新出現的 index，並用一個變數紀錄當前 substring 的起始 index。遍歷 `s`，如果當前出現的字元其上次出現的 index 位置在 substring 的範圍內，代表當前字元為重複字元，而新的 substring的起始 index 為當前字元上次出現的 $index + 1$ 。

e.g.

$s = "abcaecc"$

- 當 $index = 3$ 時， $substring = "abc"$ ，substring 的起始 index 更新為 1（b）。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int lengthOfLongestSubstring(std::string &s) {
        int max_len = 0, begin = 0; // begin 為 substring 的起始 index
        int char_table[128];        // 紀錄該字元最新出現的 index，128 為 ascii code 數量

        for (int &n : char_table) { // 初始化 hash table
            n = -1;
        }

        for (int i = 0; i < s.length(); ++i) {
            // 如果該字元上次出現的 index 在 substring 的範圍內
            if (char_table[s[i]] >= begin) {
                // substring 的起始 index 改為當前字元上次出現的 index + 1
                begin = char_table[s[i]] + 1;
            }
            max_len = std::max(max_len, i - begin + 1); // 計算當前sub string的長度
            char_table[s[i]] = i;                       // 更新字元最新出現的index
        }

        return max_len;
    }
};
```

[![](https://i.imgur.com/4Z4mvqg.png)](https://i.imgur.com/4Z4mvqg.png)

#### 複雜度分析

令 $n$ 為 `s` 的長度。

- 時間複雜度： $O(n)$

    每個字元只會被訪問一次。

- 空間複雜度： $O(1)$

    $O(128)$ ，即 $O(1)$（使用固定大小的 hash table 儲存 ASCII 字元）。
