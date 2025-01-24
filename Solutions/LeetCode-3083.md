# <center> [3083. Existence of a Substring in a String and Its Reverse](https://leetcode.com/problems/existence-of-a-substring-in-a-string-and-its-reverse/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226124935733.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226124935733.png)

給一個只包含小寫英文字母的字串 `s`，如果存在一個長度為 2 的字串 `sub` 並且在 `s` 的 reverse `s'` 中也存在 `sub`，則 return true，若整個 `s` 都不存在這樣的 `sub` 則 return false。

## 解題思路

### 1. Hash Map

要確認一個 substring `sub` 是否同時在 `s` 和 `s` 的 reverse `s'` 中都出現，可以檢查 `sub` 和 `sub` 的 reverse `sub'` 是否都出現在 `s` 中。例如 `s` = "abckecb"，`sub` = "bc" ，在 `s'` 中原本的 `sub'` "cb" 會變成 "bc"，所以就能透過檢查 `sub` 和 `sub'` 是否都出現在 `s` 中來確認 `sub` 是否同時在 `s` 和 `s'` 中都出現。

用一個 `26 x 26` 的 map 來儲存每一對字母是否出現過，例如 `s` 中有個 `sub` 為 "ad"，則 `map[0][3] = true`，表示 `s` 中有出現過 "ad"，然後檢查 `map[3][0]` 也就是 "da" 是否也在 `s` 中出現過，若都出現過則 return true。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool isSubstringPresent(std ::string s) {
        std::bitset<26> mp[26];

        for (size_t i = 0; i < s.size() - 1; ++i) {
            int a = s[i] - 'a', b = s[i + 1] - 'a';

            mp[a][b] = true;
            if (mp[b][a]) {
                return true;
            }
        }

        return false;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226132308376.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226132308376.png)

#### 複雜度分析

令 $n$ 為 `s` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$

    `cnt` 的大小恆為 $26 \times 26$ 。

### 2. Hash Map and Bit Manipulation

在方法一中，`map` 的空間還能進一步優化成一維陣列，一個 integer 共有 32 個 bit，將其中從右到左的 26 個 bit 用來儲存每個字母是否出現過的資訊，`map[i]` 表示以第 `i` 個英文字母為開頭的 substring，例如現在有出現過 "ab"、"ah"、"ax" 這三個 substring，則 `map[0] = 0b00000000100000000000000010000010`，其中 `map[0]` 的第 0 個 bit 表示 "a" 是否出現過，第 1 個 bit 表示 "b" 是否出現過，以此類推。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool isSubstringPresent(std ::string s) {
        int mp[26] = {0};

        for (size_t i = 0; i < s.size() - 1; ++i) {
            int a = s[i] - 'a', b = s[i + 1] - 'a';

            // 將 0x1 左移到第 b 個 bit 並與 mp[a] 做 bitwise OR
            mp[a] |= 1 << b;
            // 將 mp[b] 右移到第 a 個 bit 並與 0x1 做 bitwise AND
            if ((mp[b] >> a) & 1) {
                return true;
            }
        }

        return false;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226132215449.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226132215449.png)

#### 複雜度分析

令令 $n$ 為 `s` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$

    `mp` 的大小恆為 $26$ 。
