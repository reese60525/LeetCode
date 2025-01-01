# <center> [1422. Maximum Score After Splitting a String](https://leetcode.com/problems/maximum-score-after-splitting-a-string/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501011044557.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501011044557.png)

給一個只包含 0 和 1 的字串 `s`，可以將字串分成任意**非空**的兩個子字串，計算左邊子字串 0 的數量加上右邊子字串 1 的數量的最大值。

## 解題思路

### 1. Prefix Sum

預先計算出所有 1 的數量，然後從左到右掃描字串，若當前是 0 則左字串的價值 + 1，反之若當前是 1 則右字串的價值 - 1，並計算當前最大值。

要注意的是因為題目要求兩子字串不能為空，所以只能遍歷到倒數第二個字元，避免右字串為空。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int maxScore(std::string s) {
        int cnt_ones = 0;
        for (char &c : s) {
            cnt_ones += c == '1';
        }

        int res = 0, cnt_zeros = 0;
        // 因為兩個字串不為空，所以最多只能遍歷到倒數第二個字元
        for (int i = 0; i < s.size() - 1; ++i) {
            cnt_zeros += s[i] == '0';
            cnt_ones -= s[i] == '1';
            res = std::max(res, cnt_zeros + cnt_ones);
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501011105106.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501011105106.png)

時間複雜度： $O(n)$ ，其中 $n$ 為字串長度。

空間複雜度： $O(1)$ 。

---

更優雅的寫法，將 `cnt_zeros` 和 `cnt_ones` 合併成一個變數 `score`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int maxScore(std::string s) {
        int score = std::ranges::count(s, '1');

        int res = 0;
        for (int i = 0; i < s.size() - 1; ++i) {
            score += s[i] == '0' ? 1 : -1;
            res = std::max(res, score);
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501011104032.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501011104032.png)

時間複雜度： $O(n)$ ，其中 $n$ 為字串長度。

空間複雜度： $O(1)$ 。
