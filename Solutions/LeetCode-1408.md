# <center> [1408. String Matching in an Array](https://leetcode.com/problems/string-matching-in-an-array/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501092123929.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501092123929.png)

給一個大小為 `n` 的字串陣列 `words`，找出所有能成為其他字串的 substring 的字串。

## 解題思路

### 1. Brute Force

測資很小，可以直接比對每個字串對，令 $i \neq j$ 且 $0 \leq i, j \leq n-1$ ，檢查每個 `word[i]` 是否為其他 `word[j]` 的 substring，如果可以就把 `word[i]` 加入陣列 `res` 中，最後 return `res` 即可。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<std::string> stringMatching(std::vector<std::string> &words) {
        int n = words.size();

        // 檢查 words 中有沒有某個字串的 substring 和 word[i] 相同
        std::vector<std::string> res;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && words[j].find(words[i]) != std::string::npos) {
                    res.emplace_back(words[i]);
                    break;
                }
            }
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501092128499.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501092128499.png)

#### 複雜度分析

令 $n$ 為 `words` 的大小， $m$ 為 `words` 中的最長的字串長度。

- 時間複雜度： $O(m^2 \cdot n^2)$

    共有 $n(n-1)$ 個字串對，每個字串對要配對 substring 需要 $O(m^2)$ 的時間複雜度，因此總時間複雜度為 $O(m^2 \cdot n^2)$ 。

- 空間複雜度： $O(1)$

### 2. KMP Algorithm

對於配對 substring 的問題，我們可以使用 `KMP Algorithm` 來加速配對的過程，使得時間複雜度從 $O(m^2)$ 降為 $O(m)$ 。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    // 計算 s 的 LPS table
    std::vector<int> getNext(std::string &s) {
        int j = 0, n = s.size();
        // next[i] = j 表示長度為 i 的字串其 LPS 長度為 j
        std::vector<int> next(n + 1, 0);
        for (int i = 1; i < n; ++i) {
            // 若當前字元不匹配，用 next 表找出能匹配的 s[j]
            while (j > 0 && s[i] != s[j]) {
                j = next[j];
            }
            // 如果 s[i] = s[j]，j 要 +1 往後一個字元來繼續檢查，否則保持為 0
            j += s[i] == s[j];
            next[i + 1] = j;
        }

        return next;
    }

    std::vector<std::string> stringMatching(std::vector<std::string> &words) {
        std::vector<std::string> res;
        for (int i = 0; i < words.size(); ++i) {
            bool isSubstringFound = false;
            std::vector<int> next = getNext(words[i]); // 取得 LPS table

            for (int j = 0; j < words.size(); ++j) {
                // 用於確認 words[i] 是否被添加至 res 中，避免重複添加答案
                if (isSubstringFound) {
                    break;
                }
                // 若 words[i] 的長度大於 words[j]，那麼前者不可能是後者的 substring
                if (i == j || words[i].size() > words[j].size()) {
                    continue;
                }

                // 匹配 words[i] 和 words[j] 的做法和 getNext() 一樣，
                int m = 0; // m 為 words[i] 當前 index
                for (int n = 0; n < words[j].size(); ++n) {
                    while (m > 0 && words[i][m] != words[j][n]) {
                        m = next[m];
                    }
                    m += words[i][m] == words[j][n];
                    if (m == words[i].size()) {
                        res.emplace_back(words[i]);
                        isSubstringFound = true; // 設為 true 用以跳出 j 迴圈
                        break;
                    }
                }
            }
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501092358737.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501092358737.png)

#### 複雜度分析

令 $n$ 為 `words` 的大小， $m$ 為 `words` 中的最長的字串長度。

- 時間複雜度： $O(m \cdot n^2)$

    共有 $n(n-1)$ 個字串對，由於使用 `KMP Algorithm` 來匹配字串，因此時間複雜度降為 $O(m)$，總時間複雜度為 $O(m \cdot n^2)$ 。

- 空間複雜度： $O(m)$

    LPS table `next` 的大小為 $m$ 。
