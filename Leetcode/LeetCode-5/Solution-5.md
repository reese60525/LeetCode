# <center> [LeetCode - 5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241220213441064.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241220213441064.png)

給一個 string `s`，找出最長的回文子字串。

## 解題思路

### 1. Dynamic Programming

對於一個字串 `s`，如果 $s[i] == s[j]$ 且 $s[i+1:j-1]$ 是回文，則 $s[i:j]$ 也會是回文，而當 `s` 長度為 1 和 2 時，只需要判斷 $s[i] = s[j]$ 是否成立即可，可以用 `dp[i][j]` 儲存當 `s` 的範圍是 $[i, j]$ 時是否為回文，因此可以得到以下狀態轉移公式：  

$$
dp[i][j] =
\begin{cases}
true, & \text{if }s[i] = s[j] \text{ and } (dp[i+1][j-1] = true \text{ or } length < 3)\\
false,& \text{if }s[i]\neq s[j] \text{ or } dp[i+1][j-1] = false\\
\end{cases}
$$

由於是根據 `dp[i+1][j-1]` 的狀態來進行判斷，因此 `i` 要從 $n-1$ 開始往前遍歷，而 `j` 不管是從 $i+1$ 到 $n-1$ 或是 $n-1$ 到 $i+1$ 都可以，因為用的都是 `dp[i+1]` 這一列的狀態，不必擔心 `dp[i+1][j-1]` 還沒被更新過。

#### 程式碼

```cpp {.line-numbers}
/*
 *  Author      : Reese
 *  Created On  : 2024-12-20 23:59
 *  Description : https://leetcode.com/problems/longest-palindromic-substring/description/
 */

class Solution {
  public:
    std::string longestPalindrome(std::string s) {
        size_t n = s.length();
        std::pair<size_t, size_t> res_index = {0, 0}; // 最長回文子字串的起始和終點 index
        bool dp[n][n];
        std::memset(dp, 0, sizeof(dp));

        // i < n 是因為 size_t 是 unsigned int，所以 i 不會是負數
        // 當 i 從 0 減 1 時，會變成 unsigned int 的最大值，因此迴圈判斷條件要為 i < n 而不是 i >= 0
        for (size_t i = n - 1; i < n; --i) {
            dp[i][i] = true; // 單個字元一定是回文
            for (size_t j = i + 1; j < n; ++j) {
                dp[i][j] = ((s[i] == s[j]) && (j - i < 3 || dp[i + 1][j - 1]));
                // 如果 s[i:j] 是回文，且長度大於目前最長回文子字串的長度，則更新最長回文子字串的起始和終點 index
                if (dp[i][j] && (j - i) > (res_index.second - res_index.first)) {
                    res_index = {i, j};
                }
            }
        }

        return s.substr(res_index.first, res_index.second - res_index.first + 1);
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241221000024843.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241221000024843.png)

時間複雜度： $O(n^2)$ ，其中 $n$ 是字串 `s` 的長度。  
空間複雜度： $O(n^2)$ 。

---
對於這個 `dp[i][j]` 可以進一步做空間上的優化，因為 `dp[i][j]` 只會用到 `dp[i+1]` 這一列的狀態，因此可以將 `dp` 改成一維陣列，`dp[i][j]` 就降維成 `dp[j]`。令 $i = k$ ，則 `dp[j]` 儲放的是 $i = k+1$ 時的狀態，狀態轉移公式變成：  

$$
dp[j] =
\begin{cases}
true, & \text{if }s[i] = s[j] \text{ and } (dp[j-1] = true \text{ or } length < 3)\\
false,& \text{if }s[i]\neq s[j] \text{ or } dp[j-1] = false\\
\end{cases}
$$

如果 `j` 是從 $i+1$ 遍歷到 $n-1$ ，則 `dp[j]` 會變更新為 $i = k$ 時的狀態，而 `dp[j+1]` 所需要的是 $i = k+1$ 時 `dp[j]` 的狀態，因此 `j` 必須從 $n-1$ 遍歷到 $i+1$ ，才能保證 `dp[j-1]` 是 $i = k+1$ 時的狀態而非 $i = k$ 時的狀態。  

``` text
dp[j] 中的 o 表示當前可以被填入 T 或 F 的格子，x 表示還不能被填入，因為還沒有遍歷到

      index:    0  1  2  3  4  5  6  7  8  9
i = 6, dp[j] = {x, x, x, x, x, x, T, F, F, T}
i = 5, dp[j] = {x, x, x, x, x, o, o, o, o, o}
                                  |  |
                                  |  |-> 需要由 i = 6 時的 dp[6] 來判斷，若從 j = 5 開始遍歷，此時的 dp[6]
                                  |      已經被更新為 i = 5 時的狀態，會導致結果判斷錯誤，因此 j 必須從 n-1 開始往前遍歷
                                  V
該 dp[6] 的範圍是 s[5] 到 s[6]，長度 < 3 因此能直接判斷 s[i] == s[j] 是否成立就好
```

#### 程式碼

```cpp  {.line-numbers}
/*
 *  Author      : Reese
 *  Created On  : 2024-12-20 23:59
 *  Description : https://leetcode.com/problems/longest-palindromic-substring/description/
 */

class Solution {
  public:
    std::string longestPalindrome(std::string s) {
        size_t n = s.length();
        std::pair<size_t, size_t> res_index = {0, 0}; // 最長回文子字串的起始和終點 index
        bool dp[n];
        std::memset(dp, 0, sizeof(dp));

        // i < n 是因為 size_t 是 unsigned int，所以 i 不會是負數
        // 當 i 從 0 - 1 時，會變成 unsigned int 的最大值，因此迴圈判斷條件要為 i < n 而不是 i >= 0
        for (size_t i = n - 1; i < n; --i) {
            for (size_t j = n - 1; j > i; --j) {
                dp[j] = ((s[i] == s[j]) && (j - i < 3 || dp[j - 1]));
                if (dp[j] && (j - i) > (res_index.second - res_index.first)) {
                    res_index = {i, j};
                }
            }
        }

        return s.substr(res_index.first, res_index.second - res_index.first + 1);
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241221005256689.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241221005256689.png)

時間複雜度： $O(n^2)$ ，其中 $n$ 是字串 `s` 的長度。  
空間複雜度： $O(n)$ 。  

### 2. Two Pointers

遍歷 `s` 的每個字元，假設如果是奇數長度的回文則以該字元為中心，如果是偶數長度的回文則以該字元和下一個字元為中心，然後向兩側擴展，直到不是回文為止，並記錄最長的回文子字串。

#### 程式碼

```cpp {.line-numbers}
/*
 *  Author      : Reese
 *  Created On  : 2024-12-20 23:59
 *  Description : https://leetcode.com/problems/longest-palindromic-substring/description/
 */

class Solution {
  public:
    std::string longestPalindrome(std::string s) {
        std::pair<int, int> res_index = {0, 0}; // 最長回文子字串的起始index和終點index

        for (int i = 0; i < s.length(); ++i) {
            std::pair<int, int> sub_odd = findPalindromic(i, i, s);      // 奇數回文
            std::pair<int, int> sub_even = findPalindromic(i, i + 1, s); // 偶數回文

            // 若sub_odd比res_index長，則更新res_index
            if ((res_index.second - res_index.first) < (sub_odd.second - sub_odd.first)) {
                res_index = sub_odd;
            }
            // 若sub_even比res_index長，則更新res_index
            if ((res_index.second - res_index.first) < (sub_even.second - sub_even.first)) {
                res_index = sub_even;
            }
        }

        return s.substr(res_index.first, res_index.second - res_index.first + 1);
    }

  private:
    //  尋找以left和right為中心點的回文
    std::pair<int, int> findPalindromic(int left, int right, std::string &s) {
        int len = s.length();

        // 判斷邊界條件和兩側字元是否相等
        while (left > -1 && right < len && s[left] == s[right]) {
            --left;
            ++right;
        }

        // 因為while loop最後會多執行一次，所以left和right要各往中心退一格
        return {left + 1, right - 1};
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241221010101592.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241221010101592.png)

時間複雜度： $O(n^2)$ ，其中 $n$ 是字串 `s` 的長度。  
空間複雜度： $O(1)$ 。  

### 3. Manacher's Algorithm

[演算法講解影片](https://www.bilibili.com/video/BV1UcyYY4EnQ/?share_source=copy_web&vd_source=2a4a030736f1bf1d936f767fc30f5a20&t=182)

Manacher's Algorithm 是一種用於尋找字串中最長迴文子字串的演算法，它可以在 $O(n)$ 的時間複雜度內找到最長迴文子字串。  
假設 `s` = "cdabcbabcbade"，若使用 `two pointers` 來找最長迴文子字串，當 $i = 6$ 會有回文 "dabcbabcbad"，而當 $i = 8$ 時可以找到回文 "abcba"，可以發現該回文 "abcba" 早已被 $i = 6$ 時找到的回文 "dabcbabcbad" 包含，因此可以通過以下演算法流程，達到利用前面找到的迴文，來減少計算的次數。  

令 `s` = "cdabcbabcbade"，`pivot` 為目前找到的回文中**終點**最遠的中心點，`max_right` 為 `pivot` 所對應的回文終點。  
當 $i = 8$ 時， $pivot = 6$ 、 $max\_right = 11$ ，令 `mirror_i` 為 `i` 以 `pivot` 為中心點的鏡像點，則 $mirror\_i = 2 \times pivot - i = 4$ ，由於 `i` 和 `mirror_i` 都是在 `pivot` 所對應的回文範圍內並且兩者都是以 `pivot` 為中心的鏡像點，因此以 `pivot` 為中心的回文兩端對應的字元必定相同這一特性，`mirror_i` 為中心點所對應的回文的**左半區和右半區**能夠分別對應到以 `i` 為中心點的回文的**右半區和左半區**，像是 `mirror_i` 的回文是 "abcba" ，`i` 的回文是 "abcba"，`mirror_i` 回文的左半區 "ab" 對應到 `i` 回文的右半區 "ab"，`mirror_i` 回文的右半區 "ba" 對應到 `i` 回文的左半區 "ba"，`mirror_i` 能對應到 `i`，因此 `i` 的回文範圍可以以 `mirror_i` 的回文大小為基礎來進行擴充，但前提是 `mirror_i` 的回文範圍必須在 `pivot` 的回文範圍內，否則 `i` 的回文範圍若以 `mirror_i` 的回文範圍為基礎進行擴充，會導致 `i` 的回文範圍超出 `pivot` 的回文範圍，也就是 `i` 的回文終點會超過 `max_right`，而 `max_right` 右側的字元還沒被遍歷過因此無法得知是否能夠成為 `i` 的回文，因此當 `mirror_i` 的回文範圍有部分在 `pivot` 的回文範圍外時，`i` 的回文範圍要變成終點為 `max_right` 的回文。若 `i` 超過 `max_right` 時，因為此時 `i` 右側的字元都沒被遍歷過，因此 `i` 的回文範圍要從 `i` 開始擴充。  

那如果回文是偶數長度呢? 例如 "abba" ，可以透過在每個字元間插入特殊字元 '#' 來將偶數長度的回文轉換成奇數長度的回文，例如 `s` = "abba" 轉換成 `s'` = "#a#b#b#a#" ，此時原本回文 "abba" 的中心點 "bb" 會變成 "#a#b#b#a#" 的 '#'，這樣就可以套用上述演算法。此外還能在兩側額外加上特殊字元來避免邊界條件判斷，例如 `s` = "abba" 轉換成 `s'` = "^#a#b#b#a#$" ，由於 "^" 和 "$" 在字串中只會出現一次，因此當判斷 $s'[i] == s'[j]$ 時，若遇到 '^' 或 '\$' 必定會因此字元不相同跳出迴圈，藉此避免邊界條件判斷。  

要完成以上流程，需要一個 array 紀錄每個字元為中心點的回文範圍，假設 `p[i]` 為以 `i` 為中心點的回文範圍，則 `p[i]` 的值為 `i` 到終點的長度，例如 "abba" 轉換成 "^#a#b#b#a#$" ，則 $p[1] = 1$ ，因為 '#' 的回文範圍是 "#"，從中心點到終點是 "#"，長度為 1， $p[2] = 2$ ，因為 'a' 的回文範圍是 '#a#'，從中心點到終點是 "a#"，長度為 2， $p[5] = 5$ ，因為 '#' 的回文範圍是 "#a#b#b#a#"，從中心點到終點是 "#b#a#"，長度為 5，以此類推。可以發現到 $p[i] - 1$ 就是**原本字串中**以 `i` 為中心點的回文長度，因此可以透過 $p[i] - 1$ 來計算原本的字串以 `i` 為中心點的回文長度。  

而要從新的字串 `s'` 的 $index = j$ 推導出原本的字串 `s` 所對應的 index `i`，觀察 `s` = "abba" 和 `s'` = "^#a#b#b#a#$"，可以發現 `s[i*2 + 2]` 對應到 `s'[j]`，因此要從 `j` 推導出原本的 `i`，公式為 $i = \frac{j - 2}{2}$ 。  
題目要求回傳的是回文子字串，因此需要知道回文子字串的**起始 index**，一樣以 `s'` = "^#a#b#b#a#$" 為例，中心點 '#' 的 index 為 5，p[5] = 5，求該回文的起始 index，就是用中心點的 index 減去 $p[5] - 1$ ， $p[5] - 1$ 是因為要將中心點排除，這樣就能得到起始 index 為 $5 - (5 - 1) = 1$ ，由於起始字元是 '#'，因此要再加上 1 才是原始回文子字串的起始字元，也就是 2，配合前面得到的原始 index 對應公式： $i = \frac{j - 2}{2}$ ，可以得到原始字串的起始 index 為 $i = \frac{2 - 2}{2} = 0$ ，因此原始回文子字串的起始 index 為 0，也就是 `s[0]`，原始字串的回文起始 index 公式為： $\frac{[j - (p[j] - 1) + 1]-2}{2} = \frac{j-p[j]}{2}$ 。  

為何時間複雜度是 $O(n)$ 呢?整個演算法是以 `max_right` 為判斷基準，只要 `i` 是在 `max_right` 右側，就能以 $O(1)$ 的時間複雜度來找到 `i` 的回文範圍，而且該回文範圍已經是最大的無法再擴充了，舉個例子假設 `s` = "yqabacdcabaqk"，最長迴文子字串為 "qabacdcabaq"，`pivot` = 6、`max_right` = 11，當 `i` = 9 時回文是 "aba"，`mirror_i` = 3 回文是"aba"，假如 `i` 的回文 "aba" 還能往左右擴充，那麼就得是 $s[7] = s[11]$ ，並且根據 `pivot` 的回文，也要滿足 $s[7] = s[5]$ 和 $s[11] = s[1]$ 這些條件，最終會變成要滿足 $s[1] = s[5] = s[7] = s[11]$ ，但是 `mirror_i` 的最大回文範圍是 $[s[2],s[4]]$ ，要是 $s[1] = s[5] = s[7] = s[11]$ 能被滿足，那麼 `mirror_i` 的回文就應該是 $s[[1],s[5]]$ 了，出現了矛盾，由此可證明只要 `i` 在 `max_right` 右側並且 `mirror_i` 的回文範圍在 `pivot` 回文範圍中，那麼 `i` 基於 `mirror_i` 的回文範圍就是最大的無法擴充。那如果是 `i` 在 `max_right` 左側或是 `mirror_i` 的回文超出 `pivot` 的回文範圍呢?這個時候如果 `i` 能夠擴充，那麼 `i` 的回文終點就會超過 `max_right` ，而 `max_right` 就會被更新，因此下次 `i+1` 仍然可以以 $O(1)$ 的時間複雜度來找到 `i` 的回文範圍，`max_right` 最多被更新 $n$ 次，因此整個演算法時間複雜度為 $O(n)$ 。

結論：  

- 若 $i \leq max\_right$ 且 `mirror_i` 的回文範圍在 `pivot` 回文範圍中，則 `i` 的回文範圍可以以 `mirror_i` 的回文大小為基礎來進行擴充，則 `i` 的回文範圍為 $[i - (p[mirror\_i] - 1), i + (p[mirror\_i] - 1)]$ ， $p[i] = p[mirror\_i]$ ，以此為基礎往兩側擴充找回文。  
- 若 $i \leq max\_right$ 且 `mirror_i` 的回文範圍在 `pivot` 回文範圍外，則 `i` 的回文範圍要變成終點為 `max_right` 的回文，也就會變成 $[i - (max\_right - i), i + (max\_right - i)]$ ， $p[i] = max\_right - i + 1$ ，以此為基礎往兩側擴充找回文。
- 以上兩種情況可以合併成一個公式， $p[i] = min(p[mirror\_i], max\_right - i + 1)$ 。
- 若 $i > max\_right$ ，則 `i` 的回文範圍要從 `i` 開始擴充，也就是 $[i, i]$ ， $p[i] = 1$ 。

#### 程式碼

```cpp {.line-numbers}
/*
 *  Author      : Reese
 *  Created On  : 2024-12-20 23:59
 *  Description : https://leetcode.com/problems/longest-palindromic-substring/description/
 */

class Solution {
  public:
    std::string longestPalindrome(std::string s) {
        // 將 string 轉換成 manacher's algorithm 的格式
        // e.g. s = "abba" -> str = "^#a#b#b#a#$"
        size_t n = s.length();
        std::string str(2 * n + 3, '#');
        str[0] = '^';
        str[2 * n + 2] = '$';
        for (size_t i = 0; i < n; ++i) {
            str[2 * i + 2] = s[i];
        }

        // max_right 為目前找到的回文子字串終點最右邊的 index，pivot 為 max_right 的回文中心點 index
        // max_i 為目前找到的最長回文子字串的中心點 index，max_len 為目前找到的最長回文子字串長度
        size_t pivot = 0, max_right = 0, max_i = 0, max_len = 0;
        // 用來儲存 str 中以 str[i] 為回文中心，從 str[i] 到回文子字串終點的長度
        std::vector<size_t> str_max_len(str.size(), 1);
        // 排除 ^ 和 $，index = [1, str.size() - 2]
        for (size_t i = 1; i < str.size() - 1; ++i) {
            // mirror_i 為 i 基於 pivot 的鏡像 index
            size_t mirror_i = 2 * pivot - i;
            // 利用已經算過的 str_max_len 來設定 str_max_len[i]
            if (i < max_right) {
                str_max_len[i] = std::min(str_max_len[mirror_i], max_right - i + 1);
            }

            // 試著擴展 str_max_len[i]
            while (str[i - str_max_len[i]] == str[i + str_max_len[i]]) {
                ++str_max_len[i];
            }

            // 若 str_max_len[i] 擴展到 max_right 之外，則更新 max_right 和 pivot
            if (i + str_max_len[i] - 1 > max_right) {
                max_right = i + str_max_len[i] - 1;
                pivot = i;
            }

            // 如果新的回文子字串長度大於 max_len，則更新 max_len 和 max_i
            if (str_max_len[i] > max_len) {
                max_len = str_max_len[i];
                max_i = i;
            }
        }

        return s.substr((max_i - max_len) / 2, max_len - 1);
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241221034653137.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241221034653137.png)

時間複雜度： $O(n)$ ，其中 $n$ 是字串 `s` 的長度。  
空間複雜度： $O(n)$ 。
