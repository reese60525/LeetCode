# <center> [1930. Unique Length-3 Palindromic Subsequences](https://leetcode.com/problems/unique-length-3-palindromic-subsequences/description/) </center>

## 題目敘述

[![](https://i.imgur.com/maFRPXK.png)](https://i.imgur.com/maFRPXK.png)

給一個只包含小寫英文字母的字串 `s`，請找出所有**長度為 3** 並且是回文的**不重複子序列**，回傳所有可能的不重複回文子序列數量。

- 在 $s = "aaaaaaa"$ 中，只有 `"aaa"` 是長度為 3 的回文子序列，該子序列在 `s` 中出現了多次，重複的子序列只要計算一次就好，因此 return 1。

## 解題思路

### 1. Hash Table

迭代 26 個英文字母，找出每個字元在 `s` 中第一次和最後一次出現的 index，以該字母為回文的起點和終點，然後計算這之間有多少種不同的字元可以當作回文的中心字元，將結果累加即可得到答案。

### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int countPalindromicSubsequence(std::string s) {
        int n = s.size(), res = 0;

        // 遍歷每種小寫字母
        for (char c = 'a'; c <= 'z'; ++c) {
            // 找該字母的起點和終點位置
            int l = 0, r = n - 1;
            while (l < n && s[l] != c) {
                ++l;
            }
            while (r >= 0 && s[r] != c) {
                --r;
            }

            // 如果 r - l < 2 表示該字母在 s 中的數量 <=1，無法形成回文
            if (r - l < 1) {
                continue;
            }

            // 計算回文有幾種不同字元可以當中心點
            std::unordered_set<char> cnt;
            for (int i = l + 1; i < r; ++i) {
                cnt.insert(s[i]);
            }
            res += cnt.size();
        }

        return res;
    }
};
```

[![](https://i.imgur.com/jWHnvNZ.png)](https://i.imgur.com/jWHnvNZ.png)

#### 複雜度分析

令 $n$ 為字串 `s` 的長度， $|\sum|$ 為字符集的數量。

- 時間複雜度： $O(n |\sum|)$

- 空間複雜度： $O(|\sum|)$

    `std::unordered_set` 最多需要 $O(|\sum|)$ 的空間。

### 2. Prefix Sum and Suffix Sum and Bit Manipulation

遍歷 `s` 中的每個字元，以該字元為中心點，找出左右兩邊共同出現的字元數量，將每種字元不重複的左右共同字元數量累加即可得到答案。

令 `prefix[i]` 和 `suffix[i]` 分別為 `s` 中 $index = [0, i]$ 和 $index = [i, n - 1]$ 的不同字元數量，用於計算 `s[i]` 左右兩邊共同出現的字元數量。

由於小寫字母只有 26 個，因此可以用一個 32 bits 整數來表示 `prefix[i]` 和 `suffix[i]`，從最右邊開始的 bit 表示字母 `'a'` 是否出現過，如果第 `i` 個 bit 為 1 表示該字母出現過，0 表示該字元沒有出現過。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int countPalindromicSubsequence(std::string s) {
        int n = s.size();

        // prefix[i] 和 suffix[i] 分別紀錄 [0, i] 和 [i, n-1] 之間有幾種不同字元
        std::vector<int> prefix(n), suffix(n);
        for (int i = 0; i < n; ++i) {
            prefix[i] = ((i > 0) ? prefix[i - 1] : 0) | (1 << (s[i] - 'a'));
            suffix[n - i - 1] = ((i > 0) ? suffix[n - i] : 0) | (1 << (s[n - i - 1] - 'a'));
        }

        // 遍歷 s 中每個字元，計算以該字元為中心點時左右兩邊共同擁有的字元數量，並將這些不重複的共同字元累加
        int cnt[26];
        for (int i = 1; i < n - 1; ++i) {
            cnt[s[i] - 'a'] |= (prefix[i - 1] & suffix[i + 1]);
        }

        // 計算 cnt[i] 中 bit = 1 數量
        int res = 0;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                res += cnt[i] & 1;
                cnt[i] >>= 1;
            }
        }

        return res;
    }
};
```

[![](https://i.imgur.com/8vMy2fJ.png)](https://i.imgur.com/8vMy2fJ.png)

#### 複雜度分析

令 $n$ 為字串 `s` 的長度， $|\sum|$ 為字符集的數量。

- 時間複雜度： $O(n + |\sum|)$

- 空間複雜度： $O(n + |\sum|)$
