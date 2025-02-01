# <center> [1400. Construct K Palindrome Strings](https://leetcode.com/problems/construct-k-palindrome-strings/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501111049339.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501111049339.png)

給一個由小寫英文字母組成的字串 `s` 和一個整數 `k`，請判斷能否使用 `s` 中**所有**的字元來組成 `k` 個回文。

- `s` 中所有的字元都要被使用。

- 對於 `s` 中的字元可以用任意的排列組合來組成回文。

## 解題思路

### 1. Hash Map

讓我們來觀察一下奇數個和偶數個相同的字元可以如何組成回文。

- 奇數個相同的字元：

  假設有 `i` 個 `a`，那我們可以組成 `[["a...a"]、["a", "a...a"]、["a", "a", "a...a"]...["a", "a", "a",..., "a"]]` 共 1 到 `i` 個的回文。

- 偶數個相同的字元：

  假設有 `i` 個 `a`，那我們可以組成 `[["a...a"]、["a", "a...a"]、["a", "a", "a...a"]...["a", "a", "a",..., "a"]]` 共 1 到 `i` 個的回文。

進一步討論 `s` 的組成方式：

- 只有奇數個的字元：

    假設有 `i` 個不同的奇數個字元，那麼最少需要 `i` 個回文才能將所有的字元用完，例如 $s = "aaabbbbbccc"$ ，以 `"aaa"` 為回文中心，將其他所有奇數個字元都兩兩一組分配到 `'a'` 來形成回文，最後會變成 `["bbcaaacbb", "b, "c"]`，可以看到每個奇數個字元一定會剩下一個字元，因此最少需要 `i` 個回文才能將所有的字元用完。

- 只有偶數個的字元：

    假設有 `i` 個不同的偶數個字元，所有的字元都可以依附在某個偶數個字元的回文上，因此最少需要 1 個回文才能將所有的字元用完，例如 $s = "aabbbbcc"$ ，以 `"aa"` 為中心，其他所有偶數個字元都能兩兩一組分配到 `"aa"` 左右兩邊來形成回文 `"bbcaacbb"`。

- 同時有奇數個和偶數個的字元：

    首先將 `s` 中所有奇數個字元都提出一個字元，這些被提出來的字元為 `s` 最少所需要組成的回文數量，而剩下的字元都會是偶數個，對於每個字元數量為 `x` 的偶數個字元都能組成 0 到 `x` 個回文，例如 $s = "abbbbccc"$ ，將所有奇數個字元都提出一個字元後會變成 `["a", "c", "bbbb", "cc"]`，`'a'` 和 `'c'` 都必須各自組成 1 個回文，對於 `"bbbb"` 可以組成 0 到 4 個回文，對於 `"cc"` 可以組成 0 到 2 個回文，因此要將所有字元都用完的話，我們可以組成 2 到 8 個回文，也就是 `[奇數個字元的數量, 字串長度]` 的範圍。

由上面討論的三種情形可統整出一個結論，只有 $\text{奇數個字元的數量} \leq k \leq \text{字串長度}$ 時，`k` 才能滿足條件，return true，反之則 return false。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool canConstruct(std::string s, int k) {
        // 計算每種字元出現次數是奇數還是偶數
        std::bitset<26> is_odd;
        for (char &c : s) {
            is_odd[c - 'a'] = !is_odd[c - 'a'];
        }

        // 計算字串中奇數個字元的數量
        int cnt = 0;
        for (int i = 0; i < 26; ++i) {
            cnt += is_odd[i] & 1;
        }

        return k >= cnt && k <= s.size();
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501111142434.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501111142434.png)

#### 複雜度分析

令 $n$ 為字串 `s` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
