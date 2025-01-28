# <center> [1525. Number of Good Ways to Split a String](https://leetcode.com/problems/number-of-good-ways-to-split-a-string/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226211329473.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226211329473.png)

給一個字串 `s`，將其分割兩個**不為空**的 substring，若這兩個 substring 的字元種類數相同，則稱為一個 good split，請找出 `s` 有幾個 good split。

## 解題思路

### 1. Hash Table

創建兩個 hash map 用於紀錄當前左右兩邊的 substring 中每個字元的出現頻率，先計算出 `s` 中每個字元的出現頻率和種類數並賦值給左邊的 substring，接著從頭到尾遍歷 `s`，依序更新左右兩邊的 substring 的字元出現頻率和字元種類數，若左右兩邊的 substring 的字元種類數相同，則 $res + 1$ 。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int numSplits(std::string s) {
        int left_freq[26] = {0}, right_freq[26] = {0};
        int left_cnt = 0, right_cnt = 0;

        // 計算 s 中所有字元出現頻率
        for (auto &c : s) {
            if (++right_freq[c - 'a'] == 1) {
                ++right_cnt;
            }
        }

        // 從頭開始分割，並更新當前左右兩個 substring 的不同字元數量
        int res = 0;
        for (auto &c : s) {
            int cur = c - 'a';

            if (++left_freq[cur] == 1) {
                ++left_cnt;
            }
            if (--right_freq[cur] == 0) {
                --right_cnt;
            }

            res += left_cnt == right_cnt;
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226212014869.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226212014869.png)

#### 複雜度分析

令 $n$ 為 `s` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$

    因為字元種類數最多為 26 種。
