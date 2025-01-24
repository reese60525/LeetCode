# <center> [3223. Minimum Length of String After Operations](https://leetcode.com/problems/minimum-length-of-string-after-operations/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131037545.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131037545.png)

給一個由小寫字母組成的字串 `s` ，可以對其進行以下操作數次：

- 選擇某個字元 `s[i]`，將其左右邊和 `s[i]` 相同的最近字元刪除。

- 若左邊或右邊沒有相同字元則不能進行刪除的操作。

請回傳進行數次刪除操作後所能得到的最短字串長度。

## 解題思路

### 1. HashMap

觀察以下某個相同字元經過操作後所能得到的最短字串長度：

- s = ""，經過操作後 s = ""，長度 = 0。

- s = "a"，經過操作後 s = "a"，長度 = 1。

- s = "aa"，經過操作後 s = "aa"，長度 = 2。

- s = "aaa"，經過操作後 s = "a"，長度 = 1。

- s = "aaaa"，經過操作後 s = "aa"，長度 = 2。

- s = "aaaaa"，經過操作後 s = "a"，長度 = 1。

- s = "aaaaaa"，經過操作後 s = "aa"，長度 = 2。

- 以此類推 ...

能發現以上情況可以分為三種：

1. 同個字元數量為 0，經過操作後最短長度仍為 0。

2. 同個字元數量為奇數，經過操作後最短長度為 1。

3. 同個字元數量為偶數，經過操作後最短長度為 2。

因此可以用 `Hash Map` 紀錄每個字元出現的次數，並判斷該字元數量為 0、奇數或偶數，將所有字元經過操作後的最短長度加總即可得到答案。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int minimumLength(std::string &s) {
        // 計算每個字元出現次數
        int cnt[26] {0};
        for (const char &c : s) {
            ++cnt[c - 'a'];
        }

        // 若出現奇數次，則最多可以刪減到剩下 1 個字元，偶數則是 2 個字元
        int res = 0;
        for (const int &n : cnt) {
            // 若該字元出現次數為 0，則跳過
            if (n == 0) {
                continue;
            }
            res += (n & 1) ? 1 : 2;
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131048505.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131048505.png)

#### 複雜度分析

令 $n$ 為字串 `s` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
